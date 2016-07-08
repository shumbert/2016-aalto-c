#include <stdio.h>
#include <stdlib.h>
#include "ships.h"

const unsigned int xsize = 10;
const unsigned int ysize = 10;
const unsigned int shiplen = 3;

/* implement these functions */

/* Task a: Place <num> ships on the game map.
 */
void set_ships(unsigned int num)
{
    int x, y, dir;
    unsigned int placed = 0;

    while (placed < num) {
        x = rand() % xsize;
        y = rand() % ysize;
        dir = rand() % 2;

        if (place_ship(x, y, dir))
            placed++;
    }
}


/* Task b: print the game field
 */
void print_field(void)
{
    for (unsigned int j = 0; j < ysize; j++)
        for (unsigned int i = 0; i < xsize; i++) {
            if (is_visible(i, j))
                printf("%c", is_ship(i, j));
            else
                printf("?");
            if (i == (xsize - 1))
                printf("\n");
        }
}


/* Task c: Ask coordinates (two integers) from user, and shoot the location.
 * Returns -1 if user gave invalid input or coordinates, 0 if there was no ship
 * at the given location; and 1 if there was a ship hit at the location.
 */
int shoot(void)
{
    int n;
    unsigned int x, y;

    printf("Coordinates: ");
    n = scanf("%u %u", &x, &y);
    if (n != 2 || x >= xsize || y >= ysize || is_visible(x, y))
        return -1;

    if (is_ship(x, y) == '+') {
        hit_ship(x, y);
        checked(x, y);
        return 1;
    } else {
        checked(x, y);
        return 0;
    }
}

/* Task d: Returns 1 if game is over (all ships are sunk), or 0 if there
 * still are locations that have not yet been hit. <num> is the number of
 * ships on the game map. It is assumed to be the same as in the call to
 * set_ships function.
 */
int game_over(unsigned int num)
{
    unsigned int sunk = 0;
    unsigned int goal = num * shiplen;

    for (unsigned int j = 0; j < ysize; j++)
        for (unsigned int i = 0; i < xsize; i++)
            if (is_ship(i, j) == '#')
                sunk++;

    return sunk == goal;
}
