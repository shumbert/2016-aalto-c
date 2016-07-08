#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "source.h"

int main()
{
    /* Implement your own tests here. Free feel to modify. */

    char string[] = "Test string, that is different";
    char *array[] = {"This", "is", "a", "test", "string.", NULL};
    char **arr = malloc(sizeof(char*)*6);
    
    // Save pointers for later use
    char **save = arr, **begin = arr;

    for(int i=0; i<5; i++)
        arr[i] = malloc(10);
    arr[5]=NULL;

    // Test a.
    print_strarray(array);

    // Test b.
    str_to_strarray(string, arr);
    print_strarray(arr);

    // Free array
    while(*save){
        free(*save);
        save++;
    }
    free(begin);

    return 0;
}
