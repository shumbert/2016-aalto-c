#include <stdlib.h>
#include "getopt.h"


/* a) Returns the list of options given on command line arguments
 * indicated in <argc> and <argv>. These parameters are used similarly as
 * in the main function.
 * 
 * Function returns pointer to the start of linked list that contains the
 * options.
 */
struct options *get_options(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    return NULL;
}

/* a) Free the memory allocated for the linked list at <opt>.
 */
void free_options(struct options *opt)
{
    (void) opt;
}

/* b) Returns non-zero if option character <optc> is included in the
 * linked list pointed by <opt>
 */
int is_option(struct options *opt, char optc)
{
    (void) opt;
    (void) optc;
    return 0;
}

/* b) Returns the argument given with option <optc>. If argument or
 * the option was not given, the function returns NULL.
 */
char *get_optarg(struct options *opt, char optc)
{
    (void) opt;
    (void) optc;
    return NULL;
}
