title: Secret Message
task_id: 08-characters-2
points: 1


**Objective:** More playing with character manipulation, loops and use of
functions. Also, this works as a preliminary introduction to strings (actual
content in module 2).

Implement function `void secret_msg(int msg)` which decrypts (and encrypts) a given
message using a primitive algorithm (as described below). Each secret message
is identified by integer that is given as the parameter of this call ('msg').
You receive the message one character at a time by calling function `char
get_character(int msg, unsigned int cc)` that is given in the exercise
template. Implementation of that function contains some concepts introduced
only in Module 2 (arrays, strings), but you don't need to mind about them yet.
Just assume that the function returns character number 'cc' from message that
is numbered 'msg' (which is just the same value passed with the call to
secret_msg).

Character numbering starts from 0. You will need to call get_character multiple
times, by increasing the value of 'cc' by one for each call, until you receive
0 as the return value (i.e., cc is the character count from the beginning of
the message).

As you read the characters in message, you'll need to decrypt each of them at a
time and **print the decrypted character to screen**, until you reach the end
of the message (do not print the terminating 0).

The decryption algorithm is as follows: you decrement the received character
code from 158 (158 - code, where code is the value returned by get_character),
and the print the result as a character.

You can test this with messages numbered 0 and 1 that are provided in
src/main.c. If the function works, these messages should translate to readable
short sentences (in English). The TMC tests have also other message numbers.

