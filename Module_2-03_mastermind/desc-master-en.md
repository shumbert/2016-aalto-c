title: Mastermind
task_id: 03_mastermind
points: 1


**Objective:** Practice manipulation of arrays.

Implement function `void mastermind(const int *solution, const int
*guess, char *result, unsigned int len)` that compares integer array
'**guess**' to array '**solution**'. Both arrays contain '**len**' integers
from 0 to 9. The function outputs character array '**result**', that also has
'**len**' characters, in the following way:

  * If arrays '**solution**' and '**guess**' have same number in Nth array location,
    character array '**result**' will have '+' in Nth location.

  * If array '**guess**' has number in Nth location that exists in
    array '**solution**', but in different location, character array
    '**result**' will have '*' in Nth location.

  * If array '**guess**' has number in Nth location that does not
    exist at all in array '**solution**', character array '**result**'
    will have '-' in that location.

Note that arrays '**solution**' and '**guess**' are such that you
should not modify (input parameters), and array '**result**' may not
have any sane content when function is called, but you need to set it
in the function.

For example, when '**len**' is 6, '**solution**' is { 2, 6, 6, 3, 5, 3} and
'**guess**' is {4, 5, 6, 1, 8, 9}, the function sets '**result**' to
{'-', '*', '+', '-', '-', '-'}.

The main function in main.c implements a simple [Mastermind] game you
can use to test your function.

[Mastermind]: http://en.wikipedia.org/wiki/Mastermind_(board_game)
