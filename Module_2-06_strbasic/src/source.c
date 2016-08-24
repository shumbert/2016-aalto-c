#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "source.h"


/* Count Alpha
 * Count number of alphabetic characters in the given string <str>,
 * and return the count
 */
int count_alpha(const char *str)
{
    int count = 0;
    while (*str) {
        if (isalpha((int) *str))
            count++;
        str++;
    }
    return count;
}


/* Count Substring
 * Count number of occurances of substring <sub> in string <str>,
 * and return the count.
 */
int count_substr(const char *str, const char *sub)
{
    char *current = (char *) str;
    int count = 0;
    while ((current = strstr(current, sub)) != NULL) {
        current = current + strlen(sub);
        count++;
    }
    return count;
}


