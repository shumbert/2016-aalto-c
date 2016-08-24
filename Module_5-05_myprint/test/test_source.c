#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/myprint.h"

void create_str(int* numbers, char* str, char* check, int r) {
    char line[100];
    char n[3];
    memset(n, 0, 3);
    memset(line, 0, 100);
    strcat(line, "Printing ");
    sprintf(n, "%d", r);
    strcat(line, n);
    strcat(line, " numbers: ");
    char *starts[] = { "Printing now ", "This time I printed ", "Some numbers ", line };

    int i=rand()%4;
    strcat(str, starts[i]);
    strcat(check, starts[i]);
    for(i=0 ; i<r; i++){
        int t = rand()%100;
        numbers[i]=t;
        memset(n, 0, 3);
        sprintf(n, "%d", t);
        strcat(str, "& ");
        strcat(check, n);
        strcat(check, " ");
    }
    check[strlen(check)-1]=0;
    str[strlen(str)-1]=0;
}

START_TEST(test_myprint) {
    for(int n=0; n<3; n++){
        int* numbers = calloc(20, 4);
        char* str = calloc(100, 1);
        char* check = calloc(100, 1);

        int r = 5;
        create_str(numbers, str, check, r);

        FILE* f = freopen("mockoutput", "w", stdout);

        int count = myprint(str, numbers[0], numbers[1], numbers[2], numbers[3], numbers[4]);

        fflush(stdout);
        fclose(f);

        FILE *fp = fopen("mockoutput", "r");
        fseek(fp, 0, SEEK_END);
        int input_file_size = ftell(fp);
        rewind(fp);
        char *test = calloc(1, input_file_size+1);
        fread(test, 1, input_file_size, fp);

        int ret = strcmp(check, test);
        free(numbers);
        free(str);

        fail_unless(!ret, "[Task 5.5] Incorrect output with given print command, should have been \"%s\", you gave \"%s\"\n", check, test);
        free(test);
        free(check);
        fail_unless(count==5, "[Task 5.5] Incorrect return value with given print command, should have been %d, you gave %d\n", 5, count);
    }
    test_complete();
}
END_TEST

int main(int argc, const char *argv[]) {
    srand((unsigned) time(NULL));
    Suite *s = suite_create("Test-05_myprint");

    tmc_init_tests();
    
    tmc_register_test(s, test_myprint, "M5.05");

    return tmc_run_tests(argc, argv, s);
}
