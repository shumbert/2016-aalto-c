title: Number Swap
task_id: 02_basics_1
points: 1


**Objective:** A simple basic example to practice the use of pointers.

Implement function `number_swap(int *a, int *b)` that gets two
pointers to integers as parameters. The function should swap the
content of pointed integers. For example after the following code,
value of val1 should become 5, and value of val2 should become 4.

    :::c
    int val1 = 4; int val2 = 5;
    number_swap(&val1, &val2);
    if (val1 == 5 && val2 == 4) {
        printf("Great, it worked!\n");
    }
