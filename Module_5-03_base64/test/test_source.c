#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <ctype.h>
#include "../src/base64.h"



START_TEST(test_to_base64)
{
    const char *files[5] = { "nonexistent.txt", "oneline.txt", "simple.bin", "testi.txt" };
    int refvals[5] = { -1, 41, 41, 213 };
    
    unsigned int numtests = 4;
    
    for (unsigned int i = 0; i < numtests; i++) {
        int istest = 0;
        char srcfile[32];
        strcpy(srcfile, files[i]);
        int ret;
        if ((ret = to_base64("result", srcfile)) == -1) {
            sprintf(srcfile, "test/%s", files[i]);
            ret = to_base64("result", srcfile);
            istest = 1;
        }
        
        if (ret != refvals[i]) {
            fail("[M5.03.a] to_base64() for source file '%s' should return %d. You returned %d.",
                files[i], refvals[i], ret);
        }
        if (ret == -1)
                continue;
            
        FILE *fstu = fopen("result", "r");
        if (!fstu)
            fail("[M5.03.a] Could not open the destination file created by to_base64()");
        
        char reffile[32];
        if (istest)
            sprintf(reffile, "test/%s.ref", files[i]);
        else
            sprintf(reffile, "%s.ref", files[i]);
        FILE *fref = fopen(reffile, "r");
        if (!fref) {
            fclose(fstu);
            fail("[M5.03.a] Could not open the reference file '%s'", reffile);
        }
        
        int stu,ref,k = 0;
        do {
            stu = fgetc(fstu);
            ref = fgetc(fref);
            if (stu != ref) {
                fclose(fstu); fclose(fref);
                char outc = stu;
                if (!isprint((int)outc))
                    outc = '?';
                fail("[M5.03.a] to_base64 for source file '%s' -- Your file differs from reference at byte %d. You: '%c' (%02X), reference: '%c' (%02X)",
                        files[i], k + 1, outc, stu, ref, ref);
            }
            k++;
        } while (ref != EOF);
        fclose(fstu);
        fclose(fref);
    }
    test_complete();
}
END_TEST

START_TEST(test_from_base64)
{
    const char *files[5] = { "nonexistent.txt", "oneline.txt", "simple.bin", "testi.txt" };
    int refvals[5] = { -1, 56, 56, 288 };
    
    unsigned int numtests = 4;
    
    for (unsigned int i = 0; i < numtests; i++) {
        int istest = 0;
        char srcfile[32];
        sprintf(srcfile, "%s.ref", files[i]);
        int ret;
        if ((ret = from_base64("result", srcfile)) == -1) {
            sprintf(srcfile, "test/%s.ref", files[i]);
            ret = from_base64("result", srcfile);
            istest = 1;
        }
        
        if (ret != refvals[i]) {
            fail("[M5.03.b] from_base64() for source file '%s.ref' should return %d. You returned %d.",
                files[i], refvals[i], ret);
        }
        if (ret == -1)
                continue;
        FILE *fstu = fopen("result", "r");
        if (!fstu)
            fail("[M5.03.b] Could not open the destination file created by from_base64()");
        
        char reffile[32];
        if (istest)
            sprintf(reffile, "test/%s", files[i]);
        else
            sprintf(reffile, "%s", files[i]);
        FILE *fref = fopen(reffile, "r");
        if (!fref) {
            fclose(fstu);
            fail("[M5.03.b] Could not open the reference file '%s'", reffile);
        }
        
        int stu, ref, k = 0;
        do {
            stu = fgetc(fstu);
            ref = fgetc(fref);
	    if (stu == -1 && ref >= 0) {
		    fclose(fstu); fclose(fref);
		    char refc = ref;
		    if (!isprint((int)refc))
			    refc = '?';
		    fail("[M5.03.b] from_base64 for source file '%s.ref' -- Your file is too short at byte %d. Reference file has: '%c' (%02x)",
			 files[i], k + 1, refc, ref);
	    }
            if (stu != ref) {
                fclose(fstu); fclose(fref);
                char outc = stu;
                char refc = ref;
                if (!isprint((int)outc))
                    outc = '?';
                if (!isprint((int)refc))
                    refc = '?';                
                fail("[M5.03.b] from_base64 for source file '%s.ref' -- Your file differs from reference at byte %d. You: '%c' (%02x), reference: '%c' (%02x)",
                        files[i], k + 1, outc, stu, refc, ref);
            }
            k++;
        } while (ref != EOF);
        fclose(fstu);
        fclose(fref);     
    }
    test_complete();
}
END_TEST

int main(int argc, const char *argv[]) {
    srand((unsigned)time(NULL));
    Suite *s = suite_create("Test-03_base64");


    tmc_init_tests();
    
    tmc_register_test(s, test_to_base64, "M5.03.a");
    tmc_register_test(s, test_from_base64, "M5.03.b");    
    
    return tmc_run_tests(argc, argv, s);
}
