#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "source.h"

int *join_arrays(unsigned int n1, int *arr1, unsigned int n2, int *arr2, unsigned int n3, int *arr3)
{
    int *array;
    array = malloc(sizeof(int) * (n1 + n2 + n3));
    if (!array) {
        printf("Memory allocation failed\n");
        exit(-1);
    }

    memcpy(array          , arr1, n1 * sizeof(int));
    memcpy(array + n1     , arr2, n2 * sizeof(int));
    memcpy(array + n1 + n2, arr3, n3 * sizeof(int));

    return array;
}
