#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spreadsheet.h"

const struct {
    char *name;
    double (*fptr)(Sheet *,Point, Point);
} functions[] = {
    { "sum", sumfunc },
    { "max", maxfunc },
    { "count", countfunc },
    { NULL, NULL }
};


/* Creates a new spreadsheet with given dimensions.
 * Returns pointer to the allocated Sheet structure.
 */
Sheet *create_sheet(unsigned int xsize, unsigned int ysize)
{
    Sheet *sheet = malloc(sizeof(Sheet));
    if (!sheet)
        return NULL;

    sheet->xsize = xsize;
    sheet->ysize = ysize;
    sheet->cells = malloc(ysize * sizeof(Cell *));
    if (!sheet->cells) {
        free(sheet);
        return NULL;
    }

    for (unsigned int y = 0; y < ysize; y++) {
        sheet->cells[y] = malloc(xsize * sizeof(Cell));
        if (!sheet->cells[y]) {
            for (unsigned int i = 0; i < y; i++)
                free(sheet->cells[i]);
            free(sheet->cells);
            free(sheet);
            return NULL;
        }
        for (unsigned int x = 0; x < xsize; x++)
            sheet->cells[y][x].type = UNSPEC;
    }

    return sheet;
}

/* Releases the memory allocated for sheet.
 */
void free_sheet(Sheet *sheet)
{
    if (sheet) {
        if (sheet->cells) {
            for (unsigned int y = 0; y < sheet->ysize; y++)
                if (sheet->cells[y])
                    free(sheet->cells[y]);
            free(sheet->cells);
        }
        free(sheet);
    }
}


/* Returns pointer to the Cell structure at given location <p>
 * in spreadsheet <sheet>.
 */
Cell *get_cell(Sheet *sheet, Point p)
{
    if (sheet)
        if (p.x < sheet->xsize && p.y < sheet->ysize)
            return sheet->cells[p.y] + p.x;
    return NULL;
}

/* Convert two-letter user input into coordinates of type Point.
 */
Point get_point(char xc, char yc)
{
    Point p;
    p.x = toupper(xc) - 'A';
    p.y = toupper(yc) - 'A';
    return p;
}

/* Parses user input in <command> and applies it in spreadsheet <sheet>.
 * Returns 1 if input was valid, or 0 if it was not.
 */
int parse_command(Sheet *sheet, const char *command)
{
    double val;
    Point p;
    char xc, yc;
    int ret = sscanf(command, "%c%c %lf", &xc, &yc, &val);
    if (ret == 3) {
        p = get_point(xc, yc);
        set_value(sheet, p, val);
        return 1;
    }
    
    char func[10];
    Point ul, dr;
    char xc1, yc1, xc2, yc2;
    
    ret = sscanf(command, "%c%c %9s %c%c %c%c", &xc, &yc, func, &xc1, &yc1, &xc2, &yc2);
    if (ret == 7) {
        p = get_point(xc, yc);
        ul = get_point(xc1, yc1);
        dr = get_point(xc2, yc2);
        int i = 0;
        while (functions[i].name) {
            if (!strcmp(functions[i].name, func)) {
                set_func(sheet, p, functions[i].fptr, ul, dr);
                return 1;
            }
            i++;
        }
    }
    return 0;
}

/* Prints the content of given spreadsheet.
 */
void print_sheet(Sheet *sheet)
{
    printf("%-8c", ' ');
    for (unsigned int x = 0; x < sheet->xsize; x++) {
        printf("%-8c", 'A' + x);
    }
    fputs("\n", stdout);
    
    for (unsigned int y = 0; y < sheet->ysize; y++) {
        printf("%-8c", 'A' + y);
        for (unsigned int x = 0; x < sheet->xsize; x++) {
            Point p;
            p.x = x;
            p.y = y;
            Cell *c = get_cell(sheet, p);
            switch(c->type) {
                case VALUE:
                case FUNC:
                    printf("%-8.1f", eval_cell(sheet, p));
                    break;
                    
                default:
                    printf("%-8c", '*');
                    break;                    
            }
        }
        fputs("\n", stdout);
    }
}

