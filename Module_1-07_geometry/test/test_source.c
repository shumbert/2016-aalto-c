#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../src/source.h"

char *ref = 
"   1   2   3   4\n"
"   2   4   6   8\n"
"   3   6   9  12\n"
"   4   8  12  16\n"
"   5  10  15  20\n";

START_TEST(test_multi_table)
{
unsigned int xs = 4, ys = 5;
char stu[2048];
freopen("mockoutput", "w", stdout);
multi_table(xs, ys);
read_stdout(stu, 2048);

char infostr[100] = "";
if (mycompare(stu, ref, infostr)) {
fail("[Task 1.4] Called multi_table(%u, %u). Your output:\n%s\nReference output:\n%s\nReason: %s\n",
xs, ys, stu, ref, infostr);
}
}
END_TEST





// STUB goes here
START_TEST(test_draw_triangle) {
char stu[2048];
char *mod = "....#\n...##\n..###\n.####\n#####\n";
int size = 5;
freopen("mockoutput", "w", stdout);
draw_triangle(size);
read_stdout(stu, 2048);

char infostr[100] = "";
if (mycompare(stu, mod, infostr)) {
fail("[Task 1.5] Called draw_triangle(%d). Your output:\n%s\nReference output:\n%s\nReason: %s\n",
size, stu, mod, infostr);
}
}
END_TEST


START_TEST(test_draw_ball) {
char stu[2048];
char *mod = "...*...\n.*****.\n.*****.\n*******\n.*****.\n.*****.\n...*...\n";
int size = 3;
freopen("mockoutput", "w", stdout);
draw_ball(size);
read_stdout(stu, 2048);

char infostr[100] = "";
if (mycompare(stu, mod, infostr)) {
fail("[Task 1.6] Called draw_ball(%d). Your output:\n%s\nReference output:\n%s\nReason: %s\n",
size, stu, mod, infostr);
}
}
END_TEST

int main(int argc, const char *argv[]) {
    srand((unsigned) time(NULL));
    // huhuu!!
    Suite *s = suite_create("Test-07-geometry");

    tmc_register_test(s, test_multi_table, "M1.07.1");
    tmc_register_test(s, test_draw_triangle, "M1.07.2");
    tmc_register_test(s, test_draw_ball, "M1.07.3");

    return tmc_run_tests(argc, argv, s);
}
