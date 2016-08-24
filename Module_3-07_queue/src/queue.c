#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "queuepriv.h"

Queue *Queue_init(void)
{
    Queue *q = calloc(1, sizeof(Queue));
    return q;
}

int Queue_enqueue(Queue *q, const char *id, const char *name)
{
    if (q) {
        struct student *new = (struct student *) malloc(sizeof(struct student));
        if (new == NULL)
            return 0;

        new->name = (char *) malloc(strlen(name) + 1);
        if (new->name == NULL) {
            free(new);
            return 0;
        }

        if (strlen(id) > 6) {
            free(new->name);
            free(new);
            return 0;
        }

        strcpy(new->id, id);
        strcpy(new->name, name);
        new->next = NULL;

        if (q->last)
            q->last->next = new;
        else
            q->first = new;
        q->last = new;

        return 1;
    } else
        return 0;
}

char *Queue_firstID(Queue *q)
{
    if (q && q->first)
        return q->first->id;
    else
        return NULL;
}

char *Queue_firstName(Queue *q)
{
    if (q && q->first)
        return q->first->name;
    else
        return NULL;
}

int Queue_dequeue(Queue *q)
{
    if (q && q->first) {
        struct student *tmp = q->first;

        if (q->first == q->last) {
            q->first = NULL;
            q->last = NULL;
        } else
            q->first = q->first->next;

        free(tmp->name);
        free(tmp);
        return 1;
    } else
        return 0;
}

int Queue_drop(Queue *q, const char *id)
{
    if (q && q->first) {
        struct student *current = q->first;
        struct student *previous = NULL;
        while (current) {
            if (strcmp(current->id, id) == 0) {

                if (current == q->first)
                    q->first = q->first->next;
                else
                    previous->next = current->next;

                if (current == q->last)
                    q->last = previous;

                free(current->name);
                free(current);
                return 1;

            }
            previous = current;
            current = current->next;
        }
    }
    return 0;
}

void Queue_delete(Queue *q)
{
    if (q) {
        while(Queue_dequeue(q));
        free(q);
    }
}
