#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../src/source.h"


START_TEST(test_simple_sum)
{
     FILE *mock_input = freopen("mockinput", "w+", stdin);
     fputs("6 8", mock_input);
     fseek(mock_input, 0, SEEK_SET);
     freopen("mockoutput", "w", stdout);
     simple_sum();
     fflush(stdout);
     FILE *fp = fopen("mockoutput", "r");
     char str [100];
     memset(str, 0, sizeof(str));
     fgets(str, 100, fp);
     char *ref = "6 + 8 = 14\n";
     char infostr[1000] = "";
     int ret = mycompare(str, ref, infostr);
     fail_unless(!ret, "[Task 1.2] When giving input \"6 8\", your output:\n%s\nReference output:\n%s\nReason: %s\n",
            str, ref, infostr);
     fclose(fp);

     mock_input = freopen("mockinput", "w+", stdin);
     fputs("10200 20031", mock_input);
     fseek(mock_input, 0, SEEK_SET);
     freopen("mockoutput", "w", stdout);
     simple_sum();
     fflush(stdout);
     fp = fopen("mockoutput", "r");
     memset(str, 0, sizeof(str));
     fgets(str, 100, fp);
     ref = "10200 + 20031 = 30231\n";
     infostr[0] = 0;
     ret = mycompare(str, ref, infostr);
     fail_unless(!ret, "[Task 1.2] When giving input \"10200 20031\", your output:\n%s\nReference output:\n%s\nReason: %s\n",
            str, ref, infostr);
     fclose(fp);
}
END_TEST


struct t13_st {
    float a;
    char op;
    float b;
    char res[16];
};

void simple_math_helper2(float a, char op, float b, char *res)
{
    char inp[100];
    sprintf(inp, "%.1f %c %.1f", a, op, b);
    FILE *mock_input = freopen("mockinput", "w+", stdin);
    fputs(inp, mock_input);
    fseek(mock_input, 0, SEEK_SET);
    
    freopen("mockoutput", "w", stdout);
    simple_math();
    fflush(stdout);

    FILE *fp = fopen("mockoutput", "r");
    fgets(res, 99, fp);
    fclose(fp);
    remove_newline(res);
}


START_TEST(test_simple_math)
{
struct t13_st ts[5] =
{{ 1.5, '+', 2.4, "3.9" },
{ 4.3, '-', 0.2, "4.1" },
{ 2.0, '*', 1.2, "2.4" },
{ 5.0, '/', 2.0, "2.5" },
{ 1.0, 'l', 2.0, "ERR" }};

for (int i = 0; i < 5; i++) {
char stu[100];
memset(stu, 0, 100);
simple_math_helper2(ts[i].a, ts[i].op, ts[i].b, stu);

if (strcmp(stu, ts[i].res)) {
fail("[Task 1.3] With input \"%.1f %c %.1f\" your function printed '%s'. Should have printed '%s'",
ts[i].a, ts[i].op, ts[i].b, stu, ts[i].res);
}
}
}
END_TEST




int main(int argc, const char *argv[])
{
    srand((unsigned)time(NULL));
    Suite *s = suite_create("Test-05-calc");

    tmc_register_test(s, test_simple_sum, "M1.05.1");
    tmc_register_test(s, test_simple_math, "M1.05.2");

    return tmc_run_tests(argc, argv, s);
}
