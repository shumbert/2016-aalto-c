#ifndef ELECA7100_5_5
#define ELECA7100_5_5

typedef enum {
    UNSPEC,  // cell is unspecified
    VALUE,  // cell contains a numeric value
    FUNC  // cell contains a function
} Celltype;

// For expressing a single location in spreadsheet
typedef struct {
    unsigned int x;
    unsigned int y;
} Point;

struct sheet;

// for representing a function and its two parameters in spreadsheet
typedef struct {
    double (*fptr)(struct sheet *, Point, Point); // function
    Point upleft; // upper left corner of function target
    Point downright; // lower right corner of function target
} Func;

// single cell in spread sheet, that can be either function, value or unspec.
typedef struct {
    Celltype type;  // tells whether cell contains value, function or nothing
    union {
        double value;  // if type == VALUE
        Func func;  // if type == FUNC
    } un;
} Cell;

// the whole spreadsheet as two-dimensional array.
// Each location is of type Cell.
typedef struct sheet {
    unsigned int xsize;
    unsigned int ysize;
    Cell **cells;
} Sheet;

Sheet *create_sheet(unsigned int xsize, unsigned int ysize);
void free_sheet(Sheet *sheet);
Cell *get_cell(Sheet *sheet, Point p);

int parse_command(Sheet *sheet, const char *command);
void print_sheet(Sheet *sheet);

void set_value(Sheet *sheet, Point p, double value);
void set_func(Sheet *sheet, Point p,
        double (*func)(Sheet *, Point, Point),
        Point ul, Point dr);

double eval_cell(Sheet *sheet, Point p);

double sumfunc(Sheet *sheet, Point ul, Point dr);
double maxfunc(Sheet *sheet, Point ul, Point dr);
double countfunc(Sheet *sheet, Point ul, Point dr);

#endif
