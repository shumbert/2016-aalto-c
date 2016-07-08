#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "../src/source.h"



void pr_array(char *buf, int *arr, int n)
{
    char b[40];
    sprintf(buf, "{");
    while (n--) {
        sprintf(b, "%d", *arr++);
        if (n)
            strcat(b, ", ");
        strcat(buf, b);
    }
    strcat(buf, "}");
}

START_TEST(test_sort)
{
    int ar1_s[] = {65, 234, 676, 3, 98, 35, 297, 34, 12};
    int ar2_s[] = {5, 93, 4, 54, 2, 876, 11, 123};
    int ar1_sorted[] = {3, 12, 34, 35, 65, 98, 234, 297, 676};
    int ar2_sorted[] = {2, 4, 5, 11, 54, 93, 123, 876};
    int* ar1 = malloc(sizeof(ar1_s));
    int* ar2 = malloc(sizeof(ar2_s));
    memcpy(ar1, ar1_s, sizeof(ar1_s));
    memcpy(ar2, ar2_s, sizeof(ar2_s));

    int ok = 1, i;
    char obuf1[100], obuf2[100];

    sort(ar1, 9);
    sort(ar2, 8);

    for (i = 0; i < 9; i++) {
        if (ar1[i] != ar1_sorted[i]) {
            ok = 0;
            break;
        }
    }
    if (!ok) {
        pr_array(obuf1, ar1, 9);
        pr_array(obuf2, ar1_sorted, 9);
        fail("[04_sort] Array {65, 234, 676, 3, 98, 35, 297, 34, 12} not ordered correctly.\nYour array: %s.\nShould be: %s\n", obuf1, obuf2);
    }
    for (i = 0; i < 8; i++) {
        if (ar2[i] != ar2_sorted[i]) {
            ok = 0;
            break;
        }
    }
    if (!ok) {
        pr_array(obuf1, ar2, 8);
        pr_array(obuf2, ar2_sorted, 8);
        fail("[04_sort] Array {5, 93, 4, 54, 2, 876, 11, 123} not ordered correctly.\nYour array: %s.\nShould be: %s\n", obuf1, obuf2);
    }

    free(ar1);
    free(ar2);
}
END_TEST


int main(int argc, const char *argv[])
{
    srand((unsigned)time(NULL));
    Suite *s = suite_create("Test-04_sort");

    tmc_register_test(s, test_sort, "M2.04");

    return tmc_run_tests(argc, argv, s);
}
