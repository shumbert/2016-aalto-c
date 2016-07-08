#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/source.h"

START_TEST(test_number_swap) {
    int a, b;

    for (int i = 0; i < 3; i++) {
        a = rand() % 100;
        b = rand() % 100;
        int a_temp = a;
        int b_temp = b;
        number_swap(&a, &b);
        fail_unless(a == b_temp && b == a_temp, "[Task 2.1] number_swap(a, b) called with *a = %d and *b = %d. Values after call are: a: %d (should be %d), b: %d (should be %d)",
                a_temp, b_temp, a, b_temp, b, a_temp);
    }
}

END_TEST


void print_array(char *buf, int *arr, int n)
{
    char b[8];
    strcpy(buf, "{ ");
    for (int i = 0; i < n; i++) {
        sprintf(b, "%d ", arr[i]);
        strcat(buf, b);
    }
    strcat(buf, "}");
}

START_TEST(test_array_sum) {
    int arr[8];
    for (int i = 0; i < 3; i++) {
        int len = rand() % 6 + 1;
        int mod = 0;
        for (int j = 0; j < len; j++) {
            arr[j] = rand() % 100;
            mod += arr[j];
        }
        int stu = array_sum(arr, len);
        char outbuf[100] = { 0 };
        print_array(outbuf, arr, len);
        fail_unless(stu == mod, "[Task 2.2] array_sum() called with array %s (length: %d). You returned: %d. Should have been: %d.",
                outbuf, len, stu, mod);
    }
}
END_TEST


START_TEST(test_array_reader) {
    char inp[200];
    int size = rand() % 10 + 5;
    inp[0] = 0;
    int s_arr[20];
    int ar1[20];
    int i, ret;
    for (i = 0; i < size; i++) {
        s_arr[i] = rand() % 100;
        char buf[10];
        sprintf(buf, "%d ", s_arr[i]);
        strcat(inp, buf);
    }
    strcat(inp, "f");

    FILE *mock_input = freopen("mockinput", "w+", stdin);
    fputs(inp, mock_input);
    fseek(mock_input, 0, SEEK_SET);

    memset(ar1, 0, sizeof (ar1));
    ret = array_reader(ar1, 20);

    fail_unless(ret == size, "[Task 2.3] Wrong return value with input \"%s\". You returned %d, expected %d\n",
            inp, ret, size);

    for (i = 0; i < size; i++) {
        fail_unless(ar1[i] == s_arr[i], "[Task 2.3] Wrong array member with input \"%s\". You had %d as %dth item, expected %d\n",
                inp, ar1[i], i + 1, s_arr[i]);
    }

    fail_unless(ar1[size] == 0, "[Task 2.3] You have written more than %d values to array, which was the length of user input\n",
            size);
}
END_TEST
    
    
int main(int argc, const char *argv[]) {
    srand((unsigned) time(NULL));
    Suite *s = suite_create("Test-02_basics");

    /* TODO: define tests */
    tmc_register_test(s, test_number_swap, "M2.02.1");
    tmc_register_test(s, test_array_sum, "M2.02.2");
    tmc_register_test(s, test_array_reader, "M2.02.3");
    return tmc_run_tests(argc, argv, s);
}
