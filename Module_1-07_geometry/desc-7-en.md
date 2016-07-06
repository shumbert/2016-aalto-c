title: Draw Ball
task_id: 07-geometry-3
points: 1


**Objective:** One more exercise on loops in C code, together with a
decision function that determines the output.

Implement function `void draw_ball(unsigned int radius)` that draws an
ASCII box that contains a circle filled with character ('*').

The box is (2 * radius + 1) characters wide and tall, i.e., just large
enough to contain the circle. There is a helper function
'**distance**' that returns the distance of given (x,y) coordinates
from (0,0). If the circle is centered at (0,0), you can use the
'**distance**' function such that if distance(x,y) <= radius,
coordinate (x,y) is within the circle, otherwise it is outside the
circle.

If a square is within circle, print character '*'. If a square is
outside the circle, print character '.'.

When `draw_ball(3)` is called, the output should be like this:

<pre>
...*...
.*****.
.*****.
*******
.*****.
.*****.
...*...</pre>

**Hint:** You can use also negative numbers as part of the for loop,
as long as the data type allows negative numbers.
