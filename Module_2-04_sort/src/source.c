#include <stdio.h>
#include "source.h"


/* Selection sort */
/* Parameters:
 * start: start of an array
 * size: length of an array
 */
void sort(int *start, int size)
{
    for (int i = 0; i < size; i++) {
        int index = i;
        for (int j = i + 1; j < size; j++)
            if (start[j] < start[index])
                index = j;
        if (index != i) {
            int tmp = start[i];
            start[i] = start[index];
            start[index] = tmp;
        }        
    }

    for (int i = 0; i < size; i++)
        printf("%d ", start[i]);
    printf("\n");
}

