#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/source.h"


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


START_TEST(test_mastermind) {
    int sol[3][6] = { { 2, 6, 6, 3, 5, 3}, {8, 3, 3, 7, 9, 8}, {0, 7, 5, 0, 9, 1}};

    int guess[3][6] = { {4, 5, 6, 1, 8, 9}, {8, 3, 3, 1, 1, 1}, {5, 2, 3, 6, 7, 4}};
    
    char *result[3] = { "-*+---", "+++---", "*---*-" };

    char *buffer = malloc(100);
    for (int i = 0; i < 3; i++) {
        memset(buffer, 0, 100);
        mastermind(sol[i], guess[i], buffer, 6);
        if (strcmp(buffer, result[i])) {
            char out[200], solstr[40], guestr[40];
            print_array(solstr, sol[i], 6);
            print_array(guestr, guess[i], 6);
            sprintf(out, "[03_mastermind] With solution: %s and guess: %s you produced: '%s'. Should have '%s'",
                    solstr, guestr, buffer, result[i]);
            free(buffer);
            fail("%s", out);
        }
    }
}
END_TEST
    
    
int main(int argc, const char *argv[]) {
    srand((unsigned) time(NULL));
    Suite *s = suite_create("Test-03_mastermind");

    /* TODO: define tests */
    tmc_register_test(s, test_mastermind, "M2.03");
    return tmc_run_tests(argc, argv, s);
}
