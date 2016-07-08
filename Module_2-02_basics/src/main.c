#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "source.h"

int main()
{

    /* Pointer Sum with two input parameters */
    int val1 = 4; int val2 = 5;
    number_swap(&val1, &val2);
    if (val1 == 5) {
        printf("Great, 2.1 worked!\n");
    } else {
        printf("Invalid result for 2.1\n");
    }

    /*  Extending Pointer sum */
    int valarray[] = { 10, 100, 1000 };
    int sum = array_sum(valarray, 3);
    if (sum == 1110) {
        printf("2.2 worked\n");
    } else {
        printf("Invalid result for 2.2");
    }

    /* Array Reader */
    int ints[10];
    printf("Read %d integers!\n", array_reader(ints, 10));

    return 0;
}
