title: Defining a ship
task_id: 04_vessel
points: 1
last_modified: 2016-03-11 (Couple of words about pointers and use of malloc)


**Objective:** Practice definition of structures, and their basic use.

In this exercise you will need to implement three things to earn a
point 1) define a **vessel** structure; 2) implement function
**create_vessel** that creates a new vessel structure instance; and 3)
implement function **print_vessel** that prints the contents of the
vessel structure.

The vessel structure must have the following fields. It is important
that the names are correct, otherwise *src/main.c* nor the test code
will not compile.

  * *name*: name of the ship as a string. The string must be copied
    from function parameter *p_name*, you cannot directly assign
    it. The name must be modifiable, and there must be room for up to
    30 characters in name (plus the ending character '\0'). If the
    name given as function parameter is longer than 30 characters, it
    should be truncated to 30 characters long.

  * *length*: length of the ship as double floating point number (you
    could assume these are meters)

  * *depth*: depth of the ship as double floating point number (you
    can assume meters, but that's not important)

  * *crg*: cargo of the ship. This is equivalent to the content of one
    cargo structure that is given in *source.h*

The vessel structure should be defined in *source.h* so that the other
source files can find it.

*create_vessel* gets the same arguments as the vessel struct members,
 and you should use these when creating a new vessel structure. Pay
 attention to how the string argument (name) is going to be handled:
 the string must be copied.

**NOTE:** *create_vessel* returns a copy of your vessel data
  structure, which is not a pointer. The code that is outside of the
  function cannot free any memory that you have allocated, so using
  *malloc* will cause a memory leak (unless you release the memory
  right away, which is not sensible). Think whether you need pointers
  at all in this exercise.

*print_vessel* prints the *vessel* struct contents, each structure
 member in its own line, including the members of the cargo
 structure. The double type fields should be printed at the precision
 of one decimal. For example, after the functions are properly
 implemented, the example program in *src/main.c*
 would print:

<pre>
Apinalaiva
180.0
8.5
Bananas
10000
1500.0</pre>
