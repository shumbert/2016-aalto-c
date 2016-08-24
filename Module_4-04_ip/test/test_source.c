#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include "../src/ipheader.h"


void print_packet(char *buffer, unsigned char *bytes, unsigned int n)
{
    char b[16];
    buffer[0] = 0;
    for (unsigned int i = 0; i < n; i++) {
        sprintf(b, "%02x ", bytes[i]);
        strcat(buffer, b);
    }
}

START_TEST(test_parseIp1)
{

    unsigned char bytes[] = {
        0x45, 0x26, 0x01, 0xd3, 0xda, 0x8d, 0x41, 0x02,
        0x40, 0x06, 0x8c, 0xd5, 0xc0, 0xa8, 0x01, 0x46,
        0x6c, 0xa0, 0xa3, 0x33 };
    char buffer[80];
    print_packet(buffer, bytes, sizeof(bytes));
    struct ipHeader sol = {
        4, // version
        20, // ihl
        9, // dscp
        2, // ecn
        467, // length
        55949, // id
        2, // flags
        258, // offset
        64, // time_to_live
        6, // protocol
        0x8cd5, // checksum (invalid)
        {192, 168, 1, 70}, // source IP
        {108, 160, 163, 51} // destination IP
    };
    struct ipHeader ans;
    parseIp(&ans, bytes);
    fail_unless(sol.version == ans.version, "[M4.04.a] Version field parsed incorrectly (you: %d, reference: %d).\nHeader: %s\n",
            ans.version, sol.version, buffer);
    fail_unless(sol.ihl == ans.ihl, "[M4.04.a] IHL field parsed incorrectly (you: %d, reference: %d).\nHeader: %s\n",
            ans.ihl, sol.ihl, buffer);
    fail_unless(sol.dscp == ans.dscp, "[M4.04.a] DSCP field parsed incorrectly (you: %d, reference: %d).\nHeader: %s\n",
            ans.dscp, sol.dscp, buffer);
    fail_unless(sol.ecn == ans.ecn, "[M4.04.a] ECN field parsed incorrectly (you: %d, reference: %d).\nHeader: %s\n",
            ans.ecn, sol.ecn, buffer);
    fail_unless(sol.time_to_live == ans.time_to_live, "[M4.04.a] Time-to-live field parsed incorrectly (you: %d, reference: %d).\nHeader: %s\n",
            ans.time_to_live, sol.time_to_live, buffer);
    fail_unless(sol.protocol == ans.protocol, "[M4.04.a] Protocol field parsed incorrectly (you: %d, reference: %d).\nHeader: %s\n",
            ans.protocol, sol.protocol, buffer);

}
END_TEST

int ip_compare(char *buf, unsigned char *sol_ip, unsigned char *ans_ip)
{
    if (memcmp(sol_ip, ans_ip, 4)) {
        sprintf(buf, "%d.%d.%d.%d, should be: %d.%d.%d.%d",
                ans_ip[0], ans_ip[1], ans_ip[2], ans_ip[3],
                sol_ip[0], sol_ip[1], sol_ip[2], sol_ip[3]);
        return 0;
    }
    return 1;
}

