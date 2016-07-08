title: Array Sum
task_id: 02_basics_2
points: 1


**Objective:** Practice address arithmetics with pointers.

You should implement function int array_sum(int *array, int count)
that gets a pointer to the beginning of array of integers in
consecutive slots in memory, and calculates the sum of the
integers. The number of integers to be counted is given in parameter
count. The sum is returned as the return value of the function.

For example, the following code:

    :::c
    int valarray[] = { 10, 100, 1000 };
    int ret = array_sum(valarray, 3);

should set ret to 1110.
