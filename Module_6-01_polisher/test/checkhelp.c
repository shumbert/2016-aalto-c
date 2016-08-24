#include <string.h>
#include <stdio.h>
#include <ctype.h>

// Sometimes Netbeans TMC plugin pukes when it gets non-ASCII characters
// in test output. Trying to avoid that
void remove_nonascii(char *str)
{
    while (*str) {
      if (*str & 0x80 || (!isspace((int)*str) && *str < 32))
            *str = '?';
        str++;
    }
}


void printchar(char *buf, char c)
{
    if (c == '\n') {
        strcpy(buf, "\\n");
    } else if (c & 0x80) {
        strcpy(buf, "(invalid)");
    } else {
        *buf++ = c;
        *buf = 0;
    }
}

int mycompare(const char *student, const char *model, char *infostr)
{
    int i = 0, line = 1;
    char bufS[16] = { 0 };
    char bufM[16] = { 0 };
    while(*student) {
        printchar(bufS, *student);
        printchar(bufM, *model);
        if (!(*model)) {
            sprintf(infostr, "your output is longer than expected: character: '%s', position: %d, line: %d\n",
                    bufS, i+1, line);
            return -1;
        }
        if (*student != *model) {
            sprintf(infostr, "position: %d, line: %d, your output: '%s' , expected: '%s'\n", 
                    i+1, line, bufS, bufM);
            return -1;
        }
        if (*student == '\n') {
            line++;
            i = -1;
        }
        student++; model++; i++;
    }
    if (*model) {
        printchar(bufM, *model);
        sprintf(infostr, "output correct until position: %d, line: %d, but shorter than expected. Next character should be '%s'\n",
                i+1, line, bufM);
        return -1;
    }
    return 0;
}

/* Pick max <n> characters from string <start> around position <cur>.
 * Write those to <dst>.
 */
void showref(char *dst, const char *start, const char *cur, size_t n)
{
    if (strlen(start) > n-1 && (size_t) (cur - start) > (n / 2) + 1) {
        strncpy(dst, cur - (n/2) - 1, n-1);
    } else {
        strncpy(dst, start, n-1);
    }
    dst[n-1] = 0;
    remove_nonascii(dst);
}

int mycompare_new(const char *student, const char *model, char *infostr, size_t n)
{
    int i = 0, line = 1;
    char bufS[16] = { 0 };
    char bufM[16] = { 0 };
    const char *origs = student;
    const char *origm = model;
    char sturef[80];
    char modref[80];
 
    while(*student) {
        printchar(bufS, *student);
        printchar(bufM, *model);
               
        if (!(*model)) {
            showref(sturef, origs, student, 80);
            showref(modref, origm, model, 80);
            snprintf(infostr, n, "your output is longer than expected at position: %d, line: %d (char: '%s')\n"
                    "Your string: ...\"%s\"...\n"
                    "Reference string: ...\"%s\"...",
                    i+1, line, bufS, sturef, modref);
            return -1;
        }
        if (*student != *model) {
            showref(sturef, origs, student, 80);
            showref(modref, origm, model, 80);
            snprintf(infostr, n, "difference on position: %d, line: %d (char: '%s' vs. '%s')\n"
                    "Your string: ...\"%s\"...\n"
                    "Reference string: ...\"%s\"...",
                    i+1, line, bufS, bufM, sturef, modref);
            return -1;
        }
        if (*student == '\n') {
            line++;
            i = -1;
        }
        student++; model++; i++;
    }
    if (*model) {
        printchar(bufM, *model);
        showref(sturef, origs, student, 80);
        showref(modref, origm, model, 80);
        snprintf(infostr, n, "output correct until position: %d, line: %d, but shorter than expected (missing char: '%s').\n"
                    "Your string: ...\"%s\"...\n"
                    "Reference string: ...\"%s\"...",
                    i+1, line, bufM, sturef, modref);
        return -1;
    }
    return 0;    
}


void read_stdout(char *buf, unsigned int size) {
    fflush(stdout);
    FILE *fp = fopen("mockoutput", "r");
    buf[0] = '\0';
    while ((fgets(buf + strlen(buf), size - strlen(buf), fp)) != NULL);
    fclose(fp);
}
