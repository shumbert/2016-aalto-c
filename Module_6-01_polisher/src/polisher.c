#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "polisher.h"

/* Read given file <filename> to dynamically allocated memory.
 * Return pointer to the allocated memory with file content, or
 * NULL on errors.
 */
char *read_file(const char *filename)
{
    char *buf;
    int c;
    int read = 0;
    int size = 50;

    FILE *f = fopen(filename, "r");
    if (!f) {
        return NULL;
    }

    buf = calloc(size, sizeof(char));
    if (buf == NULL)
        return NULL;

    while ((c = fgetc(f)) != EOF) {
        buf[read++] = c; 
        if (read == size) {
            char *tmp = calloc(size + 50, sizeof(char));
            if (tmp == NULL) {
                free(buf);
                return NULL;
            }
            memcpy(tmp, buf, size);
            free(buf);
            buf = tmp;
            size += 50;
        }
    }
    buf[read] = '\0';

    return buf;
}


/* Remove C comments from the program stored in memory block <input>.
 * Returns pointer to code after removal of comments.
 * Calling code is responsible of freeing only the memory block returned by
 * the function.
 */
char *remove_comments(char *input)
{
    char *buf, *cur;
    int read = 0;
    int size = 50;
    int short_form = 0;
    int long_form = 0;

    buf = calloc(size, sizeof(char));
    if (buf == NULL)
        return NULL;
    cur = input;

    while (*cur) {
        if (short_form) {
            if (*cur == '\n')
                short_form = 0;
        } else if (long_form) {
            if (*cur == '*' && *(cur + 1) == '/') {
                cur++;
                long_form = 0;
            }
        } else {
            if (*cur == '/' && *(cur + 1) == '/') {
                short_form = 1;
                cur++;
            } else if (*cur == '/' && *(cur + 1) == '*') {
                long_form = 1;
                cur++;
            } else {
                buf[read++] = *cur; 
                if (read == size) {
                    char *tmp = calloc(size + 50, sizeof(char));
                    if (tmp == NULL) {
                        free(buf);
                        free(input);
                        return NULL;
                    }
                    memcpy(tmp, buf, size);
                    free(buf);
                    buf = tmp;
                    size += 50;
                }
            }
        }
        cur++;
    }

    free(input);
    return buf;
}

/* Indent the C-code at memory block <indent>. String <pad> represents
 * one block of indentation. Only opening curly braces '{' increase the
 * indentation level, and closing curly braces '}' decrease the indentation level.
 * Return the pointer to the code after modification.
 * Calling code is responsible of freeing only the memory block returned by
 * the function.
 */
char *indent(char *input, const char *pad)
{
    char *buf, *cur;
    int read = 0;
    int size = 50;
    int level = 0;

    buf = calloc(size, sizeof(char));
    if (buf == NULL)
        return NULL;
    cur = input;
    
    while (*cur) {
        if (*cur == '\n') {
            buf[read++] = *cur;
            if (read == size) {
                char *tmp = calloc(size + 50, sizeof(char));
                if (tmp == NULL) {
                    free(buf);
                    free(input);
                    return NULL;
                }
                memcpy(tmp, buf, size);
                free(buf);
                buf = tmp;
                size += 50;
            }
            cur++;
            while (*cur && *cur != '\n') {
                if (!isspace(*cur)) {
                    if (*cur == '}')
                        level--;

                    for (int i = 0; i < level; i++) {
                        if ((read + (int) strlen(pad)) >= size) {
                            size += 50;
                            buf = realloc(buf, size);
                            if (buf == NULL)
                                return NULL;
                        }
                        memcpy(buf + read, pad, strlen(pad));
                        read += strlen(pad);
                    }
                    break;
                }
                cur++;
            }
        } else {
            if (*cur == '{')
                level++;

            buf[read++] = *cur;
            if (read == size) {
                char *tmp = calloc(size + 50, sizeof(char));
                if (tmp == NULL) {
                    free(buf);
                    free(input);
                    return NULL;
                }
                memcpy(tmp, buf, size);
                free(buf);
                buf = tmp;
                size += 50;
            }
            cur++;
        }
    }

    free(input);
    return buf;
}
