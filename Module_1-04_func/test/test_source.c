#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../src/source.h"


START_TEST(test_vectorlength)
{
    double ans[][4] = {{ 2, 5, 6, 8.0622577482985491 },
		       {0,0,0, 0 },
		       {0,2,0, 2 },
		       {0,0,3, 3 },
		       {0.01, 0.04, 0.05, 0.064807406984078608}};

    for (unsigned int i = 0; i < 5; i++) {
	double x = vectorlength(ans[i][0], ans[i][1], ans[i][2]);
	if (x != ans[i][3]) {
	    fail("[04_func] When calling vectorlength(%f,%f,%f), expecting return value %.17g. Got %.17g\n",
		 ans[i][0], ans[i][1], ans[i][2], ans[i][3], x);
	}
    }
}
END_TEST


int main(int argc, const char *argv[])
{
    srand((unsigned)time(NULL));
    Suite *s = suite_create("Test-04_func");

    tmc_register_test(s, test_vectorlength, "M1.04");

    return tmc_run_tests(argc, argv, s);
}
