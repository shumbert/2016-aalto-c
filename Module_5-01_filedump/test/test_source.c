#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>
#include "../src/fileread.h"

START_TEST(test_textdump)
{
    char *files[] = { "nonexistent.txt", "empty.txt", "oneline.txt", "simple.bin", "testi.txt" };
    int refvals[] = { -1, 0, 41, 41, 213 };
    char *refouts[] = {
        "", "", "This file has text only on one line. Wow.",
        "?Teemu Teekkari00000A???ELEC-A1100???????",
        "#include <stdio.h>?#include \"fileread.h\"??int main(void)?{?    if (textdump(\"main.c\") == -1) {?        if (textdump(\"src/main.c\") == -1) {?            fprintf(stderr, \"Could not open main.c\\n\");?        }?    }?}?"
    };
    
    char buf[40];
    char stu[2048];
    int ret;
    for (int i = 0; i < 5; i++) {
        strcpy(buf, files[i]);
        freopen("mockoutput", "w", stdout);
        ret = textdump(buf);
        if (ret == -1) {
            strcpy(buf, "test/");
            strcat(buf, files[i]);
            ret = textdump(buf);
        }
        
        fail_unless(ret == refvals[i], "[M5.01.a] textdump(\"%s\") should return %d. You returned %d.",
                files[i], refvals[i], ret);
        
        read_stdout(stu, 2048);
        char infostr[100] = "";
        if (ret != -1 && mycompare(stu, refouts[i], infostr)) {
            remove_nonascii(stu);
            fail("[M5.01.a] Called textdump(\"%s\"). Your output:\n%s\nReference output:\n%s\nReason: %s\n",
                    files[i], stu, refouts[i], infostr);
        }
    }
    test_complete();
}
END_TEST


START_TEST(test_hexdump)
{
    char *files[] = { "nonexistent.txt", "empty.txt", "oneline.txt", "simple.bin", "testi.txt" };
    int refvals[] = { -1, 0, 41, 41, 213 };
    char *refouts[] = {
        "", "",
        "54 68 69 73 20 66 69 6c 65 20 68 61 73 20 74 65 \n78 74 20 6f 6e 6c 79 20 6f 6e 20 6f 6e 65 20 6c \n69 6e 65 2e 20 57 6f 77 2e ",
        "0e 54 65 65 6d 75 20 54 65 65 6b 6b 61 72 69 30 \n30 30 30 30 41 00 00 14 45 4c 45 43 2d 41 31 31 \n30 30 00 00 00 00 00 00 00 ",
        "23 69 6e 63 6c 75 64 65 20 3c 73 74 64 69 6f 2e \n68 3e 0a 23 69 6e 63 6c 75 64 65 20 22 66 69 6c \n65 72 65 61 64 2e 68 22 0a 0a 69 6e 74 20 6d 61 \n69 6e 28 76 6f 69 64 29 0a 7b 0a 20 20 20 20 69 \n66 20 28 74 65 78 74 64 75 6d 70 28 22 6d 61 69 \n6e 2e 63 22 29 20 3d 3d 20 2d 31 29 20 7b 0a 20 \n20 20 20 20 20 20 20 69 66 20 28 74 65 78 74 64 \n75 6d 70 28 22 73 72 63 2f 6d 61 69 6e 2e 63 22 \n29 20 3d 3d 20 2d 31 29 20 7b 0a 20 20 20 20 20 \n20 20 20 20 20 20 20 66 70 72 69 6e 74 66 28 73 \n74 64 65 72 72 2c 20 22 43 6f 75 6c 64 20 6e 6f \n74 20 6f 70 65 6e 20 6d 61 69 6e 2e 63 5c 6e 22 \n29 3b 0a 20 20 20 20 20 20 20 20 7d 0a 20 20 20 \n20 7d 0a 7d 0a " 
    };
    
    char buf[40];
    char stu[2048];
    int ret;
    for (int i = 0; i < 5; i++) {
        strcpy(buf, files[i]);
        freopen("mockoutput", "w", stdout);
        ret = hexdump(buf);
        if (ret == -1) {
            strcpy(buf, "test/");
            strcat(buf, files[i]);
            ret = hexdump(buf);
        }
        
        fail_unless(ret == refvals[i], "[M5.01.b] hexdump(\"%s\") should return %d. You returned %d.",
                files[i], refvals[i], ret);
        
        read_stdout(stu, 2048);
        char infostr[100] = "";
        if (ret != -1 && mycompare(stu, refouts[i], infostr)) {
            remove_nonascii(stu);
            fail("[M5.01.b] Called hexdump(\"%s\"). Your output:\n%s\nReference output:\n%s\nReason: %s\n",
                    files[i], stu, refouts[i], infostr);
        }
    }
    test_complete();
}
END_TEST


int main(int argc, const char *argv[]) {
    Suite *s = suite_create("Test-01_filedump");

    tmc_init_tests();
    
    tmc_register_test(s, test_textdump, "M5.01.a");
    tmc_register_test(s, test_hexdump, "M5.01.b");    

    return tmc_run_tests(argc, argv, s);
}
