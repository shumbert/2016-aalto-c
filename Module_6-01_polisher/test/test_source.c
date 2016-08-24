#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/polisher.h"

static const char *refstr = 
"// This is a test file\n"
"int main(void) {\n"
"/* comment\n"
"block */\n"
"printf(\"juu\\n\");\n"
"while (1)\n"
"{\n"
"// Another comment\n"
"while (2) {\n"
"printf(\"jaa\\n\");\n"
"}\n"
"}\n"
"}\n";

#define OUTPUTLEN 400


START_TEST(test_read_file)
{
    char *str;
    str = read_file("testifile.c");
    if (!str) str = read_file("test/testifile.c");
    if (!str) {
        fail("[M6.01.a] read_file(\"testifile.c\") returned NULL");
    }
    char buf[OUTPUTLEN];
    if (mycompare_new(str, refstr, buf, OUTPUTLEN)) {
        free(str);
        fail("[M6.01.a] Invalid string from read_file(\"testifile.c\"): %s", buf);
    }
    free(str);
    
    test_complete();
}
END_TEST

static const char *ref61b = 
"int main(void) {\n"
"\n"
"printf(\"juu\\n\");\n"
"while (1)\n"
"{\n"
"while (2) {\n"
"printf(\"jaa\\n\");\n"
"}\n"
"}\n"
"}\n";

START_TEST(test_remove_comments)
{
    char *str = read_file("testifile.c");
    if (!str) str = read_file("test/testifile.c");
    if (!str) {
        fail("[M6.01.b] read_file(\"testifile.c\") returned NULL");
    }
    char *res = remove_comments(str);
    if (!res) {
        free(str);
        fail("[M6.01.b] remove_comments(\"testifile.c\") returned NULL");
    }
    
    char buf[OUTPUTLEN];
    if (mycompare_new(res, ref61b, buf, OUTPUTLEN)) {
        free(res);
        fail("[M6.01.b] Invalid string from remove_comments(\"testifile.c\"): %s", buf);
    }
    
    free(res);
    
    test_complete();
}
END_TEST

static const char *ref61c = 
"// This is a test file\n"
"int main(void) {\n"
"    /* comment\n"
"    block */\n"
"    printf(\"juu\\n\");\n"
"    while (1)\n"
"    {\n"
"        // Another comment\n"
"        while (2) {\n"
"            printf(\"jaa\\n\");\n"
"        }\n"
"    }\n"
"}\n";

START_TEST(test_indent)
{
    char *str = read_file("testifile.c");
    if (!str) str = read_file("test/testifile.c");
    if (!str) {
        fail("[M6.01.c] read_file(\"testifile.c\") returned NULL");
    }
    char *res = indent(str, "    ");
    if (!res) {
        free(str);
        fail("[M6.01.c] indent(\"testifile.c\") returned NULL");
    }
    
    char buf[OUTPUTLEN];
    if (mycompare_new(res, ref61c, buf, OUTPUTLEN)) {
        free(res);
        fail("[M6.01.c] Invalid string from indent(\"testifile.c\"): %s", buf);
    }
    
    free(res);
    
    test_complete();
}
END_TEST

int main(int argc, const char *argv[]) {
    srand((unsigned)time(NULL));
    Suite *s = suite_create("Test-01_polisher");

    tmc_init_tests();
    
    tmc_register_test(s, test_read_file, "M6.01.a");
    tmc_register_test(s, test_remove_comments, "M6.01.b");
    tmc_register_test(s, test_indent, "M6.01.c");

    return tmc_run_tests(argc, argv, s);
}
