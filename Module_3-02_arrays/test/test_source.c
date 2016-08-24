#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/source.h"


START_TEST(test_dyn_reader) {
    for (int j = 0; j < 3; j++) {
        char inp[200];
        int size = rand() % 10 + 5;
        inp[0] = 0;
        int s_arr[20];
        int i;
        for (i = 0; i < size; i++) {
            s_arr[i] = rand() % 100;
            char buf[10];
            sprintf(buf, "%d ", s_arr[i]);
            strcat(inp, buf);
        }

        FILE *mock_input = freopen("mockinput", "w+", stdin);
        fputs(inp, mock_input);
        fseek(mock_input, 0, SEEK_SET);

        int *res = dyn_reader(size);
        if (res == NULL) {
            fail("[M3.02.1] dyn_reader(%d) returned NULL. Should have returned pointer to the allocated array",
                    size);
        }

        for (i = 0; i < size; i++) {
            if (res[i] != s_arr[i]) {
                free(res);
                fail("[M3.02.1] Wrong array member with input \"%s\". You had %d as %dth item, expected %d\n",
                        inp, res[i], i + 1, s_arr[i]);
            }
        }
        free(res);
    }
}
END_TEST

START_TEST(test_add_to_array) {
    for (int j = 0; j < 3; j++) {
        int size = rand() % 10 + 5;
        int *arr = malloc(size * sizeof(int));
        memset(arr, 0, size * sizeof(int));
        
        int tt[20];
        for (int i = 0; i < size; i++) {
            tt[i] = rand() % 100;
	    int *orig = arr;
            arr = add_to_array(orig, size + i, tt[i]);
            if (!arr) {
	      free(orig);
                fail("[M3.02.2] add_to_array returned NULL. Should have returned a pointer to allocated array.");
            }
        }
        
        for (int i = 0; i < size; i++) {
            if (tt[i] != arr[i + size]) {
                free(arr);
                fail("[M3.02.2] array content incorrect after %dth add_to_array() call with value %d",
                        i+1, tt[i]);
            }
        }
	free(arr);
    }
}
END_TEST


int main(int argc, const char *argv[]) {
    srand((unsigned) time(NULL));
    Suite *s = suite_create("Test-02_arrays");

    tmc_register_test(s, test_dyn_reader, "M3.02.1");
    tmc_register_test(s, test_add_to_array, "M3.02.2");

    return tmc_run_tests(argc, argv, s);
}
