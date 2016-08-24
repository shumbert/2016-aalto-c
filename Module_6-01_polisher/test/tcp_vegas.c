/*
 * TCP Vegas congestion control
 *
 * This is based on the congestion detection/avoidance scheme described in
 *    Lawrence S. Brakmo and Larry L. Peterson.
 *    "TCP Vegas: End to end congestion avoidance on a global internet."
 *    IEEE Journal on Selected Areas in Communication, 13(8):1465--1480,
 *    October 1995. Available from:
 *	ftp://ftp.cs.arizona.edu/xkernel/Papers/jsac.ps
 *
 * See http://www.cs.arizona.edu/xkernel/ for their implementation.
 * The main aspects that distinguish this implementation from the
 * Arizona Vegas implementation are:
 *   o We do not change the loss detection or recovery mechanisms of
 *     Linux in any way. Linux already recovers from losses quite well,
 *     using fine-grained timers, NewReno, and FACK.
 *   o To avoid the performance penalty imposed by increasing cwnd
 *     only every-other RTT during slow start, we increase during
 *     every RTT during slow start, just like Reno.
 *   o Largely to allow continuous cwnd growth during slow start,
 *     we use the rate at which ACKs come back as the "actual"
 *     rate, rather than the rate at which data is sent.
 *   o To speed convergence to the right rate, we set the cwnd
 *     to achieve the right ("actual") rate when we exit slow start.
 *   o To filter out the noise caused by delayed ACKs, we use the
 *     minimum RTT sample observed during the last RTT to calculate
 *     the actual rate.
 *   o When the sender re-starts from idle, it waits until it has
 *     received ACKs for an entire flight of new data before making
 *     a cwnd adjustment decision. The original Vegas implementation
 *     assumed senders never went idle.
 */

#include <linux/mm.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/inet_diag.h>

#include <net/tcp.h>

#include "tcp_vegas.h"

static int alpha = 2;
static int beta  = 4;
static int gamma = 1;

module_param(alpha, int, 0644);
MODULE_PARM_DESC(alpha, "lower bound of packets in network");
module_param(beta, int, 0644);
MODULE_PARM_DESC(beta, "upper bound of packets in network");
module_param(gamma, int, 0644);
MODULE_PARM_DESC(gamma, "limit on increase (scale by 2)");


/* There are several situations when we must "re-start" Vegas:
 *
 *  o when a connection is established
 *  o after an RTO
 *  o after fast recovery
 *  o when we send a packet and there is no outstanding
 *    unacknowledged data (restarting an idle connection)
 *
 * In these circumstances we cannot do a Vegas calculation at the
 * end of the first RTT, because any calculation we do is using
 * stale info -- both the saved cwnd and congestion feedback are
 * stale.
 *
 * Instead we must wait until the completion of an RTT during
 * which we actually receive ACKs.
 */
static void vegas_enable(struct sock *sk)
{
const struct tcp_sock *tp = tcp_sk(sk);
struct vegas *vegas = inet_csk_ca(sk);

/* Begin taking Vegas samples next time we send something. */
vegas->doing_vegas_now = 1;

/* Set the beginning of the next send window. */
vegas->beg_snd_nxt = tp->snd_nxt;

vegas->cntRTT = 0;
vegas->minRTT = 0x7fffffff;
}

/* Stop taking Vegas samples for now. */
static inline void vegas_disable(struct sock *sk)
{
struct vegas *vegas = inet_csk_ca(sk);

vegas->doing_vegas_now = 0;
}

void tcp_vegas_init(struct sock *sk)
{
struct vegas *vegas = inet_csk_ca(sk);

vegas->baseRTT = 0x7fffffff;
vegas_enable(sk);
}
EXPORT_SYMBOL_GPL(tcp_vegas_init);


static void tcp_vegas_cong_avoid(struct sock *sk, u32 ack, u32 acked)
{
struct tcp_sock *tp = tcp_sk(sk);
struct vegas *vegas = inet_csk_ca(sk);

if (!vegas->doing_vegas_now) {
tcp_reno_cong_avoid(sk, ack, acked);
return;
}

if (after(ack, vegas->beg_snd_nxt)) {
/* Do the Vegas once-per-RTT cwnd adjustment. */

/* Save the extent of the current window so we can use this
 * at the end of the next RTT.
 */
vegas->beg_snd_nxt  = tp->snd_nxt;

/* We do the Vegas calculations only if we got enough RTT
 * samples that we can be reasonably sure that we got
 * at least one RTT sample that wasn't from a delayed ACK.
 * If we only had 2 samples total,
 * then that means we're getting only 1 ACK per RTT, which
 * means they're almost certainly delayed ACKs.
 * If  we have 3 samples, we should be OK.
 */

if (vegas->cntRTT <= 2) {
/* We don't have enough RTT samples to do the Vegas
 * calculation, so we'll behave like Reno.
 */
tcp_reno_cong_avoid(sk, ack, acked);
} else {
u32 rtt, diff;
u64 target_cwnd;

/* We have enough RTT samples, so, using the Vegas
 * algorithm, we determine if we should increase or
 * decrease cwnd, and by how much.
 */

/* Pluck out the RTT we are using for the Vegas
 * calculations. This is the min RTT seen during the
 * last RTT. Taking the min filters out the effects
 * of delayed ACKs, at the cost of noticing congestion
 * a bit later.
 */
rtt = vegas->minRTT;

/* Calculate the cwnd we should have, if we weren't
 * going too fast.
 *
 * This is:
 *     (actual rate in segments) * baseRTT
 */
target_cwnd = (u64)tp->snd_cwnd * vegas->baseRTT;
do_div(target_cwnd, rtt);

/* Calculate the difference between the window we had,
 * and the window we would like to have. This quantity
 * is the "Diff" from the Arizona Vegas papers.
 */
diff = tp->snd_cwnd * (rtt-vegas->baseRTT) / vegas->baseRTT;

if (diff > gamma && tp->snd_cwnd <= tp->snd_ssthresh) {
/* Going too fast. Time to slow down
 * and switch to congestion avoidance.
 */

/* Set cwnd to match the actual rate
 * exactly:
 *   cwnd = (actual rate) * baseRTT
 * Then we add 1 because the integer
 * truncation robs us of full link
 * utilization.
 */
tp->snd_cwnd = min(tp->snd_cwnd, (u32)target_cwnd+1);
tp->snd_ssthresh = tcp_vegas_ssthresh(tp);

} else if (tp->snd_cwnd <= tp->snd_ssthresh) {
/* Slow start.  */
tcp_slow_start(tp, acked);
} else {
/* Congestion avoidance. */

/* Figure out where we would like cwnd
 * to be.
 */
if (diff > beta) {
/* The old window was too fast, so
 * we slow down.
 */
tp->snd_cwnd--;
tp->snd_ssthresh
= tcp_vegas_ssthresh(tp);
} else if (diff < alpha) {
/* We don't have enough extra packets
 * in the network, so speed up.
 */
tp->snd_cwnd++;
} else {
/* Sending just as fast as we
 * should be.
 */
}
}

if (tp->snd_cwnd < 2)
tp->snd_cwnd = 2;
else if (tp->snd_cwnd > tp->snd_cwnd_clamp)
tp->snd_cwnd = tp->snd_cwnd_clamp;

tp->snd_ssthresh = tcp_current_ssthresh(sk);
}

/* Wipe the slate clean for the next RTT. */
vegas->cntRTT = 0;
vegas->minRTT = 0x7fffffff;
}
/* Use normal slow start */
else if (tp->snd_cwnd <= tp->snd_ssthresh)
tcp_slow_start(tp, acked);

}
