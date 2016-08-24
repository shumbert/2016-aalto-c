title: Election system
points: 2
task_id: 06_election


**Objective:** Refresh on file handling, dynamic arrays with
  structures, and use of algorithms.


Implement an election system that calculates votes from given
file. The system consists of two functions as follows:

a) *read_votes* that reads votes from given text file. Vote consists a
name of no more than 39 characters, each given in a separate line. See
file *src/votes.txt* for a short example. Based on the votes you
should build a dynamic array where each element is a *votes*
structure. Each name in the file should be represented only once in
the array, and associated with the count of how many times that name
was represented in file. In other words, the array has as many
elements as the file has different names. The end of the array is
indicated by an additional element that has empty string as a
name. For example with the example file the array will have four
elements, plus the ending element. This array is returned to the caller.

Note that the names **should not include the newline character** that
separates the votes in the file.

b) *results* that outputs the results of voting, using the created
dynamic array, in the screen in the following format:

`name: votes`

The results should be ordered based on the number of votes, having the
entry with most votes first. In cases where there are same number of
votes, the names are ordered according to alphabetical order. Remember
that C library contains handy helper functions for easy ordering of data.

For example, the *main.c* function should output the following with
given *src/votes.txt*:

<pre>
Trump: 4
Clinton: 2
Sanders: 2
Cruz: 1</pre>

(The example is purely fictional.)

Feel free to generate your own test files when developing the
functions. Implement functions to file *election.c* based on the
definitions in *election.h*.
