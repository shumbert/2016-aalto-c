#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/getopt.h"

#define NumTries 3
#define MaxOpts 10

void randString(char *work, int len)
{
    for (int i = 0; i < len; i++) {
        char c = rand() % ('z' - 'a') + 'a';
        work[i] = c;
    }
    work[len] = 0;
}

void rand_cmdline(char *opts, char **optarg, char **args, int *argc)
{
    int n = (rand() & 7) + 2;
    int ac = 1;
    strcpy(args[0], "xxx");
    
    for (int i = 0; i < n; i++) {
        char c = 0;
        do {
            c = 'a' + (rand() % ('z' - 'a'));
            for (int j = 0; j < i; j++) {
                if (opts[j] == c)
                    c = 0;
            }
            opts[i] = c;
        } while(!c);
    }
    
    for (int i = 0; i < n; i++) {
        sprintf(args[ac], "-%c", opts[i]);
        
        if (rand() & 1) {
            ac++;
            randString(args[ac], 8);
            optarg[i] = args[ac];
        } else {
            optarg[i] = NULL;
        }
        ac++;
    }
    *argc = ac;
}

void print_cmdline(char *buf, int argc, char **argv)
{
    *buf = 0;
    for (int i = 0; i < argc; i++) {
        strcat(buf, argv[i]);
        strcat(buf, " ");
    }
}

START_TEST(test_get_options) {
    char argvec[MaxOpts * 2][20];
    char *args[MaxOpts * 2];
    int argc;
    char opts[MaxOpts] = { 0 };
    char *optarg[MaxOpts] = { NULL };
    
    for (int i = 0; i < NumTries; i++) {
        for (int j = 0; j < MaxOpts; j++) {
            opts[j] = 0;
            args[j*2] = argvec[j*2];
            args[j*2+1] = argvec[j*2+1];
        }
        rand_cmdline(opts, optarg, args, &argc);

        char cmdline[100];
        print_cmdline(cmdline, argc, args);
        
        struct options *opt = get_options(argc, args);
        if (!opt) {
            fail("[M6.02.a] get_options returned NULL");
        }

        struct options *orig = opt;
        for (int j = 0; j < MaxOpts; j++) {
            if (!opts[j])
                break;
            if (!opt) {
                free_options(orig);
                fail("[M6.02.a] Command line: \"%s\", premature NULL pointer at %d. member of linked list",
                        cmdline, j+1);
            }
            if (opt->optchar != opts[j]) {
                char oc[2] = { 0 };
                oc[0] = opt->optchar;
                remove_nonascii(oc);
                free_options(orig);
                fail("[M6.02.a] Command line: \"%s\", optchar member of structure is '%c' (%d), expected '%c'",
                        cmdline, oc[0], oc[0], opts[j]);
            }
            opt = opt->next;
        }
        free_options(orig);
    }
    test_complete();
}
END_TEST

START_TEST(test_get_optarg)
{
    char argvec[MaxOpts * 2][20];
    char *args[MaxOpts * 2];
    int argc;
    char opts[MaxOpts] = { 0 };
    char *optarg[MaxOpts] = { NULL };
    
    for (int i = 0; i < NumTries; i++) {
        for (int j = 0; j < MaxOpts; j++) {
            opts[j] = 0;
            args[j*2] = argvec[j*2];
            args[j*2+1] = argvec[j*2+1];
        }
        rand_cmdline(opts, optarg, args, &argc);

        char cmdline[100];
        print_cmdline(cmdline, argc, args);

        struct options *opt = get_options(argc, args);
        if (!opt) {
            fail("[M6.02.b] get_options returned NULL");
        }
        for (char tc = 'a'; tc <= 'z'; tc++) {
            int ret = is_option(opt, tc);
            int sol = 0;
            for (int i = 0; i < MaxOpts; i++) {
                if (opts[i] == tc) {
                    sol = 1;
                    break;
                }
            }
            if (ret != sol) {
                free_options(opt);
                fail("[M6.02.b] Command line: \"%s\", is_option(opt, '%c') returned %d, expected %d",
                        cmdline, tc, ret, sol);
            }
            
            char *ret2 = get_optarg(opt, tc);
            char *sol2 = NULL;
            for (int i = 0; i < MaxOpts; i++) {
                if (opts[i] == tc) {
                    sol2 = optarg[i];
                    break;
                }
            }
            if (!sol2 && ret2) {
                free_options(opt);
                fail("[M6.02.b] Command line: \"%s\", get_optarg(opt, '%c') returned non-null value, but expected NULL",
                        cmdline, tc);  
            }
            if (sol2 && !ret2) {
                free_options(opt);
                fail("[M6.02.b] Command line: \"%s\", get_optarg(opt, '%c') returned NULL, but expected non-null value",
                        cmdline, tc);                  
            }
            if (sol2 && strncmp(sol2, ret2, 20)) {
                remove_nonascii(ret2);
                free_options(opt);
                fail("[M6.02.b] Command line: \"%s\", get_optarg(opt, '%c') returned \"%s\", but expected \"%s\"",
                        cmdline, tc, ret2, sol2);                      
            }
        }
        free_options(opt);
    }
    test_complete();
}
END_TEST


int main(int argc, const char *argv[]) {
    srand((unsigned)time(NULL));
    Suite *s = suite_create("Test-02_parser");

    tmc_init_tests();
    
    tmc_register_test(s, test_get_options, "M6.02.a");
    tmc_register_test(s, test_get_optarg, "M6.02.b");

    return tmc_run_tests(argc, argv, s);
}
