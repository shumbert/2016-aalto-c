#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "fileread.h"

/* Prints the given file as text on the screen.
 * Only printable characters are shown. Non-printable characters are printed
 * as '?'. <filename> parameter is the name of the file.
 * 
 * Returns the number of characters read
 */
int textdump(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f) {
        return -1;
    }

    int c;
    int count = 0;
    while ((c = fgetc(f)) != EOF) {
        count++;
        if (isprint(c))
            printf("%c", c);
        else
            printf("?");
    }

    fclose(f);
    return count;
}


/* Prints the given file as hexdump, at most 16 numbers per line.
 * <filename> parameter is the name of the file.
 * 
 * Returns the number of characters read
 */
int hexdump(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f) {
        return -1;
    }

    int c;
    int count = 0;
    while ((c = fgetc(f)) != EOF) {
        printf("%02x ", c);
        count++;
        if (count % 16 == 0)
            printf("\n");
    }

    fclose(f);
    return count;
}
