#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/queue.h"
#include "../src/queuepriv.h"

struct stu {
    char *id;
    char *name;
};

const struct stu students[] = {
    {"123456", "Antti Ahkera" },
    {"234567", "Lasse Laiska" },
    {"777777", "Hubert Blaine Wolfeschlegelsteinhausenbergerdorff" },  // this is actual name, I googled!
    {"aaaaaaaaa", "Aku Ankka" },
    {"666666", "Dennis Ritchie" }
};

int check_queue(char *buf, unsigned int buflen, Queue *q, unsigned int checkidx,
        const char *id, const char *name, int last)
{
    if (!q->first) {
        sprintf(buf, "Queue->first is NULL, even though there should be members in queue");
       return 0;
    }
    if (!q->last) {
        sprintf(buf, "Queue->last is NULL, even though there should be members in queue");
        return 0;
    }
    struct student *s = q->first;
    if (!s) {
        sprintf(buf, "Queue should have at least %d members, but q->first is NULL",
                checkidx + 1);
        return 0;
    }
    unsigned int i = 0;
    while (checkidx - i) {
        if (!s->next) {
            sprintf(buf, "Queue should have at least %d members, but next pointer of member %d is NULL",
                    checkidx + 1, i);
            return 0;
        }
        s = s->next;
        i++;
    }
    if (last && q->last != s) {
        sprintf(buf, "The Queue->last pointer does not point to the last member");
        return 0;
    }
    if (s->name == name) {
        sprintf(buf, "Memory for name at queue member %d is not allocated dynamically",
                checkidx);
        return 0;
    }
    if (last && s->next) {
        sprintf(buf, "Queue member %d is last, but the next pointer is not NULL",
                checkidx);
        return 0;
    }
    if (s->id[6]) {
        sprintf(buf, "The student ID string at queue member %d does not have terminating NULL",
                checkidx);
        return 0;
    }
    if (id && strcmp(id, s->id)) {
        remove_nonascii(s->id);
        snprintf(buf, buflen, "The student ID at queue member %d is \"%s\", but expected \"%s\"",
                checkidx, s->id, id);
        return 0;
    }
    if (name && strcmp(name, s->name)) {
        remove_nonascii(s->name);
        snprintf(buf, buflen, "The student name at queue member %d is \"%s\", but expected \"%s\"",
                checkidx, s->name, name);
        return 0;
    }
    return 1;
}

void releaseall(Queue *q, int trystud)
{
    if (trystud)
        while(Queue_dequeue(q));
    struct student *s = q->first;
    while (s) {
        struct student *ds = s;
        s = s->next;
        if (ds->name)
            free(ds->name);
        free(ds);
    }
    free(q);
}

START_TEST(test_Queue_enqueue)
{
    Queue *q = Queue_init();
    unsigned int qlen = 0;
    for (unsigned int i = 0; i < sizeof(students) / sizeof(struct stu); i++) {
        int ret = Queue_enqueue(q, students[i].id, students[i].name);
        int expret;
        if (strlen(students[i].id) <= 6)
            expret = 1;
        else
            expret = 0;
        
        if (ret != expret) {
            releaseall(q, 0);
            fail("[M3.07.a] Queue_enqueue(q, \"%s\", \"%s\" returned %d, should have returned %d",
                    students[i].id, students[i].name, ret, expret);
        }
        char buf[200];
        int adjust = (ret == 0);  // cover for case when addition is rejected
        if (!check_queue(buf, sizeof(buf), q, qlen-adjust, students[i-adjust].id, students[i-adjust].name, 1)) {
            releaseall(q, 0);
            fail("[M3.07.a] %s", buf);
        }
        if (ret)
            qlen++;
    }
    releaseall(q, 0);
}
END_TEST


START_TEST(test_Queue_dequeue)
{
    Queue *q = Queue_init();
    unsigned int qlen = 0;
    for (unsigned int i = 0; i < sizeof(students) / sizeof(struct stu); i++) {
        int ret = Queue_enqueue(q, students[i].id, students[i].name);
        if (ret)
            qlen++;
    }
    if (!qlen) {
      releaseall(q, 0);
      fail("[M3.07.b] Implement Queue_enqueue first");
    }
    unsigned int i = 0, origqlen = qlen;
    while (qlen) {
        int ret = Queue_dequeue(q);
        if (!ret) {
            releaseall(q, 0);
            fail("[M3.07.b] Queue_dequeue should return nonzero when members in queue. You returned: %d",
                    ret);
        }
        char buf[200];
        while (i+1 < sizeof(students) / sizeof(struct stu) && strlen(students[i+1].id) > 6)
            i++;
        if (i + 1 < sizeof(students) / sizeof(struct stu) &&
            !check_queue(buf, sizeof(buf), q, 0, students[i+1].id, students[i+1].name, qlen == 1)) {
            releaseall(q, 0);
            fail("[M3.07.b] After %d dequeue calls: %s",
                    origqlen - qlen + 1, buf);
        }
        qlen--;
        i++;
    }
    if (q->first || q->last) {
        releaseall(q, 0);
        fail("[M3.07.b] After all members have been dequeued, first and last pointer should be NULL");
    }
    int ret = Queue_dequeue(q);
    if (ret) {
        releaseall(q, 0);
        fail("[M3.07.b] Queue_dequeue should return zero when queue is empty. You returned: %d",
                    ret);
    }
    free(q);
    q = NULL;
}
END_TEST

START_TEST(test_Queue_drop)
{
    Queue *q = Queue_init();
    for (unsigned int i = 0; i < sizeof(students) / sizeof(struct stu); i++) {
        Queue_enqueue(q, students[i].id, students[i].name);
    }
        
    struct {
        const char *drop;
        int expret;
        unsigned int checkidx;
        const char *checkid;
        int checklast;
    } tests[] = {
        { "aaaaaaaaaa", 0, 3, "666666", 1},
        { "234567", 1, 1, "777777", 0},
        { "666666", 1, 1, "777777", 1},
        { "123456", 1, 0, "777777", 1}
    };
 
    for (unsigned int i = 0; i < 4; i++) {
        int ret = Queue_drop(q, tests[i].drop);
        if (ret != tests[i].expret) {
            releaseall(q, 1);
            fail("[M3.07.c] When trying to drop item \"%s\", should return %d, you returned %d",
                tests[i].drop, tests[i].expret, ret);
        }
        char buf[200];
        if (!check_queue(buf, sizeof(buf), q, tests[i].checkidx, tests[i].checkid, NULL, tests[i].checklast)) {
            releaseall(q, 1);
            fail("[M3.07.c] After dropping item \"%s\": %s", tests[i].drop, buf);
        }
    }
    releaseall(q, 1);
}
END_TEST


int main(int argc, const char *argv[])
{

    srand((unsigned)time(NULL));
    Suite *s = suite_create("Test-07_queue");
    
    tmc_register_test(s, test_Queue_enqueue, "M3.07.a");
    tmc_register_test(s, test_Queue_dequeue, "M3.07.b");
    tmc_register_test(s, test_Queue_drop, "M3.07.c");
        
    return tmc_run_tests(argc, argv, s);
}
