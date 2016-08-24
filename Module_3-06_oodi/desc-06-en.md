title: Oodi
task_id: 06_oodi
points: 3

**Objective:** Practice use of data structures, as a member of
  dynamically allocated (and re-sized) array.

Implement a simplified database for storing course grades. Each
database record is specified as `struct oodi`, and the database is
built as a dynamically allocated array, that contains a number of
consecutive **struct oodi** instances in a contiguous positions in
memory that needs to be dynamically allocated. Every time a new
element is added to the array, it needs to be reallocated to have
sufficient space for all entries.

**struct oodi** definition, and the purpose of each field in the
structure are defined in file `oodi.h`. Pay attention to which
structure members are allocated as part of the structure definition,
and which need to be allocated separately. For example, member
`course` is a dynamically allocated string.

The exercise consists of 4 subtasks, each worth of one exercise point
as follows. It is recommended that you implement the subtasks in
order, because tests of later subtasks depend on the earlier
implemented functions. You can also test and submit the exercise
after each subtask, to make testing easier, and to gain part of the
points.

(a) Initialize student record
-------------------------------

Implement function '**init_record**' that initializes an `struct oodi`
instance pointed by parameter '**or**'. The structure does not need to
be allocated from by this function, but the allocation is done
elsewhere. However, you need to allocate needed memory for those
structure fields that need to be allocated separately.

The function returns 1, if initialization was successful, and 0 if it
did not succeed. Initialization fails if function is called with
invalid student ID. Invalid student ID has more than 6 characters. You
can assume that any other other student ID with 6 characters or less
is valid.

(b) Add new record
--------------------

Implement function '**add_record**' that adds a new **struct oodi**
record to the dynamic array, and reallocates the array as needed. The
start of the dynamic array is given in parameter '**array**', and the
current length of the array is given in parameter '**length**'. The
new information to be added is given as parameter '**newrec**'. Note
that the content of **newrec** needs to be copied to the array. Pay
attention to which parameters are pointers and which are not.

The function returns address to the dynamic array after the
addition. This may be same or different than the pointer given in
'**array**' parameter.

(c) Change grade
------------------

Implement function '**change_grade**' that changes the grade
('**newgrade**') and completion date ('**newdate**') in one of the
existing records in the array. The record to be changed is identified
by student ID ('**p_code**') and course code ('**p_course**'). If no
record with matching student ID and course code are found, nothing is
changed. The function returns 1, if a change was made, and 0 if no
matching records were found. You can assume that there are no multiple
entries with same student ID and code.
