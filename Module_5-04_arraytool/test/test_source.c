#include <check.h>
#include <assert.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/arraytool.h"

START_TEST(test_check)
{
#ifndef CHECK
    fail("[M5.04.a] Implement CHECK macro");
#else
    freopen("mockoutput", "w", stdout);
    CHECK(5 > 10, "Test-1");
    char stu[80];
    stu[0] = 0;
    read_stdout(stu, 80);
    if(strncmp(stu, "Test-1", 6)) {
        fail("[M5.04.a] CHECK(5 > 10, \"Test-1\") should output 'Test-1'");
    }
    
    stu[0] = 0;
    freopen("mockoutput", "w", stdout);
    CHECK(5 < 10, "Test-2");
    if (strlen(stu) > 0) {
        fail("[M5.04.a] CHECK(5 < 10, \"Test-2\") should not output anything");
    }
    
    for (int i = 3; i < 10; i++) {
        int val = rand() & 7;
        char buf[16];
        sprintf(buf, "Test-%d", i);
        stu[0] = 0;
        freopen("mockoutput", "w", stdout);
        CHECK(val & 1, buf);
        read_stdout(stu, 80);
        if ((val & 1) && (strlen(stu) > 0)) {
            fail("[M5.04.a] CHECK(val & 1, \"%s\") should not output anything, when val==%d",
                    buf, val);
        } else if(!(val & 1) && strncmp(stu, buf, 6)) {
            fail("[M5.04.a] CHECK(val & 1, \"%s\") should output '%s', when val==%d",
                    buf, buf, val);
        }
    }
    test_complete();
#endif
}
END_TEST


START_TEST(test_make_array)
{
#ifndef MAKE_ARRAY
    fail("[M5.04.b] Implement MAKE_ARRAY macro");
#else
    void *ptr1 = NULL;
    ptr1 = MAKE_ARRAY(int, 10);
    if (!ptr1) {
        fail("[M5.04.b] MAKE_ARRAY(int, 10) returned NULL pointer");
    }
    int *p1 = ptr1;
    for (int i = 0; i < 10; i++) {
        *p1++ = i;
    }
    free(ptr1);
    
    void *ptr2 = NULL;
    ptr2 = MAKE_ARRAY(double, 500);
       if (!ptr2) {
        fail("[M5.04.b] MAKE_ARRAY(double, 500) returned NULL pointer");
    }
    double *p2 = ptr2;
    for (int i = 0; i < 500; i++) {
        *p2++ = (double) i;
    }
    free(ptr2);
    test_complete();
#endif  
}
END_TEST

START_TEST(test_array_idx)
{
#ifndef MAKE_ARRAY
    fail("[M5.04.c] Implement MAKE_ARRAY macro");
#else
#ifndef ARRAY_IDX
    fail("[M5.04.c] Implement ARRAY_IDX macro");
#else
    
    void *ptr1 = NULL;
    ptr1 = MAKE_ARRAY(int, 10);
    if (!ptr1) {
        fail("[M5.04.c] MAKE_ARRAY(int, 10) returned NULL pointer");
    }
    for (int i = 0; i < 10; i++) {
        ARRAY_IDX(int, ptr1, i) = i;
    }
    int *p1 = ptr1;
    for (int i = 0; i < 10; i++) {
        if(*p1 != i || ARRAY_IDX(int, ptr1, i) != i) {
            free(ptr1);
            fail("[M5.04.c] ARRAY_IDX(int, ptr, %d) = %d did not modify array correctly.",
                    i, i);
        }
        p1++;
    }
    free(ptr1);

    void *ptr2 = NULL;
    ptr2 = MAKE_ARRAY(double, 500);
    if (!ptr2) {
        fail("[M5.04.c] MAKE_ARRAY(double, 500) returned NULL pointer");
    }
    for (int i = 0; i < 500; i++) {
        ARRAY_IDX(double, ptr2, i) = i;
    }
    double *p2 = ptr2;
    for (int i = 0; i < 500; i++) {
        if(*p2 != i || ARRAY_IDX(double, ptr2, i) != i) {
            free(ptr2);
            fail("[M5.04.c] ARRAY_IDX(int, ptr, %d) = %d did not modify array correctly.",
                    i, i);
        }
        p2++;
    }
    free(ptr2);
    test_complete();
    
#endif
#endif
}
END_TEST

int main(int argc, const char *argv[])
{
     srand((unsigned)time(NULL));
     Suite *s = suite_create("Test-04_arraytool");

     tmc_init_tests();
     
     tmc_register_test(s, test_check, "M5.04.a");
     tmc_register_test(s, test_make_array, "M5.04.b");
     tmc_register_test(s, test_array_idx, "M5.04.c");    
     
     return tmc_run_tests(argc, argv, s);
}
