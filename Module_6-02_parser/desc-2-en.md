title: Command line parser
points: 2
task_id: 02_parser


**Objective:** Get familiar with command line arguments, and refresh
  your memory on linked lists.


Command line arguments are a common way to give parameters for a
program. A short summary of command line arguments and typical use of
command line options was given in [Module 4]. We will now practice
parsing the options given from the command line.

[Module 4]: ../Module_4/index.html#03_cmdline

Your code will read the command line options and store them in a
linked list of `struct option` structures. In this exercise command
line options start with '-', and are followed by alphabetical
character. Command line option may have an optional argument (string),
which is in the following element of the `argv` array if it does not
begin with the '-' character that identifies a new option. Each option can
only have at most a single argument. If an `argv` member is not an
option or its argument, it should be ignored. You will need to store
the possible option argument in a new `struct option` field that you
will add to the structure.

`struct option` is not complete: it is missing the space for option
argument, so **you will need to expand the structure**. The structure
contains place for the option character and the **next** pointer to
implement a linked list. Do not modify these fields. [Module 3]
explained linked lists, if you need a refresher on them.

[Module 3]: ../Module_3/index.html#06_linkedlist

a) Parse options
-------------------

Implement function **get_options** that will process the command line
arguments given to function, and return a pointer to the start of
linked list that contains the options. Each option on the command line
(and its optional argument) will be a separate node in the linked list.

You will also need to implement function **free_options** that
releases the dynamic memory allocated for the linked list.

b) Query options
-------------------

Implement function **is_option** that will return non-zero if the
given option character is in the options list, or zero if the option
character could not be found.

Also implement function **get_optarg** that returns the option
argument if one was provided with the given option. If the option was
not given, or if it did not have an argument, the function returns
NULL.

**src/main.c** demonstrates how these functions are used, assuming
  that you execute it from command line, giving some arguments. If you
  do not want to use the command line terminal, you will need to
  modify the main function to provide a test sequence of command line
  arguments.
