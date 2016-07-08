#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "../src/source.h"


START_TEST(test_count_alpha)
{
    char str[20];
    for (int i = 0; i < 3; i++) {
        int count = 0;
        unsigned int len = rand() % 10 + 4;
        for (unsigned int j = 0; j < len; j++) {
            int c = rand() % 90 + 32;
            if (isalpha(c))
                count++;
            str[j] = c;
        }
        str[len] = 0;
        int stu = count_alpha(str);
        fail_unless(stu == count, "[Task 2.6] There are %d alpha characters in string '%s'. You returned: %d",
                count, str, stu);
    }
}
END_TEST


START_TEST(test_count_substr)
{
    char *str[] = { "one two one twotwo three", "abcdefghijk", "ttatamtammtammitammi", "a b a b b b c d" };
    char *sub[] = { "two", "kkk", "tammi", "b" };
    int ans[] = { 3, 0, 2, 4 };
    
    for (int i = 0; i < 4; i++) {
        int stu = count_substr(str[i], sub[i]);
        fail_unless(stu == ans[i],
                "[Task 2.7] count_substr(\"%s\", \"%s\") should have returned %d. You returned %d.",
                str[i], sub[i], ans[i], stu);
    }
}
END_TEST




int main(int argc, const char *argv[])
{
    srand((unsigned)time(NULL));
    Suite *s = suite_create("Test-06_strbasic");

    tmc_register_test(s, test_count_alpha, "M2.06.1");
    tmc_register_test(s, test_count_substr, "M2.06.2");
    
    return tmc_run_tests(argc, argv, s);
}
