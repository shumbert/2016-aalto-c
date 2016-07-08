title: Count Alpha
task_id: 06_strbasic_1
points: 1


**Objective:** Get familiar with operating on a string, character by
character until the end of the string.

Write function `int count_alpha(const char *str)` that counts the
number of alphabetic characters in given string. You can use function
**int [isalpha](http://linux.die.net/man/3/isalpha)(int character)**
defined in **ctype.h** header, to check whether a single given
character is alphabetic (i.e. you need to add a correct `#include`
directive in the beginning of your source file). **isalpha** returns
non-zero if the given character is alphabetic, or zero if it is not
alphabetic. The function should return the number of alphabetic
characters.
