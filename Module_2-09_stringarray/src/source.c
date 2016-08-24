#include <stddef.h>
#include <stdio.h>
#include "source.h"


/* Print string array, last element is NULL */
/* Parameters:
 * array: string array to be printed, each string on own line */
void print_strarray(char *array[])
{
    int index = 0;
    while (array[index] != NULL) {
        printf("%s\n", array[index]);
        index++;
    }
}

/* Put strings from string separated by space to a string array */
/* Parameters:
 * string: string to be cut into parts and placed into the array, 
   remember to add ending zeros '\0' for strings and NULL to the end of the whole array!
 * arr: ready-made array that the strings will be put into */
void str_to_strarray(char* string, char** arr)
{
    int words   = 0;
    int current = 0;

    while (*string) {
        if (*string == ' ') {
            arr[words][current] = '\0';
            words++;
            current = 0;
        } else {
            arr[words][current] = *string;
            current++;
        }
        string++;
    }
    arr[words][current] = '\0';
    arr[++words] = NULL;
}
