title: Array tool
task_id: 04_arraytool
points: 3


**Objective:** Practice use of parametrized macros, for operating with
  arrays (of generic type).

This exercise does not contain other *.c files than main.c (and the
test sources in test directory). Instead, the relevant code you'll
need to implement is in src/arraytool.h header, where you need to
place the following three macros:

**Exercise (a): CHECK(cond, msg)** that will check logical condition
  **cond**, and if the condition fails, output string **msg** to
  standard output stream. This is like the **assert** macro, but
  does not terminate the execution of the program if condition
  fails. Example: `CHECK(5 > 10, "5 > 10 failed\n");`

**Exercise (b): MAKE_ARRAY(type, n)** that will create a dynamically
  allocated array, that contains **n** obejcts of type
  **type**. The macro returns pointer to the allocated
  memory. Example: `void *ptr = MAKE_ARRAY(int, 10);`

**Exercise (c): ARRAY_IDX(type, array, i)** that will access the
  given **array** at index **i** (count starting from 0, as
  always), with given <b>type</b>. Example: `ARRAY_IDX(int, ptr,
  i) = i * 2;`

When the three macros are correctly implemented, src/main.c should
allocate an int array for 10 members, initialize it, and print its
contents. The main function also demonstrates the use of CHECK macro
with failing condition.
