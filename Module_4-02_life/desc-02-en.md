title: Game of Life
task_id: 02_life
points: 4


**Objective:** practice allocating and manipulating dynamic
  two-dimensional arrays.

Conway's [Game of Life] is a traditional zero-player game that runs a
cellular automaton based on an initial system state and a simple set of
rules. Game of Life operates on a two-dimensional grid, where each
cell can have two states: "dead" or "alive". The state of the grid
progresses in discrete steps (or "ticks"), where each cell may change
its state based on the states of its neighbors.

[Game of Life]: http://en.m.wikipedia.org/wiki/Conway%27s_Game_of_Life

The rules determining state changes on an individual cell are:

  * Any **live** cell with **fewer than two live** neighbours **dies**

  * Any **live** cell with **two or three live** neighbours **lives** on to the
    next generation.

  * Any **live** cell with **more than three live** neighbours **dies**

  * Any **dead** cell with **exactly three live neighbours** becomes a
    **live** cell.

Also diagonal cells are considered neighbors, i.e., each cell (that is
not on the edge of the field) has 8 neighbors. Remember to consider
cells that are on the edge of the field: you should not access
positions that are out of the bounds of the field.

The state changes on each cell occur simultaneously. I.e., as you
process the field one cell at a time, the intermediate changes made
earlier during the current iteration must not affect the result.

For example, a field with the following setting ('*' indicates live cell):

<pre>
..........
.**.***...
.**......*
.*.*.....*
........*.</pre>

Will in the next generation be:

<pre>
.....*....
.***.*....
*...**....
.*......**
..........</pre>

The [wikipedia page] on Conway's Game of Life gives further background,
and examples of some interestingly behaving patterns.

[wikipedia page]: http://en.m.wikipedia.org/wiki/Conway%27s_Game_of_Life

In this exercise you will implement the necessary components for Game
of Life such that you should be able to follow the progress of the
game field between generations. The main function in src/main.c has
the core of the game, that generates the field and goes through the
generations one by one using the functions you will implement.

The exercise will have the following subtasks, each worth one point.

a) Create and release game field
-----------------------------------

Implement the function '**createField**' that allocates the needed space
for the '**Field**' structure that holds the game field, and for a
two-dimensional array of dimensions given in parameters '**xsize**'
and '**ysize**'. Each cell in the field must be initialized to 'DEAD'
state, as well as the 'xsize' and 'ysize' fields in the structure.

Note: the tests assume that the rows (y-axis) of the field are
the first dimension of the array (and allocated first), and the
columns are the second dimension. I.e., the cells are indexed as
[y][x].

You will also need to implement the function '**releaseField**' that frees
the memory allocated by *createField()*. The tests will use this
function for all memory releases, so failing to implement this will
result in Valgrind errors about memory leaks.

b) Initialize field
----------------------

Implement the function '**initField**' that turns a given number of cells
into 'ALIVE' state. You can decide the algorithm by which you set up
the field, but the outcome must be that exactly '**n**' cells in the
field are alive. One possibility is to use the '**[rand]**' function
to choose the live cells randomly.

[rand]: http://linux.die.net/man/3/rand

c) Print field
-----------------

Implement the function '**printField**' that outputs the current state of
the field to the screen. Each dead cell is marked with '.' and each
live cell is marked with '*'. There are no spaces between the cells,
and each row ends in a newline ('\n'), including the last line. The
output should look similar, as in the above examples in this task
description.

d) Progress game field
-------------------------

Implement the function '**tick**' that advances the game field by one
generation according to the rules given above. Note that all cells
need to be evaluated "simultaneously". One way to do this is to
maintain two game fields: one that holds the state before the transition,
and another where you will build the next generation of the game field.

(If you allocate new memory in this function, don't forget to
release it.)
