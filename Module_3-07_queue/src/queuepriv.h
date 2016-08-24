#ifndef QUEUEPRIV_H
#define QUEUEPRIV_H

#include "queue.h"

/* One student in linked list*/
struct student {
    char id[7];  // student ID: 6 characters + '\0'
    char *name;  // Name of student, allocated dynamically
    struct student *next;  // next student in linked list
};

/* For storing the first and last item in linked list
 * If list is empty, both <first> and <last> are NULL
 * If list has one element, <first> and <last> point to the same place
 */
struct queue {
    struct student *first;
    struct student *last;
};

#endif
