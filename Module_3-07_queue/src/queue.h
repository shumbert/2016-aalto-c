#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue Queue;

/* Allocates and initializes a new queue.
 * 
 * Returns: pointer to an empty queue
 */
Queue *Queue_init(void);

/* Adds a new member with given student ID <id> and name <name> to the
 * end of queue <q>.
 * 
 * Returns: 1 if addition was successful, 0 if addition failed. Addition fails,
 * for example if student ID has more than 6 characters.
 */
int Queue_enqueue(Queue *q, const char *id, const char *name);

/* Returns the student ID of the first member of the queue,
 * or NULL if the queue is empty.
 */
char *Queue_firstID(Queue *q);

/* Returns the student name of the first member of the queue,
 * or NULL if the queue is empty.
 */
char *Queue_firstName(Queue *q);

/* Removes the first member of queue.
 * 
 * Returns: 1 if something was removed,
 * 0 if nothing was removed, i.e., the queue was already empty
 */
int Queue_dequeue(Queue *q);

/* Drops the given student with student ID <id> from queue <q>.
 * Only the first instance with matching ID is dropped.
 * 
 * Returns: 1 if something was removed,
 * 0 if nothing was removed, i.e., matching student ID was not found.
 */
int Queue_drop(Queue *q, const char *id);

/* Delete whole queue and all memory allocated for it
 */
void Queue_delete(Queue *q);


#endif
