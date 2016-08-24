#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/election.h"


START_TEST(test_read_votes)
{   
    struct votes* v = read_votes("votes.txt");
    for(int i=0; i<5; i++) {
        if(!strcmp(v[i].name, "Trump") && v[i].votes != 4) {
            free(v);
            fail("[M6.06.a] Trump should have 4 votes in this test, you had %d.", v[i].votes);
        } else if(!strcmp(v[i].name, "Clinton") && v[i].votes != 2) {
            free(v);
            fail("[M6.06.a] Clinton should have 2 votes in this test, you had %d.", v[i].votes);        
        } else if(!strcmp(v[i].name, "Sanders") && v[i].votes != 2) {
            free(v);
            fail("[M6.06.a] Sanders should have 2 votes in this test, you had %d.", v[i].votes);
        } else if(!strcmp(v[i].name, "Cruz") && v[i].votes != 1) {
            free(v);
            fail("[M6.06.a] Cruz should have 2 votes in this test, you had %d.", v[i].votes);   
        }
    }
    free(v);

    test_complete();
}
END_TEST

START_TEST(test_results)
{  
    struct votes* v = read_votes("votes.txt");
    char* check = "Trump: 4\nClinton: 2\nSanders: 2\nCruz: 1\n";

    FILE* f = freopen("mockoutput", "w", stdout);

    results(v);

    fflush(stdout);
    fclose(f);

    FILE *fp = fopen("mockoutput", "r");
    fseek(fp, 0, SEEK_END);
    int input_file_size = ftell(fp);
    rewind(fp);
    char *test = calloc(1, input_file_size+1);
    fread(test, 1, input_file_size, fp);
    fclose(fp);

    int ret = strcmp(check, test);
    fail_unless(!ret, "[Task 6.06.b] Incorrect output with given file, should have been \n\"%s\"\nyou gave \n\"%s\"\n", check, test);

    free(test);
    free(v);

    test_complete();
}
END_TEST

int main(int argc, const char *argv[])
{
    Suite *s = suite_create("Test-06_election");

    srand((unsigned)time(NULL));    
    
    tmc_init_tests();
    
    tmc_register_test(s, test_read_votes, "M6.06.a");
    tmc_register_test(s, test_results, "M6.06.b");

    return tmc_run_tests(argc, argv, s);
}
