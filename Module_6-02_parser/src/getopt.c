#include <ctype.h>
#include <stdlib.h>
#include <string.h>
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
    struct options *head = NULL;
    struct options *previous = NULL;
    struct options *current = NULL;

    for (int i = 1; i < argc; i++) {
        if (strlen(argv[i]) == 2 && argv[i][0] == '-' && isalpha(argv[i][1])) {
            previous = current;

            current = malloc(sizeof(struct options));
            if (current == NULL) {
                free(head);
                return(NULL);
            }

            current->optchar = argv[i][1];
            current->next = NULL;
            if ((i + 1) < argc && argv[i + 1][0] != '-') {
                i++;
                current->argument = malloc(strlen(argv[i]) + 1);
                if (current->argument == NULL) {
                    free(head);
                    return(NULL);
                }
                strncpy(current->argument, argv[i], strlen(argv[i]) + 1);
            } else
                current->argument = NULL;

            if (previous != NULL)
                previous->next = current;
            if (head == NULL)
                head = current;
        }
    }

    return head;
}

/* a) Free the memory allocated for the linked list at <opt>.
 */
void free_options(struct options *opt)
{
    while (opt) {
        struct options *tmp = opt;
        if (opt->argument)
            free(opt->argument);
        opt = opt->next;
        free(tmp);
    }
}

/* b) Returns non-zero if option character <optc> is included in the
 * linked list pointed by <opt>
 */
int is_option(struct options *opt, char optc)
{
    while (opt) {
        if (opt->optchar == optc)
            return 1;
        opt = opt->next;
    }
    return 0;
}

/* b) Returns the argument given with option <optc>. If argument or
 * the option was not given, the function returns NULL.
 */
char *get_optarg(struct options *opt, char optc)
{
    while (opt) {
        if (opt->optchar == optc) {
            if (opt->argument)
                return opt->argument;
            else
                return NULL;
        }
        opt = opt->next;
    }
    return NULL;
}
