#include <stdarg.h>
#include <stdio.h>
#include "myprint.h"

int myprint(const char *fmt, ...)
{
    char *ptr = (char *) fmt;
    int count = 0;
    va_list args;

    va_start(args, fmt);
    while (*ptr) {
        if (*ptr == '&') {
            printf("%d", va_arg(args, int));
            count++;
        } else
            printf("%c", *ptr);
        ptr++;
    }

    va_end(args);
    return count;
}