START_TEST(test_parseIp2)
{
    unsigned char bytes[] = {
        0x45, 0x29, 0x01, 0xd3, 0xda, 0x8d, 0x41, 0x03,
        0x40, 0x06, 0x8c, 0xd5, 0xc0, 0xa8, 0x01, 0x46,
        0x6c, 0xa0, 0xa3, 0x33 };
    struct ipHeader sol = {
        4, // version
        20, // ihl
        10, // dscp
        1, // ecn
        467, // length
        55949, // id
        2, // flags
        259, // offset
        64, // time_to_live
        6, // protocol
        0x8cd5, // checksum (invalid)
        {192, 168, 1, 70}, // source IP
        {108, 160, 163, 51} // destination IP
    };
    char buffer[80];
    print_packet(buffer, bytes, sizeof(bytes));
    
    struct ipHeader ans;
    parseIp(&ans, bytes);
    fail_unless(sol.length == ans.length, "[M4.04.b] Length field parsed incorrectly (you: %d, reference: %d).\nHeader: %s\n",
            ans.length, sol.length, buffer);
    fail_unless(sol.identification == ans.identification, "[M4.04.b] Identification field parsed incorrectly (you: %d, reference: %d).\nHeader: %s\n",
            ans.identification, sol.identification, buffer);
    fail_unless(sol.flags == ans.flags, "[M4.04.b] Flags field parsed incorrectly (you: %d, reference: %d).\nHeader: %s\n",
            ans.flags, sol.flags, buffer);
    fail_unless(sol.fragment_offset == ans.fragment_offset, "[M4.04.b] Fragment offset field parsed incorrectly (you: %d, reference: %d).\nHeader: %s\n",
            ans.fragment_offset, sol.fragment_offset, buffer);
    fail_unless(sol.header_checksum == ans.header_checksum, "[M4.04.b] Header checksum field parsed incorrectly (you: %d, reference: %d).\nHeader: %s\n",
            ans.header_checksum, sol.header_checksum, buffer);
    
    char outbuf[80];
    if (!ip_compare(outbuf, sol.source_ip, ans.source_ip)) {
        fail("[M4.04.b] Source IP field parsed incorrectly, you have: %s.\nHeader: %s.\n",
                outbuf, buffer);
    }
    if (!ip_compare(outbuf, sol.destination_ip, ans.destination_ip)) {
        fail("[M4.04.b] Destination IP field parsed incorrectly, you have: %s.\nHeader: %s.\n",
                outbuf, buffer);
    }


}
END_TEST


START_TEST(test_sendIp1)
{
    unsigned char bytes[] = {
        0x45, 0x29, 0x01, 0xd3, 0xda, 0x8d, 0x41, 0x03,
        0x40, 0x06, 0x8c, 0xd5, 0xc0, 0xa8, 0x01, 0x46,
        0x6c, 0xa0, 0xa3, 0x33 };
    struct ipHeader hdr = {
        4, // version
        20, // ihl
        10, // dscp
        1, // ecn
        467, // length
        55949, // id
        2, // flags
        259, // offset
        64, // time_to_live
        6, // protocol
        0x8cd5, // checksum (invalid)
        {192, 168, 1, 70}, // source IP
        {108, 160, 163, 51} // destination IP
    };

    unsigned char buf[20];
    memset(buf, 0, sizeof(buf));
    sendIp(buf, &hdr);
    fail_unless(buf[0] == bytes[0], "[M4.04.c] With version: %d, ihl: %d, octet[0] should be 0x%02x. You have 0x%02x.",
            hdr.version, hdr.ihl, bytes[0], buf[0]);
    fail_unless(buf[1] == bytes[1], "[M4.04.c] With DSCP: %d, ECN: %d, octet[1] should be 0x%02x. You have 0x%02x.",
            hdr.dscp, hdr.ecn, bytes[1], buf[1]);
    fail_unless(buf[4] == bytes[4], "[M4.04.c] With identification: %d, octet[4] should be 0x%02x. You have 0x%02x.",
            hdr.identification, bytes[4], buf[4]);
    fail_unless(buf[5] == bytes[5], "[M4.04.c] With identification: %d, octet[5] should be 0x%02x. You have 0x%02x.",
            hdr.identification, bytes[5], buf[5]);
    fail_unless(buf[8] == bytes[8], "[M4.04.c] With time-to-live: %d, octet[8] should be 0x%02x. You have 0x%02x.",
            hdr.time_to_live, bytes[8], buf[8]);
    fail_unless(buf[9] == bytes[9], "[M4.04.c] With protocol: %d, octet[9] should be 0x%02x. You have 0x%02x.",
            hdr.protocol, bytes[9], buf[9]);
    
}
END_TEST


int check_ip(char *buf, unsigned char *stud_ip, unsigned char *ref_ip, const char *ad_str)
{
    if (memcmp(stud_ip, ref_ip, 4)) {
        sprintf(buf, "%s address %d.%d.%d.%d has been stored incorrectly. You have: %d.%d.%d.%d. ",
                ad_str, ref_ip[0], ref_ip[1], ref_ip[2], ref_ip[3],
                stud_ip[0], stud_ip[1], stud_ip[2], stud_ip[3]);
        return 0;
    }
    return 1;
}

