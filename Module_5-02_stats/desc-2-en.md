title: File statistics
task_id: 02_stats
points: 2


**Objective:** More practice on file processing

Implement functions to calculate the following metrics from a given
file:

(a) Line count
----------------

Implement function `int line_count(const char *filename)`
that calculates the number of lines in the given file, and returns the
line count. If there is an error, the function should return -1. Empty
file is considered to have no lines. If the last line of the file is
not empty, it should be counted as a line even if it does not end in
newline character.

(b) Word count
----------------

Implement function `int word_count(const char *filename)`
that calculates the number of words in the given file and returns the
word count. In this exercise we define word like this: Word is a
substring that contains at least one **alphabetic** character. Two
words are separated by one or more **whitespace** characters. If
there is an error, the function should return -1. (Note that shell
command 'wc -w' defines a "word" differently, and cannot be used to
compare results with this function)
