title: Join arrays
task_id: 03_join
points: 1

**Objective:** Practice use of memory management functions, and
  creating your source file and the related header definition from
  scratch.

Implement function **join_arrays** that gets three integer arrays as
its arguments, and for each array the number of integers the array
contains. The six function arguments should be in this order:

  * number of integers in the first array (as unsigned integer)
  * pointer to first array of integers
  * number of integers in the second array (as unsigned integer)
  * pointer to second array of integers
  * number of integers in the third array (as unsigned integer)
  * pointer to third array of integers

The function should join the three arrays into single array that
contains all integers from the original arrays in the above
order. The new array should be allocated dynamically, and the
function should return the pointer to the created array. You must not
modify the original arrays.

See example from *main.c* about how the function is called. In
addition to *source.c* you will also need to modify *source.h*, so
that the main function (and the tests) can find your
function. Remember to include the needed headers. Note that in the
beginning the code will not even compile, before you have implemented
at least a some sort of placeholder of the *join_arrays* function that
matches the interface that *main.c* assumes.