START_TEST(test_sendIp2)
{
        unsigned char bytes[] = {
        0x45, 0x00, 0x01, 0xd3, 0xda, 0x8d, 0x40, 0x00,
        0x40, 0x06, 0x8c, 0xd5, 0xc0, 0xa8, 0x01, 0x46,
        0x6c, 0xa0, 0xa3, 0x33 };
    struct ipHeader hdr = {
        4, // version
        20, // ihl
        0, // dscp
        0, // ecn
        467, // length
        55949, // id
        2, // flags
        0, // offset
        64, // time_to_live
        6, // protocol
        0x8cd5, // checksum (invalid)
        {192, 168, 1, 70}, // source IP
        {108, 160, 163, 51} // destination IP
    };

    unsigned char buf[20];
    memset(buf, 0, sizeof(buf));
    sendIp(buf, &hdr);
    fail_unless(buf[2] == bytes[2], "[M4.04.d] With total length: %d, octet[2] should be 0x%02x. You have: 0x%02x",
            hdr.length, bytes[2], buf[2]);
    fail_unless(buf[3] == bytes[3], "[M4.04.d] With total length: %d, octet[3] should be 0x%02x. You have: 0x%02x",
            hdr.length, bytes[3], buf[3]);    
    fail_unless(buf[6] == bytes[6], "[M4.04.d] With flags: %d, fragment offset: %d, octet[6] should be 0x%02x. You have: 0x%02x",
            hdr.flags, hdr.fragment_offset, bytes[6], buf[6]);
    fail_unless(buf[7] == bytes[7], "[M4.04.d] With fragment offset: %d, octet[7] should be 0x%02x. You have: 0x%02x.",
            hdr.fragment_offset, bytes[7], buf[7]);
    fail_unless(buf[10] == bytes[10], "[M4.04.d] With header checksum: %04x, octet[10] should be 0x%02x. You have: 0x%02x.",
            hdr.header_checksum, bytes[10], buf[10]);
    fail_unless(buf[11] == bytes[11], "[M4.04.d] With header checksum: %04x, octet[11] should be 0x%02x. You have: 0x%02x.",
            hdr.header_checksum, bytes[11], buf[11]);
    char msgbuf[80];
    if (!check_ip(msgbuf, &buf[12], &bytes[12], "source IP")) {
        fail("[M4.04.d] Starting from octet[12], %s", msgbuf);
    }
    if (!check_ip(msgbuf, &buf[16], &bytes[16], "destination IP")) {
        fail("[M4.04.d] Starting from octet[16], %s", msgbuf);
    }
    
/*    fail_unless(buf[12] == bytes[12], "[M4.04.d] Error in the first Source IP octet.");
    fail_unless(buf[13] == bytes[13], "[M4.04.d] Error in the second Source IP octet.");
    fail_unless(buf[14] == bytes[14], "[M4.04.d] Error in the third Source IP octet.");
    fail_unless(buf[15] == bytes[15], "[M4.04.d] Error in the fourth Source IP octet.");
    fail_unless(buf[16] == bytes[16], "[M4.04.d] Error in the first Destination IP octet.");
    fail_unless(buf[17] == bytes[17], "[M4.04.d] Error in the second Destination IP octet.");
    fail_unless(buf[18] == bytes[18], "[M4.04.d] Error in the third Destination IP octet.");
    fail_unless(buf[19] == bytes[19], "[M4.04.d] Error in the fourth Destination IP octet.");*/
    
}
END_TEST


int main(int argc, const char *argv[])
{
    	Suite *s = suite_create("Test-04_ip");

        /* TODO: define tests */
	tmc_register_test(s, test_parseIp1, "M4.04.a");
	tmc_register_test(s, test_parseIp2, "M4.04.b");
	tmc_register_test(s, test_sendIp1, "M4.04.c");
	tmc_register_test(s, test_sendIp2, "M4.04.d");
        
	return tmc_run_tests(argc, argv, s);
}