/* Set the content of location <p> in spreadsheet to constant <value>
 */
void set_value(Sheet *sheet, Point p, double value)
{
    if (sheet)
        if (p.x < sheet->xsize && p.y < sheet->ysize) {
            Cell *cell     = sheet->cells[p.y] + p.x;
            cell->type     = VALUE;
            cell->un.value = value;
        }
}

/* Set the content of location <p> in spreadsheet to given function.
 * <func> is pointer to the function. <ul> is the upper left corner and 
 * <dr> is the lower right corner of the area over which the function
 * is applied.
 */
void set_func(Sheet *sheet, Point p,
        double (*func)(Sheet *, Point, Point),
        Point ul, Point dr)
{
    if (sheet)
        if (p.x < sheet->xsize && p.y < sheet->ysize) {
            Cell *cell                = sheet->cells[p.y] + p.x;
            cell->type                = FUNC;
            cell->un.func.fptr        = func;
            cell->un.func.upleft.x    = ul.x;
            cell->un.func.upleft.y    = ul.y;
            cell->un.func.downright.x = dr.x;
            cell->un.func.downright.y = dr.y;
        }
}

/* Evaluate the content of cell at location <p>.
 * If cell is constant value, that is returned.
 * If cell contains function, the function is evaluated and its result returned.
 * If cell is unspecified or location out of bounds, NAN is returned.
 */
double eval_cell(Sheet *sheet, Point p)
{
    if (sheet)
        if (p.x < sheet->xsize && p.y < sheet->ysize) {
            Cell *cell = sheet->cells[p.y] + p.x;
            if (cell->type == VALUE)
                return cell->un.value;
            if (cell->type == FUNC)
                return cell->un.func.fptr(sheet, cell->un.func.upleft, cell->un.func.downright);
        }
    return NAN;
}

/* Calculate the maximum value within area with upper left corner <ul>
 * and lower right corner <dl>, and return it.
 */
double maxfunc(Sheet *sheet, Point ul, Point dr)
{
    double max = 0.;

    for (unsigned int i = ul.x; i <= dr.x; i++)
        for (unsigned int j = ul.y; j <= dr.y; j++)
            if (i < sheet->xsize && j < sheet->ysize) {
                Cell *cell = sheet->cells[j] + i;
                double current = 0.;

                if (cell->type == VALUE)
                    current = cell->un.value;

                if (cell->type == FUNC) {
                    Point p;
                    p.x = i;
                    p.y = j;
                    current = eval_cell(sheet, p);
                }
                
                if (current > max)
                    max = current;
            }

    return max;
}

/* Calculate the sum of values within upper left corner <ul> and
 * lower right corner <dr>, and return the result.
 */
double sumfunc(Sheet *sheet, Point ul, Point dr)
{
    double sum = 0.;

    for (unsigned int i = ul.x; i <= dr.x; i++)
        for (unsigned int j = ul.y; j <= dr.y; j++)
            if (i < sheet->xsize && j < sheet->ysize) {
                Cell *cell = sheet->cells[j] + i;
                double current = 0.;

                if (cell->type == VALUE)
                    current = cell->un.value;

                if (cell->type == FUNC) {
                    Point p;
                    p.x = i;
                    p.y = j;
                    current = eval_cell(sheet, p);
                }
                
                sum += current;
            }

    return sum;
}

/* Count the number of specified cells inside the area with upper left
 * corner <ul> and lower right corner <dr>.
 */
double countfunc(Sheet *sheet, Point ul, Point dr)
{
    double count = 0.;

    for (unsigned int i = ul.x; i <= dr.x; i++)
        for (unsigned int j = ul.y; j <= dr.y; j++)
            if (i < sheet->xsize && j < sheet->ysize) {
                Cell *cell = sheet->cells[j] + i;
                if (cell->type == FUNC || cell->type == VALUE)
                    count++;
            }

    return count;
}
