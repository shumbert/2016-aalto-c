#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/source.h"


void makebuf(char *buf, char *src, unsigned int n)
{
    memset(buf, '?', n);
    strcpy(buf, src);
    buf[strlen(src)] = '?';
}

START_TEST(test_es_print)
{
    char buf[200];
   
    freopen("mockoutput", "w", stdout);
    char *test1 = "Foobar123nelja#viisibaz";
    makebuf(buf, test1, sizeof(buf));
    
    es_print(buf);
    fflush(stdout);
    FILE *fp = fopen("mockoutput", "r");
    char str [100] = { 0 };
    fgets(str, 100, fp);

    //char infostr[100] = "";
    char *mod = "Foobar123nelja";
    //int ret = mycompare(str, "Foobar123nelja", infostr);
    int ret = strcmp(str, mod);
    remove_nonascii(str);
    fail_unless(!ret, "[Task 2.9.a] Incorrect output with input \"%s\": should have been \"%s\", you gave \"%s\"\n",
            test1, mod, str);
    
    freopen("mockoutput", "w", stdout);
    char *test2 = "v#iisibazfoo";
    makebuf(buf, test2, sizeof(buf));
    es_print(buf);
    fflush(stdout);
    fp = fopen("mockoutput", "r");
    char str2 [100] = { 0 };
    fgets(str2, 100, fp);
    
    //infostr[0] = 0;
    //ret = mycompare(str2, "v", infostr);
    char *mod2 = "v";
    ret = strcmp(str2, mod2);
    remove_nonascii(str2);
    fail_unless(!ret, "[07_altstring.a] Incorrect output with input \"%s\": should have been \"%s\", you gave \"%s\"\n",
            test2, mod2, str2);
}
END_TEST

START_TEST(test_es_length)
{
	unsigned int ret;
        char buf[200];

        char *test1 = "Foobar123nelja#viisibaz";
        makebuf(buf, test1, sizeof(buf));
	ret = es_length(buf);
	fail_unless(ret == 14, "[07_altstring.b] Wrong length with string \"%s\". Got %d, expected 14\n",
                test1, ret);

        char *test2 = "#viisibazfoo";
        makebuf(buf, test2, sizeof(buf));
	ret = es_length(buf);
	fail_unless(ret == 0, "[07_altstring.b] Wrong length with string \"%s\". Got %d, expected 0\n",
                test2, ret);
}
END_TEST


START_TEST(test_es_copy)
{
	char buf[100];
	int ret;

        char *test1 = "Foobar123neljaa#viisibaz";
        char *ref1 = "Foobar123neljaa#";
	ret = es_copy(buf, test1);
	fail_unless(ret == 15, "[07_altstring.c] Wrong return value with string \"%s\". Got %d, expected 15\n",
                test1, ret);
        //char infostr[100] = "";
        //ret = myNcompare(buf, ref1, infostr, strlen(ref1));
        ret = memcmp(buf, ref1, strlen(ref1));
        buf[strlen(ref1)] = 0;
        remove_nonascii(buf);
	fail_unless(!ret, "[07_altstring.c] Copied string is incorrect with input \"%s\". Should have been \"%s\", you have \"%s\"",
                test1, ref1, buf);

        //infostr[0] = 0;
        char *test2 = "#viisibazfoo";
	ret = es_copy(buf, test2);
	fail_unless(ret == 0, "[07_altstring.c] Wrong return value with string \"%s\". Got %d, expected 0\n",
                test2, ret);
        char *ref2 = "#";
        //ret = myNcompare(buf, "#", infostr, 1);
        ret = memcmp(buf, ref2, strlen(ref2));
        buf[strlen(ref2)] = 0;
        remove_nonascii(buf);
        fail_unless(!ret, "[07_altstring.c] Copied string is incorrect with input \"%s\". Should have been \"%s\", you have \"%s\"",
                test2, ref2, buf);
}
END_TEST


START_TEST(test_es_token)
{
	char str1[] = "Foobarbaz#asd:w";
        char *ref1 = "Foobarbaz#";
	char str2[] = "Foobar:baz#asd:w";
        char *ref2 = "Foobar#baz#";
        char orig1[80], orig2[80];
	char *ret;
        int ret2;

        strcpy(orig1, str1);
        strcpy(orig2, str2);
	ret = es_token(str1, ':');
	fail_unless(ret == NULL, "[07_altstring.d] With string \"%s\" and token \':\' should have returned NULL. Remember that the end of the string here is marked with \'#\'",
                orig1);
        //char infostr[100] = "";
        //ret2 = myNcompare(str1, ref1, infostr, strlen(ref1));
        ret2 = memcmp(str1, ref1, strlen(ref1));
        str1[strlen(ref1)] = 0;
        remove_nonascii(str1);
	fail_unless(!ret2, "[07_altstring.d] Processed string is incorrect with input (\"%s\", ':'). Should have been \"%s\", you have \"%s\"",
                orig1, ref1, str1);

	ret = es_token(str2, ':');
	fail_unless(ret == &(str2[7]), "[07_altstring.d] Wrong return value with string \"%s\": Got %p, expected %p\n",
                orig2, ret, &(str2[7]));
        //infostr[0] = 0;
        //ret2 = myNcompare(str2, ref2, infostr, strlen(ref2));
        ret2 = memcmp(str2, ref2, strlen(ref2));
        str2[strlen(ref2)] = 0;
        remove_nonascii(str2);
        fail_unless(!ret2, "[07_altstring.d] Processed string is incorrect with input (\"%s\", ':'). Should have been \"%s\", you have \"%s\"",
                orig2, ref2, str2);
}
END_TEST


int main(int argc, const char *argv[])
{
	Suite *s = suite_create("Test-07_altstring");

	tmc_register_test(s, test_es_print, "M2.07.a");
	tmc_register_test(s, test_es_length, "M2.07.b");
	tmc_register_test(s, test_es_copy, "M2.07.c");
	tmc_register_test(s, test_es_token, "M2.07.d");
        
	return tmc_run_tests(argc, argv, s);
}
