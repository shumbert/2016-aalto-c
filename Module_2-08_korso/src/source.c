#include "source.h"


/* Korsoraattori
 */
void korsoroi(char *dest, const char *src)
{
    int words = 0;
    while (*src) {
        if (*src == ' ') {
            words++;

            *dest++ = ' ';
            if (words > 0 && (words % 3) == 0) {
                *dest++ = 'n';
                *dest++ = 'i';
                *dest++ = 'i';
                *dest++ = 'n';
                *dest++ = 'k';
                *dest++ = 'u';
                *dest++ = ' ';
            }

            if (words > 0 && (words % 4) == 0) {
                *dest++ = 't';
                *dest++ = 'o';
                *dest++ = 't';
                *dest++ = 'a';
                *dest++ = 'n';
                *dest++ = 'o';
                *dest++ = 'i';
                *dest++ = 'n';
                *dest++ = ' ';
            }

        } else if (*src == 'k') {
            if (*(src + 1) == 's') {
                *dest++ = 'x';
                src++;
            } else
                *dest++ = 'k';

        } else if (*src == 't') {
            if (*(src + 1) == 's') {
                *dest++ = 'z';
                src++;
            } else
                *dest++ = 't';

        } else
            *dest++ = *src;

        src++;
    }
    *dest = '\0';
}
