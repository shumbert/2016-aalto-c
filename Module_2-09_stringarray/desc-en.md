title: String array
task_id: 09_stringarray
points: 2


**Objective:** Take a advance peek into arrays of strings (which are
essentially two-dimensional arrays).

Also strings can be placed in arrays. Because string is an array of
characters, string arrays are arrays of string, that each are arrays
of characters. This exercise assumes an array of strings, where end of
the array is indicated with a NULL pointer.


a) Print string array
---------------------

Implement function `void print_strarray(char *array[])` that prints
all strings in *array*, each on a separate line (there is newline
character at the end of each string). The function argument notation
may seem new: it represents an *array* that is composed of `char *` -
typed elements. Therefore, you can use each array member as any normal
string in expressions. Remember that the end of array is represented
by a NULL pointer. 


b) Convert string into array
----------------------------

Implement function `void str_to_strarray(char* string, char** arr)`
that gets *string* as a parameter, and turns it into an array of
strings (*arr*). The original string may contain multiple words separated by
space, and the function separates each space-separated word into its
own array member. Remember that each string in array must end in
'\0' - character, and the array must end in NULL pointer.

We have not yet covered two-dimensional arrays, but when `arr[i]` is a
string in an array as described above, you can access individual j'th
character with notation `arr[i][j]`, either for reading or writing.
