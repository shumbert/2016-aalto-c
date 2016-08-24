title: Spreadsheet
task_id: 05_sheet
points: 4


**Objective**: Practice use of function pointers. This exercise also
  revisits various other recent topics such as typedefs, unions,
  two-dimensional arrays, etc.

This exercise implements a two-dimensional spreadsheet. Each cell in
the spreadsheet can be in three possible states: a) unspecified,
i.e., the cell has no defined content; b) it can hold a static value of
*double* type; or c) it can hold a function that makes an calculation
over specified area of the spreadsheet.

The "function" is specified as a function pointer to your code that
performs the intended calculation. All such functions take two
coordinates as their arguments: location of the upper left corner of
an area, and location of the lower right corner of an area. The
functions should return a double-typed return value as a result of
their calculation, that is shown as a value of the particular location
in the spreadsheet.

There are some readily given functions in the task template, that are
only used from src/main. It is recommended that you use src/main to
test your code before passing it to TMC tests.

  * **parse_command** reads a short command from user that can set a
    given sheet location to a static value or to one of the three
    functions given in the template. The coordinates are represented
    as two letters in the beginning of command. For example: "AA 6"
    sets the upper left coordinate to value 6, and "BA sum CC EE" sets
    location (1,0) to show the sum over a 3x3 area between coordinates
    (2,2) and (4,4).

  * **print_sheet** outputs the content of the current spreadsheet.

Note that in order to either of the above functions to work correctly,
you'll need to implement a few other functions they depend on.

You'll need to implement this exercise in the following phases (in
this respective order):

(a) Creating and releasing the spreadsheet
--------------------------------------------

Implement the following functions:

  * **create_sheet** that allocates the memory needed for the
    spreadsheet, i.e., the *Sheet* structure, and the
    two-dimensional array.

  * **free_sheet** that releases all memory allocated by
    *create_sheet()*

  * **get_cell** that accesses one cell with given coordinates in the
    spreadsheet and returns a pointer to that. *get_cell()* should be
    safe against indexing out of bounds: if invalid coordinates are
    given, it should return NULL (instead of Valgrind errors).

Note that the tests use these functions in all of the following parts,
so they need to be implemented first.

(b) Set content for the spreadsheet
-------------------------------------

Implement the following functions:

  * **set_value** that sets the given location in the spreadsheet to a
    double-typed constant value.

  * **set_func** that sets the given location in the spreadsheet to
    contain the given function and its parameters.

Both functions should be safe against indexing out of bounds. In such
case, they should do nothing.

(c) Evaluate cell content
---------------------------

Implement function **eval_cell** that returns double-typed value based
on the cell content. If cell type is VALUE, the function should return
this value. If cell type is FUNC, the function should call the
function associated with the cell, and return the value returned by
the function. If cell type is UNSPEC, or if the caller is indexing out
of bounds, the function should return constant *NAN* (not-a-number),
which is defined in the '*math.h*' header. (*Note: if you need to test
whether a value is NAN, you should use [isnan()] macro.*)

[isnan()]: http://linux.die.net/man/3/isnan

(d) Three spreadsheet functions
---------------------------------

Implement functions for calculating the maximum value over an area, a
sum over an area, and count of specified cells over an area as
follows:

  * **maxfunc** will return the largest value inside an area with
    upper left corner and lower right corner as given by arguments. If
    the area contains unspecified cells, or out-of-bound coordinates,
    they should be ignored.

  * **sumfunc** will return the sum of values inside an area with
    upper left corner and lower right corner as given by arguments. If
    the area contains unspecified cells, or out-of-bound coordinates,
    they should be ignored.

  * **countfunc** that will return the number of cells within the
    given area that contain specified content (value or function).

These functions are called by the *eval_cell()* function as needed based
on spreadsheet content.

Note that in all three above functions the target area may contain
either values or functions. For cells that contain functions, the
result of the given function needs to be used in calculation. In other
words, the functions themselves may need to use *eval_cell()* and
subsequently call other functions.
