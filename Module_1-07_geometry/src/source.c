#include <stdio.h>
#include <math.h>
#include "source.h"


void multi_table(unsigned int xsize, unsigned int ysize)
{
    for (unsigned int j = 1; j <= ysize; j++)
        for (unsigned int i = 1; i <= xsize; i++) {
            printf("%4d", i * j);
            if (i == xsize)
                printf("\n");
        }
}


void draw_triangle(unsigned int size)
{
    for (unsigned int j = 1; j <= size; j++)
        for (unsigned int i = 1; i <= size; i++) {
            if (i > size - j)
                printf("#");
            else
                printf(".");
            if (i == size)
                printf("\n");
        }
}

double distance(int x, int y)
{
    return sqrt(x * x + y * y);
}


void draw_ball(unsigned int radius)
{
    for (int j = (int) -radius; j <= (int) radius; j++)
        for (int i = (int) -radius; i <= (int) radius; i++) {
            if (distance(i, j) <= radius)
                printf("*");
            else
                printf(".");
            if (i == (int) radius)
                printf("\n");
        }
}
