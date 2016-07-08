title: Array Reader
task_id: 02_basics_3
points: 1


**Objective:** Practice use of arrays and array notation together with
scanf.

Implement function `int array_reader(int *vals, int n)` that reads
integer values using scanf into pre-allocated array ('**vals**'). The
numbers read from input are separated with whitespace (space, tab,
newline,...) that is the default field separator for scanf function,
i.e., you should be able to use the basic scanf format string for
decimal numbers. Parameter '**n**' gives the maximum length of the
array, and the maximum number of values to be read. If user does not
give a valid integer (as can be seen from return value of scanf), the
array ends, even if the maximum size was not yet reached. The function
returns the final size of the array at the end, which can be smaller
that the incoming '**n**' parameter, if the user finished the input
with non-valid integer.

Below is an example how this function can be tested:

    :::c
    int array[10];
    int n = array_reader(array, 10);
    printf("%d numbers read\n", n);
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }

For example, the following input should cause the first four array
elements to become 5, 8, 2, and 7, and then terminate because the
fifth field read is not a decimal number:

<pre>
<font color="red">5 8 2 7 -</font></pre>
