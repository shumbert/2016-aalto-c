#include <ctype.h>
#include <stdio.h>
#include "filestats.h"


/* Returns the line count in given file
 * 
 * Parameters:
 * filename: name of the file to be investigated.
 * 
 * Returns:
 * The number of lines in file. */
int line_count(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f) {
        return -1;
    }

    int c;
    int count = 0;
    int emptyLine = 1;
    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') {
            count++;
            emptyLine = 1;
        } else if (emptyLine == 1)
            emptyLine = 0;
    }

    if (!emptyLine)
        count++;

    fclose(f);
    return count;
}


/* Count the number of words in the file. Word has to include at least one
 * alphabetic character, and words are separated by whitespace.
 * 
 * Parameters:
 * filename: name of the file to be investigated.
 * 
 * Returns:
 * number of words in the file */
int word_count(const char *filename)
{
   FILE *f = fopen(filename, "r");
    if (!f) {
        return -1;
    }

    int c;
    int count = 0;
    int isWord = 0;
    while ((c = fgetc(f)) != EOF) {
        if (isspace(c)) {
            if (isWord) {
                count++;
                isWord = 0;
            }
        } else if (isalpha(c)) {
            isWord = 1;
        }
    }
    if (isWord)
        count++;

    fclose(f);
    return count;
}
