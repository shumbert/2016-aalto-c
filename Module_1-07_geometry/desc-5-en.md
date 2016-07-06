title: Multiplication table
task_id: 07-geometry-1
points: 1


**Objective:** Practice use of nested loops and formatted output

Implement function `void multi_table(unsigned int xsize, unsigned int
ysize)` that prints a multiplication table on the screen that has
numbers from 1 to '**xsize**' on the x-axis, and numbers from 1 to
'**ysize**' on the y-axis, and products of these numbers in tabular
format. Each number should take 4 characters when printed on the
screen, aligned to the right. There is a newline character ('\n') at
the end of each line, including the last line. For example, function
call `multi_table(4,5)` should result in the following output:

<pre>
   1   2   3   4
   2   4   6   8
   3   6   9  12
   4   8  12  16
   5  10  15  20</pre>
