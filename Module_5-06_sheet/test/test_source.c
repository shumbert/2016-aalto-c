#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>
#include "../src/spreadsheet.h"


double testfunc1(Sheet *sheet, Point ul, Point dr);


START_TEST(test_create_sheet)
{
    for (unsigned int i = 0; i < 3; i++) {
        Point p[3] = { {0,0} };
        unsigned int xs = rand() % 20 + 5;
        unsigned int ys = rand() % 20 + 5;
        
        Sheet *s = create_sheet(xs, ys);
        
        if (!s) {
            fail("[M5.06.a] create_sheet returned NULL");
        }
        
        if (s->xsize != xs || s->ysize != ys) {
            unsigned int xref = s->xsize;
            unsigned int yref = s->ysize;
            free_sheet(s);
            fail("[M5.06.a] xsize and ysize set by create_sheet are wrong. You: (%u,%u). Expected: (%u,%u)",
                    xref, yref, xs, ys);
        }
        
        p[1].x = xs - 1;
        p[1].y = ys - 1;
        p[2].x = xs + 2;
        p[2].y = ys + 2;
        
        for (unsigned int j = 0; j < 3; j++) {
            Cell *c = get_cell(s, p[j]);
            if (p[j].x < xs) {
                if (!c) {
                    free_sheet(s);
                    fail("[M5.06.a] get_cell for (%u,%u) returned NULL, even though it is an in-bound coordinate.",
                            p[j].x, p[j].y);
                }
                if (c->type != UNSPEC) {
                    free_sheet(s);
                    fail("[M5.06.a] After creating the sheet, get_cell for (%u,%u) did not return UNSPEC type as expected.",
                            p[j].x, p[j].y);
                }
            }
            if (p[j].x >= xs && c != NULL) {
                free_sheet(s);
                fail("[M5.06.a] get_cell for out-of-bounds location (%d,%d) did not return NULL.",
                        p[j].x, p[j].y);
            }
        }
        free_sheet(s);
    }
    test_complete();
}
END_TEST

START_TEST(test_set_value)
{   
    for (unsigned int i = 0; i < 3; i++) {
        unsigned int xs = rand() % 20 + 5;
        unsigned int ys = rand() % 20 + 5;
        unsigned int voff = rand() % 100;
        
        Sheet *s = create_sheet(xs, ys);
        if (!s) {
            fail("[M5.06.b] create_sheet returned NULL");
        }
        
        // set content
        for (unsigned int j = 0; j < 4; j++) {
            Point p = { xs - 3 + j, ys - 3};
            set_value(s, p, voff + j);
            
            p.y++;
            Point ul = {j, j+1};
            Point dr = {j+2, j+3};
            set_func(s, p, testfunc1, ul, dr);
        }
        
        // test content
        for (unsigned int j = 0; j < 4; j++) {
            Point p = { xs - 3 + j, ys - 3};
            Cell *c = get_cell(s, p);
            if (j < 3 && !c) {
                free_sheet(s);
                fail("[M5.06.b] get_cell returned NULL for valid cell.");
            }
            if (j == 3 && c) {
                free_sheet(s);
                fail("[M5.06.b] get_cell did not return NULL for out-of-bound cell.");
            }
            if (!c)
                continue;
            
            if (c->type != VALUE) {
                free_sheet(s);
                fail("[M5.06.b] After set_value on (%u,%u), cell type is not VALUE.",
                        p.x, p.y);
            }
            if (c->un.value != (double) voff + j) {
                double v = c->un.value;
                free_sheet(s);
                fail("[M5.06.b] After set_value on (%u,%u), cell value should be %f, you have %f",
                        p.x, p.y, (double) voff + j, v);
            }
            
            p.y++;
            Point ul = {j, j+1};
            Point dr = {j+2, j+3};
            
            c = get_cell(s, p);
            if (j < 3 && !c) {
                free_sheet(s);
                fail("[M5.06.b] get_cell returned NULL for valid cell.");
            }
            if (j == 3 && c) {
                free_sheet(s);
                fail("[M5.06.b] get_cell did not return NULL for out-of-bound cell.");
            }
            if (!c)
                continue;
            
            if (c->type != FUNC) {
                free_sheet(s);
                fail("[M5.06.b] After set_func on (%u,%u), cell type is not FUNC.",
                        p.x, p.y);
            }
            if (c->un.func.fptr != testfunc1) {
                free_sheet(s);
                fail("[M5.06.b] After set_func on (%u,%u), function pointer is not set correctly.",
                        p.x, p.y);
            }
            if (memcmp(&c->un.func.downright, &dr, sizeof(Point))) {
                Point sp = c->un.func.downright;
                free_sheet(s);
                fail("[M5.06.b] After set_func on (%u,%u), 'downright' parameter is (%u,%u). Expected (%u,%u).",
                        p.x, p.y, sp.x, sp.y, dr.x, dr.y);
            }
            if (memcmp(&c->un.func.upleft, &ul, sizeof(Point))) {
                Point sp = c->un.func.upleft;
                free_sheet(s);
                fail("[M5.06.b] After set_func on (%u,%u), 'upleft' parameter is (%u,%u). Expected (%u,%u).",
                        p.x, p.y, sp.x, sp.y, dr.x, dr.y);
            }
        }
        free_sheet(s);
    }
    test_complete();
}
END_TEST

