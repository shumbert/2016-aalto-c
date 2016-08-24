#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/source.h"

void print_array(int *a, int c, char* s) {
    for(int i=0; i<c; i++)
        sprintf(s+strlen(s), "%d ", a[i]);
    s[strlen(s)-1]=0;
}

START_TEST(test_join_arrays) {
    int a = rand()%20+1, b = rand()%20+1, c = rand()%20+1;
    int *a1=calloc(sizeof(int),a), *a2=calloc(sizeof(int),b), *a3=calloc(sizeof(int),c);

    for(int i=0; i<a; i++)
        a1[i] = rand() % 100+1;

    for(int i=0; i<b; i++)
        a2[i] = rand() % 100+1;

    for(int i=0; i<c; i++)
        a3[i] = rand() % 100+1;

    int* joined = join_arrays(a, a1, b, a2, c, a3);

    for (int i = 0; i < a+b+c; i++) {
        if (i<a) {
            if(joined[i]!=a1[i]){
                char b1[200], b2[200], b3[200];
                memset(b1, 0, 200);
                memset(b2, 0, 200);
                memset(b3, 0, 200);
                print_array(a1, a, b1);
                print_array(a2, c, b2);
                print_array(a3, c, b3);
                fail("[M3.03] Wrong array member when given arrays were \n%s,\n%s\nand\n%s. \nYou had %d as %dth item, expected %d\n",
                        b1, b2, b3, joined[i], i + 1, a1[i]);
                free(joined);
                free(a1);
                free(a2);
                free(a3);
            }
        }
        else if (i>=a && i<a+b) {
            if(joined[i]!=a2[i-a]){
                char b1[200], b2[200], b3[200];
                memset(b1, 0, 200);
                memset(b2, 0, 200);
                memset(b3, 0, 200);
                print_array(a1, a, b1);
                print_array(a2, c, b2);
                print_array(a3, c, b3);
                fail("[M3.03] Wrong array member when given arrays were \n%s,\n%s\nand\n%s. \nYou had %d as %dth item, expected %d\n",
                        b1, b2, b3, joined[i], i + 1, a2[i-a]);
                free(joined);
                free(a1);
                free(a2);
                free(a3);
            }
        }
        else if (i>=b && i<a+b+c) {
            if(joined[i]!=a3[i-a-b]){
                char b1[200], b2[200], b3[200];
                memset(b1, 0, 200);
                memset(b2, 0, 200);
                memset(b3, 0, 200);
                print_array(a1, a, b1);
                print_array(a2, c, b2);
                print_array(a3, c, b3);
                fail("[M3.03] Wrong array member when given arrays were \n%s,\n%s\nand\n%s. \nYou had %d as %dth item, expected %d\n",
                        b1, b2, b3, joined[i], i + 1, a3[i-a-b]);
                free(joined);
                free(a1);
                free(a2);
                free(a3);
            }
        }
    }
    free(joined);
    free(a1);
    free(a2);
    free(a3);
}
END_TEST

int main(int argc, const char *argv[]) {
    srand((unsigned) time(NULL));
    Suite *s = suite_create("Test-03_join");

    tmc_register_test(s, test_join_arrays, "M3.03");

    return tmc_run_tests(argc, argv, s);
}
