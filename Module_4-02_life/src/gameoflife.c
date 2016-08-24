#include <stdio.h>
#include <stdlib.h>
#include "gameoflife.h"


/* Exercise a: Allocates needed memory for the field structure and
 * the actual game field. 'xsize' and 'ysize' indicate the horizontal and
 * vertical dimensions of the field.
 * 
 * Returns: pointer to the Field structure allocated by this function.
 */
Field *createField(unsigned int xsize, unsigned int ysize)
{
    Field *field = (Field *) malloc(sizeof(Field));
    if (!field)
        return NULL;

    field->xsize = xsize;
    field->ysize = ysize;
    field->cells = malloc(ysize * sizeof(State *));
    if (!field->cells) {
        releaseField(field);
        return NULL;
    }

    for (unsigned int j = 0; j < ysize; j++) {
        field->cells[j] = malloc(xsize * sizeof(State));

        if (!field->cells[j]) {
            releaseField(field);
            return NULL;
        }

        for (unsigned int i = 0; i < xsize; i++)
            field->cells[j][i] = DEAD;
    }

    return field;
}

/* Free memory allocated for field <f>.
 */
void releaseField(Field *f)
{
    if (f) {
        if (f->cells) {
            for (unsigned int j = 0; j < f->ysize; j++)
                if (f->cells[j])
                    free(f->cells[j]);
            free(f->cells);
        }
        free(f);
    }
}

/* Exercise b: Initialize game field by setting exactly <n> cells into
 * ALIVE state in the game field <f>.
 */
void initField(Field *f, unsigned int n)
{
    for (unsigned int i = 0; i < n;) {
        unsigned int x = rand() % f->xsize;
        unsigned int y = rand() % f->ysize;
        if (f->cells[y][x] == DEAD) {
            f->cells[y][x] = ALIVE;
            i++;
        }
    }
}

/* Exercise c: Output the current state of field <f>.
 */
void printField(const Field *f)
{
    for (unsigned int j = 0; j < f->ysize; j++) {
        for (unsigned int i = 0; i < f->xsize; i++)
            if (f->cells[j][i] == DEAD)
                printf(".");
            else
                printf("*");
        printf("\n");
    }
}

/* Exercise d: Advance field <f> by one generation.
 */
void tick(Field *f)
{
    // First make a copy of the field
    Field *copy = createField(f->xsize, f->ysize);
    for (unsigned int j = 0; j < f->ysize; j++)
        for (unsigned int i = 0; i < f->xsize; i++)
            copy->cells[j][i] = f->cells[j][i];

    for (unsigned int j = 0; j < f->ysize; j++)
        for (unsigned int i = 0; i < f->xsize; i++) {
            if (copy->cells[j][i] == DEAD) {
                if (aliveNeighbours(copy, i, j) == 3)
                    f->cells[j][i] = ALIVE;
            } else {
                int neighbours = aliveNeighbours(copy, i, j);
                if (neighbours < 2)
                    f->cells[j][i] = DEAD;
                if (neighbours > 3)
                    f->cells[j][i] = DEAD;
            }
        }

    releaseField(copy);
}

int aliveNeighbours(Field *f, unsigned int x, unsigned int y)
{
    int neighbours = 0;

    if (x > 0) {
        if (y > 0 && f->cells[y - 1][x - 1] == ALIVE)
                neighbours++;
        if (f->cells[y][x - 1] == ALIVE)
                neighbours++;
        if (y < (f->ysize - 1) && f->cells[y + 1][x - 1] == ALIVE)
                neighbours++;
    }

    if (y > 0 && f->cells[y - 1][x] == ALIVE)
            neighbours++;
    if (y < (f->ysize - 1) && f->cells[y + 1][x] == ALIVE)
            neighbours++;

    if (x < (f->xsize - 1)) {
        if (y > 0 && f->cells[y - 1][x + 1] == ALIVE)
                neighbours++;
        if (f->cells[y][x + 1] == ALIVE)
                neighbours++;
        if (y < (f->ysize - 1) && f->cells[y + 1][x + 1] == ALIVE)
                neighbours++;
    }

    return neighbours;
}
