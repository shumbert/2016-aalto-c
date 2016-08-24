#include <stdlib.h>
#include <stdio.h>
#include "source.h"


/* Dynamic Array Reader */
/* Parameters:
 * n: Number of values to be read
 * 
 * Returns: pointer to the dynamically allocated array
 */
int *dyn_reader(unsigned int n)
{
    int *array = malloc(n * sizeof(int));
    unsigned int read = 0;
    while(read < n) {
        scanf("%d", array + read);
        read++;
    }
    return array;
}

/* Add to array */
/* Parameters:
 * arr: Existing array of integers
 * num: number of integers in the array before the call
 * newval: new value to be added
 * 
 * Returns: pointer to the allocated array
 */
int *add_to_array(int *arr, unsigned int num, int newval)
{
    int *array = realloc(arr, (num + 1) * sizeof(int));
    array[num] = newval;
    return array;
}
