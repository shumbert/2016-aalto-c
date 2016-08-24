#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"

const struct stud {
    const char *id;
    const char *name;
} students[] = {
    {"123456", "Antti Ahkera" },
    {"234567", "Lasse Laiska" },
    {"777777", "Hubert Blaine Wolfeschlegelsteinhausenbergerdorff" },  // this is actual name, I googled!
    {"aaaaaaaaa", "Aku Ankka" },
    {"666666", "Dennis Ritchie" }
};

int main()
{
    /* testing exercise. Feel free to modify this function */

    Queue *q = Queue_init();
    
    for (unsigned int i = 0; i < sizeof(students) / sizeof(struct stud); i++) {
        if (Queue_enqueue(q, students[i].id, students[i].name))
            printf("i = %d, firstname: %s\n", i, Queue_firstName(q));
    }
    
    Queue_drop(q, "777777");
    
    while (Queue_dequeue(q)) {
        if (Queue_firstName(q))
            printf("dequeue, firstname: %s\n", Queue_firstName(q));
        else
            printf("Queue is empty\n");
    }
    
    Queue_delete(q);
}
