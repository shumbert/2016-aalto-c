#include <stddef.h>
#include <stdio.h>
#include "source.h"


/* Print string */
/* Parameters:
 * s: string to be printed */
void es_print(const char *s)
{
    int index = 0;
    while (s[index] != '#')
        printf("%c", s[index++]);
}

/* String length */
/* Parameters:
 * s: string to be evaluated
 * Returns: length of the string */
unsigned int es_length(const char *s)
{
    int index = 0;
    while (s[index] != '#')
        index++;
    return index;
}

/* String copy */
/* Parameters:
 * dst: buffer to which the new string is copied
 * src: original string
 * Returns: Number of characters copied
 */
int es_copy(char *dst, const char *src)
{
    int index = 0;
    while (src[index] != '#') {
        dst[index] = src[index];
        index++;
    }
    dst[index] = '#';
    return index;
}

/* String tokenizer */
/* Parameters:
 * s: string to be processed
 * c: character to be replaced by '#'
 * Returns: pointer to the character following the replaced character,
 *          NULL if end of string reached */
char *es_token(char *s, char c)
{
    int index = 0;
    while (s[index] != '#' && s[index] != c)
        index++;

    if (s[index] == c) {
        s[index] = '#';
        return s + index + 1;
    } else
        return NULL;
}
