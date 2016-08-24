#ifndef AALTO_GETOPT_H
#define AALTO_GETOPT_H

/* This structure is not sufficient. You will need to add field(s) to it
 * in order to pass the exercise.
 * Do not modify 'optchar' and 'next' fields, however, because the test assumes
 * that the options are stored as linked list.
 */
struct options {
    char optchar;   
    struct options *next;
};

struct options *get_options(int argc, char *argv[]);
void free_options(struct options *opt);
int is_option(struct options *opt, char optc);
char *get_optarg(struct options *opt, char optc);

#endif
