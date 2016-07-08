#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/source.h"

char* genstr()
{
    char *str = calloc(1, 50);
    unsigned int len = rand() % 6 + 3;
    unsigned int j = 0, n = 0;
    for(int i = 0; i<5; i++) {
        for (j = 0; j < len; j++) {
            str[n] = rand() % 10 + 'a';
            n++;
        }
        str[n] = ' ';
        n++;
    }
    n--;
    str[n] = '\0';
    return str;
}

char* genarr()
{
    char *str = calloc(1, 50);
    unsigned int n = 0;
    for(int i = 0; i<5; i++) {
        str[n] = rand() % 10 + 'a';
        n++;
    }
    n--;
    str[n] = '\0';
    return str;
}

START_TEST(test_print_strarray)
{
    char test1[500];
    char **arr = malloc(sizeof(char*)*5);

    memset(test1, 0, 500);

    srand(time(0));
    for(int i = 0; i<4; i++){
        arr[i]=genstr();
        sprintf(test1+strlen(test1), "%s", arr[i]);
        sprintf(test1+strlen(test1), "%c", '\n');
    }
    arr[4]=NULL;

    FILE* f = freopen("mockoutput", "w", stdout);

    print_strarray(arr);

    fflush(stdout);
    fclose(f);

    FILE *fp = fopen("mockoutput", "r");
    fseek(fp, 0, SEEK_END);
    int input_file_size = ftell(fp);
    rewind(fp);
    char *str = calloc(1, input_file_size+1);
    fread(str, 1, input_file_size, fp);

    int ret = strcmp(test1, str);
    remove_nonascii(str);
    fail_unless(!ret, "[Task 2.9.a] Incorrect output with given array, should have been \"%s\", you gave \"%s\"\n", test1, str);
    char** b = arr;
    while(*arr){
        free(*arr);
        arr++;
    }
    free(b);
    free(str);
}
END_TEST

START_TEST(test_str_to_strarray)
{
    char test1[500];
    char **arr = malloc(sizeof(char*)*5);
    char **test_arr = malloc(sizeof(char*)*5);
    for(int i=0; i<4; i++) {
        test_arr[i]=malloc(50);
        memset(test_arr[i], '#', 50);
    }
    test_arr[4]=(void*)0x42424242;

    memset(test1, 0, 500);

    srand(time(0));
    for(int i = 0; i<4; i++){
        arr[i]=genarr();
        sprintf(test1+strlen(test1), "%s", arr[i]);
        sprintf(test1+strlen(test1), "%c", ' ');
    }
    test1[strlen(test1)-1] = '\0'; // replace trailing ' '
    arr[4]=NULL;

    str_to_strarray(test1, test_arr);

    int ret = 0, n = 0;
    char** test_b = test_arr;
    char** b = arr;
    for (n = 0; n < 4; ++n) {
        fail_unless(*test_arr != NULL, "[Task 2.9.b] The pointer in the output array at index %d should not be NULL\n", n);
        ret = strcmp(*test_arr, *arr);
        remove_nonascii(*test_arr);
        remove_nonascii(*arr);
        fail_unless(!ret, "[Task 2.9.b] Incorrect output with given string, %d. string in array should have been \"%s\", you gave \"%s\"\n", n, *arr, *test_arr);
        test_arr++;
        arr++;
    }
    fail_unless(*test_arr == NULL, "[Task 2.9.b] The last pointer in the output array at index %d should be NULL\n", n);
    test_arr = test_b;
    arr = b;
    while(*test_arr){
        free(*test_arr);
        test_arr++;
    }
    while(*arr){
        free(*arr);
        arr++;
    }
    free(test_b);
    free(b);
}
END_TEST

int main(int argc, const char *argv[])
{
    Suite *s = suite_create("Test-09_stringarray");

    tmc_register_test(s, test_print_strarray, "M2.09.a");
    tmc_register_test(s, test_str_to_strarray, "M2.09.b");

    return tmc_run_tests(argc, argv, s);
}
