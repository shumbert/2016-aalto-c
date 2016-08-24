title: String array
task_id: 03_strarray
points: 4


**Objective:** Practice the use of dynamically allocated arrays that
consist of dynamically allocated strings.

This exercise manipulates an array that contains pointers to
dynamically allocated strings. The last element of the array is a NULL
pointer, i.e., an 'empty' array consists of a single NULL
member. Implement the following functions:

a) Initialize array
----------------------

Implement function '**init_array**' that initializes the string array
to have the initial NULL pointer, but nothing else. The space for the
NULL pointer needs to be allocated dynamically. In other words: the
array has one pointer member, that has NULL value.

In addition, implement the function **free_strings** that releases the
memory allocated for the array. Remember that in later phases there
will also be pointers to strings in the array. Implementing
**free_strings** is necessary for Valgrind tests to pass, and
therefore for getting points for this and other parts of the
exercise.

b) Add string
----------------

Implement the function '**add_string**' that adds the given string to the
array. Note that the source string is of type `const char*`, but the
array members should be modifiable. Therefore, just copying the string
pointer is not enough. As you resize (and likely reallocate) the
array, remember that the last member should always be a NULL
pointer.

c) Make lower case
---------------------

Implement the function **make_lower** that converts all strings in the
array to lower case characters (<b><a
href="http://linux.die.net/man/3/tolower">tolower</a></b> function
converts a single character to lower case).

d) Sort array
----------------

Implement the function <b>sort_strings</b> that sorts the strings in the array
to lexicographical order (as determined by the <b><a
href="http://linux.die.net/man/3/strcmp">strcmp</a></b> function). You
have (probably) implemented one kind of sort function in Module 2, and a
similar approach works also here. It is useful to know that '**strcmp**' can
be used for determining the order: if the <b>strcmp</b> function
returns *smaller than 0*, the first string is before the second; if it returns
*larger than 0* the first string should be after the second.
