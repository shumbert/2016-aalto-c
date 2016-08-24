#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include "../src/strarray.h"

START_TEST(test_init_array)
{
    char **arr = init_array();
    if (!arr) {
        fail("[M4.03.a] init_array returned NULL");
    }
    if (*arr != NULL) {
        fail("[M4.03.a] After initialization the first object should be NULL");
    }
    free_strings(arr);
}
END_TEST

void genstr(char str[][20], unsigned int num)
{
    for (unsigned int i = 0; i < num; i++) {
        unsigned int len = rand() % 6 + 3;
        unsigned int j = 0;
        for (j = 0; j < len; j++) {
            str[i][j] = rand() % 20 + 'A';
        }
        str[i][j] = 0;
    }
}

void printref(char *buf, char str[][20], unsigned int num)
{
    buf[0] = 0;
    for (unsigned int i = 0; i < num; i++) {
        char b2[20];
        sprintf(b2, "'%s'", str[i]);
        strcat(buf, b2);
        if (i < num - 1)
            strcat(buf, ",");
    }
}

START_TEST(test_add_string)
{
    char ref[10][20];
    const unsigned int num = 5;
    genstr(ref, num);
    
    char **arr = init_array();
    if (!arr) {
      fail("[M4.03.b] Implement init_array first");
    }
    for (unsigned int i = 0; i < num; i++) {
        char **a2 = add_string(arr, ref[i]);
        if (!a2) {
            free_strings(arr);
            fail("[M4.03.b] add_string(ptr, \"%s\") returned NULL",
                    ref[i]);
        }
	arr = a2;
    }
    
    char buf[200];
    printref(buf, ref, num);
    
    if (arr[num] != NULL) {
        free_strings(arr);
        fail("[M4.03.b] After adding %d strings, array member %d should be NULL",
                num, num);
    }
    
    for (unsigned int i = 0; i < num; i++) {
        if (arr[i] == NULL) {
            free_strings(arr);
            fail("[M4.03.b] After adding %d strings, array member %d is NULL, but it should point to string",
                    num, i);
        }
        if (strcmp(arr[i], ref[i])) {
            remove_nonascii(arr[i]);
            char buf2[200];
            sprintf(buf2, "[M4.03.b] After adding strings %s, array member %d is %s, should be %s",
                    buf, i, arr[i], ref[i]);
            free_strings(arr);
            fail(buf2);
        }
    }
    free_strings(arr);
}
END_TEST


START_TEST(test_make_lower)
{
    char strs[][4][20] = {{ "oNe", "TWO", "three", "Four" },
    { "ALPHA", "beta", "Gamma", "Theta" }};
    char ref[][4][20] = {{ "one", "two", "three", "four" },
    { "alpha", "beta", "gamma", "theta" }};

    const unsigned int num = 4;
    
    for (int k = 0; k < 2; k++) {
    char **arr = init_array();
    if(!arr) {
      fail("[M4.03.c] init_array returned NULL");
    }
    for (unsigned int i = 0; i < num; i++) {
        char **a2 = add_string(arr, strs[k][i]);
	if (!a2) {
	  free_strings(arr);
	  fail("[M4.03.c] add_string returned NULL");
	}
	arr = a2;
    }
    
    char buf[200];
    printref(buf, strs[k], num);
    
    make_lower(arr);
    
    for (unsigned int i = 0; i < num; i++) {
        if (strcmp(arr[i], ref[k][i])) {
            remove_nonascii(arr[i]);
            char buf2[200];
            sprintf(buf2, "[M4.03.c] After adding strings {%s}, array member %d is '%s', should be '%s'",
                    buf, i, arr[i], ref[k][i]);
            free_strings(arr);
            fail(buf2);
        }
    }
    free_strings(arr);
    }
}
END_TEST


START_TEST(test_sort_strings)
{
    char strs[][4][20] = {{ "oNe", "TWO", "three", "Four" },
    { "ALPHA", "beta", "Gamma", "Theta" }};
    char ref[][4][20] = {{ "Four", "TWO", "oNe", "three" },
    { "ALPHA", "Gamma", "Theta", "beta" }};
    
    const unsigned int num = 4;
    
    for (int k = 0; k < 2; k++) {
    char **arr = init_array();
    if(!arr) {
      fail("[M4.03.d] init_array returned NULL");
    }
    for (unsigned int i = 0; i < num; i++) {
        char **a2 = add_string(arr, strs[k][i]);
	if (!a2) {
	  free_strings(arr);
          fail("[M4.03.d] add_string returned NULL");
        }
	arr = a2;
    }
    
    char buf[200];
    printref(buf, strs[k], num);
    
    sort_strings(arr);
    
    for (unsigned int i = 0; i < num; i++) {
        if (strcmp(arr[i], ref[k][i])) {
            remove_nonascii(arr[i]);
            char buf2[200];
            sprintf(buf2, "[M4.03.d] After adding strings {%s}, array member %d is '%s', should be '%s'",
                    buf, i, arr[i], ref[k][i]);
            free_strings(arr);
            fail(buf2);
        }
    }
    free_strings(arr);
    }
}
END_TEST


int main(int argc, const char *argv[])
{
    	Suite *s = suite_create("Test-03_strarray");

        /* TODO: define tests */
	tmc_register_test(s, test_init_array, "M4.03.a");
	tmc_register_test(s, test_add_string, "M4.03.b");
        tmc_register_test(s, test_make_lower, "M4.03.c");
        tmc_register_test(s, test_sort_strings, "M4.03.d");
        
	return tmc_run_tests(argc, argv, s);
}
