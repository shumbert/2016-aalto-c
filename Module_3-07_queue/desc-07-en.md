title: Exercise queue
task_id: 07_queue
points: 3

**Objective:** Practice structure and pointer manipulation together
with linked list, a common data structure in C programs.

This exercise implements a simple queue that holds student IDs and
names. The queue is implemented as an abstract data type '**Queue**',
and the functions to operate the queue are in file '**queue.c**'.
'**queue.h**' defines the public interface to the queue, and
'**queuepriv.h**' contains definitions that are internal to the queue
and should not be directly accessed from elsewhere than
'**queue.c**'. The queue is implemented as a linked list.

This variant of linked list has the pointer to the **first member** of
the queue, and another pointer to the **last member** of the queue, in
addition to the **next** pointers with each member that allow
traversing through the linked list. The **next** pointer of the last
member in the queue should always be NULL.

Initially, pointers '**first**' and '**last**' are NULL. When the list
has only one member, both '**first** and '**last**' point to the same
address. With longer lists they are different. Each new list member
should be dynamically allocated, and linked to the end of the list by
replacing the NULL pointer with the address of the new element (and
updating the '**last**' pointer. The new element, in turn, will have
NULL as its next pointer. 

Walking forward along each member of the linked list happens by
following the '**next**' pointers. After finding the last element
`(q->next == NULL)`, you will need to modify the pointer, to connect
the newly allocated node to the list (i.e., assigning the pointer you
received from dynamic memory allocation).

Some of the functions for handling the '**Queue**' type are already
implemented, but the most important operations are missing. You should
implement the following functions for the linked list.

(a) Add student to queue
-----------------

Implement function '**Queue_enqueue**' that adds a new student with
given student ID and name to the end of the queue. The function
returns 1 if addition was successful, or 0 if not. If student ID is
invalid (more than 6 characters), the function should not add
anything, and return 0. Because the length of the name is not known,
the space for it needs to be allocated dynamically. Also the space for
the new queue element needs to be dynamically allocated.

You do not need to check whether the given student is already on the
queue.

For easier debugging, it is advised that you test your code first
using the main.c executable, before giving it to the TMC tester.

(b) Remove the head of the queue
------------------

Implement function '**Queue_dequeue**' that removes the first member
of the queue, and releases all memory allocated for it. The function
returns 1, if something was removed; or 0 if nothing was removed,
i.e., because the queue was already empty. This way, the whole queue
can be removed by `while (Queue_dequeue(queue));`.

(c) Drop a specific member from queue
---------------------------------------

Implement function '**Queue_drop**' that removes the given student (as
identified by student ID) from the queue, and releases memory
allocated for it. This queue member can be located anywhere in the
queue, and after removal, the queue should remain operational, i.e.,
all the pointers should be updated accordingly.

The function returns 1, if student with matching ID was found and
removed, and 0, if there was no match, and nothing was removed. Each
call should remove only one queue member: if a student is on the queue
several times, only the first entry is removed.