double testfunc1(Sheet *s, Point ul, Point dr)
{
    for (unsigned int i = ul.x; i <= ul.x; i++) {
        for (unsigned int j = ul.y; j <= ul.y; j++) {
            Point p = {i, j};
            set_value(s, p, i*j);
        }
    }
    return dr.x + ul.x + dr.y + ul.y;
}

START_TEST(test_eval_cell)
{
    unsigned int xs = 10;
    unsigned int ys = 10;
    Sheet *s = create_sheet(xs, ys);
    
    if (!s) {
        fail("[M5.06.c] create_sheet returned NULL");
    }
    
    Point p = {1,1};
    double val = rand() % 100;
    set_value(s, p, val);
    
    p.x = 3;
    p.y = 2;
    Point ul = {4,5};
    Point dr = {6,8};
    set_func(s, p, testfunc1, ul, dr);
    
    p.x = 0; p.y = 0;
    double ret = eval_cell(s, p);
    if (!isnan(ret)) {
        free_sheet(s);
        fail("[M5.06.c] eval_cell() for UNSPEC location should return NAN");
    }
    
    p.x = 1; p.y = 1;
    ret = eval_cell(s, p);
    if (ret != val) {
        free_sheet(s);
        fail("[M5.06.c] eval_cell() for VALUE location should have returned value %f. You returned %f",
                val, ret);
    }
    
    p.x = 3; p.y = 2;
    ret = eval_cell(s, p);
    double expval = dr.x + ul.x + dr.y + ul.y;
    if (ret != expval) {
        free_sheet(s);
        fail("[M5.06.c] eval_cell() for FUNC cell should call the given function and use its return value. You returned: %f, expected: %f",
                ret, expval);
    }
    
    p.x = 4; p.y = 5;
    ret = eval_cell(s, p);
    if (ret != (double) 4 * 5) {
        free_sheet(s);
        fail("[M5.06.c] eval_cell() for FUNC cell should cause the given function to be called");
    }
    free_sheet(s);
    test_complete();
}
END_TEST

START_TEST(test_funcs)
{
    char buf[80] = { 0 };
    Sheet *s = create_sheet(10,10);
    if (!s) {
        fail("[M5.06.d] create_sheet returned NULL");
    }
    
    double expsum = 0;
    double expmax = 0;
    for (unsigned int x = 1; x <= 3; x++) {
        for (unsigned int y = 1; y <= 2; y++) {
            Point p = {x, y};
            char b2[8];
            int d = rand() % 100 + 2;
            sprintf(b2, "%d ", d);
            strcat(buf, b2);
            
            set_value(s, p, d);
            expsum += d;
            if (d > expmax)
                expmax = d;
        }
    }

    Point p = {4,1};
    Point ul = {1,1};
    Point dr = {3,2};
    set_func(s, p, maxfunc, ul, dr);
    
    p.x = 5;
    dr.x = 4;
    set_func(s, p, sumfunc, ul, dr);
    
    p.x = 6;
    dr.x = 5;
    set_func(s, p, countfunc, ul, dr);
    
    p.x = 4;
    double ret = eval_cell(s, p);
    if (ret != expmax) {
        free_sheet(s);
        fail("[M5.04.d] eval_cell on location with maxfunc over 3x2 area returned %f. Expected %f. Values: %s",
                ret, expmax, buf);
    }
    
    char b2[16];
    sprintf(b2, "%f", ret);
    strcat(buf, b2);
    expsum += ret;
    
    p.x = 5;
    ret = eval_cell(s, p);
    if (ret != expsum) {
        free_sheet(s);
        fail("[M5.04.d] eval_cell on location with sumfunc over 4x2 area returned %f. Expected %f. Values: %s",
                ret, expsum, buf);
    }
    
    p.x = 6;
    ret = eval_cell(s, p);
    if (ret != 8) {
        free_sheet(s);
        fail("[M5.04.d] eval_cell on location with countfunc over 5x2 area (2 undefined cells) returned %f. Expected %f",
                ret, (double) 8);
    }

    free_sheet(s);
    test_complete();
}
END_TEST

int main(int argc, const char *argv[]) {
    srand((unsigned)time(NULL));
    Suite *s = suite_create("Test-05_sheet");

    tmc_init_tests();
    
    tmc_register_test(s, test_create_sheet, "M5.06.a");
    tmc_register_test(s, test_set_value, "M5.06.b");
    tmc_register_test(s, test_eval_cell, "M5.06.c");
    tmc_register_test(s, test_funcs, "M5.06.d");
        
    return tmc_run_tests(argc, argv, s);
}
