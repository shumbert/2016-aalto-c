#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/gameoflife.h"

START_TEST(test_createField)
{
    unsigned int i, j, k, xs, ys;
    Field *f;
    for (i = 0; i < 3; i++) {
        xs = 10 + (rand() % 90);
        ys = 10 + (rand() % 90);
        f = createField(xs, ys);
        if (!f) {
            fail("[M4.02.a] createField returned NULL");
        }
        if (f->xsize != xs || f->ysize != ys) {
            releaseField(f);
            fail("[M4.02.a] Incorrect dimensions in Field struct for %ux%u field.", ys, xs);
        }
        for (j = 0; j < ys; j++) {
            for (k = 0; k < xs; k++) {
                if (f->cells[j][k] != DEAD) {
                    releaseField(f);
                    fail("[M4.02.a] Place (%u, %u) initialized incorrectly, not DEAD.", k, j);
                }
            }
        }
        releaseField(f);
    } 
}
END_TEST

int countlive(const Field *f)
{
    int alive = 0;
    for (unsigned int y = 0; y < f->ysize; y++) {
        for (unsigned int x = 0; x < f->xsize; x++) {
            if (f->cells[y][x] == ALIVE)
                alive++;
            else if (f->cells[y][x] != DEAD)
                return -1;
        }
    }
    return alive;
}

START_TEST(test_initField)
{
    Field *f;
    for (unsigned int i = 0; i < 3; i++) {
        unsigned int xs = 10 + (rand() % 30);
        unsigned int ys = 10 + (rand() % 30);
        f = createField(xs, ys);
        
        int count = xs * ys / 4;
        initField(f, count);
        
        int c = countlive(f);
        if (c < 0) {
            releaseField(f);
            fail("[M4.02.b] After calling initField, the field has cells that is neither DEAD or ALIVE.");
        } else if (c != count) {
            releaseField(f);
            fail("[M4.02.b] After calling initField(f, %d) the field has %d ALIVE cells.",
                    count, c);
        }
	releaseField(f);
    }
}
END_TEST


Field *fieldFromString(const char *s)
{
    unsigned int xsize = 0, ysize = 0, x = 0, y = 0;
    const char *t = s;

    // Figure out size of the field
    while (*t) {
        if (*t == '\n') {
            if (!xsize)
                xsize = x;
            x = 0;
            y++;
        } else {
            x++;
        }
        t++;
    }
    ysize = y;

    // set up field
    Field *f = malloc(sizeof(Field));
    if (!f)
        return NULL;

    f->cells = malloc(sizeof(State*) * ysize);
    if (!f->cells) {
        free(f);
        return NULL;
    }
    for (unsigned int i = 0; i < ysize; i++) {
        f->cells[i] = malloc(sizeof(State) * xsize);
    }
    
    unsigned int i = 0, j = 0;
    while (*s) {
        if (*s == '*')
            f->cells[i][j] = ALIVE;
        else if (*s != '\n')
            f->cells[i][j] = DEAD;
        else {
            i++;
            j = 0;
            s++;
            continue;
        }
        j++;
        s++;
    }
    
    f->xsize = xsize;
    f->ysize = ysize;
    return f;    
}

const char *fields[] = 
{   ".****..\n"
    "*.***..\n"
    "..*....\n"
    ".*...**\n"
    ".......\n",

    "*.***..\n"
    ".**...*\n"
    ".......\n"
    ".*.*.**\n"
    ".....*.\n",

    "..**...\n"
    ".**....\n"
    ".*...**\n"
    "....***\n"
    "....***\n",

    ".***...\n"
    ".*.*...\n"
    ".**.*.*\n"
    ".......\n"
    "....*.*\n"
};

int fieldToString(const Field *f, char *buf, unsigned int size)
{
    freopen("mockoutput", "w", stdout);
    printField(f);
    fflush(stdout);
    
    FILE *fp = fopen("mockoutput", "r");
    if (!fp)
        return -1;
    int n = fread(buf, 1, size-1, fp); 
    buf[n] = 0; 
    fclose(fp);
    return 0;
}

START_TEST(test_printField)
{
    Field *f;
    for (unsigned int i = 0; i < sizeof(fields) / sizeof(char *); i++) {
        f = fieldFromString(fields[i]);
        
        char str[400];
        fieldToString(f, str, sizeof(str));
    
        char infostr[400];
        if (mycompare(str, fields[i], infostr) != 0) {
            releaseField(f);
            fail("[M4.02.c] Your output:\n%s\nReference output:\n%s\nReason: %s\n",
                    str, fields[i], infostr);
        }
	releaseField(f);
    }
}
END_TEST


START_TEST(test_tick)
{
    Field *f;
    for (unsigned int i = 1; i < sizeof(fields) / sizeof(char *) - 1; i++) {
        f = fieldFromString(fields[i]);
        tick(f);
        
        char str[400];
        fieldToString(f, str, sizeof(str));
        
        char infostr[400];
        if (mycompare(str, fields[i + 1], infostr) != 0) {
            releaseField(f);
            fail("[M4.02.d] After tick()\n%s should evolve into\n%s. Your field:\n%s\nReason: %s\n",
                    fields[i], fields[i+1], str, infostr);
        }
	releaseField(f);
    }
}
END_TEST


int main(int argc, const char *argv[])
{
    srand((unsigned)time(NULL));
    Suite *s = suite_create("Test-02_life");

    tmc_register_test(s, test_createField, "M4.02.a");
    tmc_register_test(s, test_initField, "M4.02.b");
    tmc_register_test(s, test_printField, "M4.02.c");
    tmc_register_test(s, test_tick, "M4.02.d");   
    
    return tmc_run_tests(argc, argv, s);
}
