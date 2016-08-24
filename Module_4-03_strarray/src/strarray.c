#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strarray.h"

/* Exercise a: Initializes the string array to contain the initial
 * NULL pointer, but nothing else.
 * Returns: pointer to the array of strings that has one element
 *      (that contains NULL)
 */
char **init_array(void)
{
    char **array = malloc(sizeof(char **));
    array[0] = NULL;
    return array;
}

/* Releases the memory used by the strings.
 */
void free_strings(char **array)
{
    char **current = array;
    while (*current) {
        free(*current);
        current++;
    }
    free(array);
}

/* Exercise b: Add <string> to the end of array <array>.
 * Returns: pointer to the array after the string has been added.
 */
char **add_string(char **array, const char *string)
{
    char **newarray = array;
    char *newitem;
    int length = 1;

    while (*newarray) {
        length++;
        newarray++;
    }

    newarray = malloc(sizeof(char **) * (length + 1));
    for (int i = 0; i < (length - 1); i++)
        newarray[i] = array[i];
    free(array);

    newitem = malloc(sizeof(string) + 1);
    strcpy(newitem, string);
    newarray[length - 1] = newitem;
    newarray[length] = NULL;

    return(newarray); 
}

/* Exercise c: Convert letters of all strings in <array> to lower case.
 */
void make_lower(char **array)
{
    while (*array) {
        int length = strlen(*array);
        for (int i = 0; i < length; i++)
            (*array)[i] = tolower((*array)[i]);
        array++;
    }
}


/* Exercise d: reorder strings in <array> to lexicographical order */
void sort_strings(char **array)
{
    while (*array) {
        char **cursor = array + 1;
        while (*cursor) {
            if (strcmp(*cursor, *array) < 0) {
                char *tmp = *array;
                *array = *cursor;
                *cursor = tmp;
            }
            cursor++;
        }
        array++;
    }
}

/* You can use this function to check what your array looks like.
 */
void print_strings(char **array)
{
    if (!array)
        return;
    while (*array) {
        printf("%s  ", *array);
        array++;
    }
    printf("\n");
}
