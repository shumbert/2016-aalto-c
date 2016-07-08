title: Count Substring
task_id: 06_strbasic_2
points: 1


**Objective:** Practice the use of string functions (although the
exercise could be done without them as well).

Write function `int count_substr(const char *str, const char *sub)`
that counts how many times string '**sub**' occurs in string
'**str**', and return that as return value. For example, call
`count_substr("one two one twotwo three", "two")` should return 3,
because "two" occurs three times in the longer string. Note that the
spaces do not have any special role in these string manipulation
operations -- they are just normal characters like everything else.

**Hint:** Function **strstr** might be helpful here. It is also useful
to observe that you can process partial strings by using a pointer to
the middle of string (or any array in general). In such case the
function ignores the characters before the pointer, and continues
processing from the pointed location.
