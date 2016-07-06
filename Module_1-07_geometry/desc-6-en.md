title: Draw Triangle
task_id: 07-geometry-2
points: 1


**Objective**: Practice use of nested loops in C code, together with a
bit of conditional application logic.

Implement function `void draw_triangle(unsigned int size)` that draws
an ASCII box that contains a triangle.

The box should be **size** characters wide, and **size** characters tall.
The box is split diagonally in two such that the righthand and bottom
characters are '#', and the lefthand and top characters are '.'.

The first line contains one '#' character at the right edge, the
second line contains two '##' characters, and so on. On the last line
all characters are '#'.

All lines (also the last) end with a newline character ('\n').

Here is an example calling `draw_triangle(5)`:

<pre>
....#
...##
..###
.####
#####
</pre>
