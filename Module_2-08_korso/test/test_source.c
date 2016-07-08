#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "../src/source.h"




START_TEST(test_korsoroi)
{
    char orig[4][200] = { "yksi auto valui itsekseen ilman kuljettajaa makea alas",
        "kaks",
        "sleeping now zzzz tststs good night"};
    
    char ref[4][200] = { "yxi auto valui niinku izexeen totanoin ilman kuljettajaa niinku makea alas",
        "kax",
        "sleeping now zzzz niinku zzz totanoin good night"};
    
    int count = 3;
    
    
    char *buffer = malloc(200);
    for (int i = 0; i < count; i++) {
        memset(buffer, '#', 200);
        buffer[0] = 0;
        korsoroi(buffer, orig[i]);
        buffer[199] = 0;
        char infostr[100];
        if (mycompare(buffer, ref[i], infostr)) {
            char out[600];
            sprintf(out, "[08_korso] Input string:\n%s\nYour output:\n%s\nReference output:\n%s\nReason: %s\n",
                orig[i], buffer, ref[i], infostr);
            free(buffer);
            fail("%s", out);
        }
    }
    free(buffer);
}
END_TEST


int main(int argc, const char *argv[])
{
    srand((unsigned)time(NULL));
    Suite *s = suite_create("Test-08_korso");

    tmc_register_test(s, test_korsoroi, "M2.08");
    
    return tmc_run_tests(argc, argv, s);
}
