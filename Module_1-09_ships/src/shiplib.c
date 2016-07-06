#include <stdio.h>
#include <stdlib.h>
#include "ships.h"

/* DO NOT MODIFY THE FUNCTIONS IN THIS FILE */

extern unsigned int xsize;
extern unsigned int ysize;
extern unsigned int shiplen;

struct field_st **field;


/* Creates an empty game field that is <xsize> wide and <ysize> tall.
 * By default <xsize> and <ysize> are 10 squares.
 * Optimistically assumes that the function always succeeds.
 */
void create_field(void)
{
    field = malloc(ysize * sizeof(*field));
    for (unsigned int i = 0; i < ysize; i++) {
        field[i] = malloc(xsize * sizeof(**field));
        for (unsigned int j = 0; j < xsize; j++) {
            field[i][j].ship = NOSHIP;
            field[i][j].vis = 0;
        }
    }
}


/* Places a single ship on the game field. Each ship is 3 squares tall.
 * The ship is placed on location <xp>, <yp>.
 * <dir> determines whether the ship is horizontally or vertically aligned:
 * value 0 means horizontal ship, value 1 means vertical ship.
 * Returns 0 if creation failed and 1 if creation of ship was succesful.
 */
int place_ship(unsigned int xp, unsigned int yp, int dir)
{
    if (dir != 0 && dir != 1)
        return 0;
    
    // horizontal ship
    if (dir == 0) {    
        if (yp >= ysize || xp >= xsize || xp + shiplen >= xsize) // out of bounds?
            return 0;
        
        // check that the position is free
        for (unsigned int x = xp; x < xp + shiplen; x++) {
            if (field[yp][x].ship == SHIP)
                return 0;
        }
        // set ship
        for (unsigned int x = xp; x < xp + shiplen; x++) {
            field[yp][x].ship = SHIP;
        }
    }
    
    // vertical ship
    if (dir == 1) {
        // out of bounds?
        if (xp >= xsize || yp >= ysize || yp + shiplen >= ysize)
            return 0;
        
        // check that the position is free
        for (unsigned int y = yp; y < yp + shiplen; y++) {
            if (field[y][xp].ship == SHIP)
                return 0;
        }
        // set ship
        for (unsigned int y = yp; y < yp + shiplen; y++) {
            field[y][xp].ship = SHIP;
        }
    }
    return 1;
}

/* Returns 1 if location <x>,<y> is visible to player (i.e., it has been tried
 * at least once before). Returns 0 if location is not visible.
 */
int is_visible(unsigned int x, unsigned int y)
{
    if (x >= xsize || y >= ysize)
        return 0;
    
    return field[y][x].vis;
}

/* Returns the whether there is a ship on given location <x>,<y>.
 * The function returns a character that can be used in printout, if sector
 * is visible. Following characters are used:
 * '.' -- location does not have a ship.
 * '+' -- location has (part of) a ship that is not yet hit.
 * '#' -- location has (part of) a ship that has been hit.
 */
char is_ship(unsigned int x, unsigned int y)
{
    if (x >= xsize || y >= ysize)
        return '.';
    
    return field[y][x].ship;
}

/* Marks ship at location <x>,<y> as hit.
 * You must check before this call that the location indeed has a ship
 */
void hit_ship(unsigned int x, unsigned int y)
{
    if (x >= xsize || y >= ysize)
        return;
    
    field[y][x].ship = SUNKEN;
}

/* Marks location <x>,<y> as checked, i.e., it becomes visible to the player.
 */
void checked(unsigned int x, unsigned int y)
{
    if (x >= xsize || y >= ysize)
        return;
    
    field[y][x].vis = 1;
}
