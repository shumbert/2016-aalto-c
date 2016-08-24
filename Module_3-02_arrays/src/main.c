#include <stdlib.h>
#include <stdio.h>
#include "source.h"

int main()
{
    /* testing exercise. Feel free to modify */
    int *array = dyn_reader(5);
    
    array = add_to_array(array, 5, 10);
    array = add_to_array(array, 6, 100);
    array = add_to_array(array, 6, 1000);
    
    return 0;
}
