/* userif.c -- interacting with user, showing map and other output
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "dungeon.h"

/* Determine what character to show on the given map position.
 * 
 * Parameters:
 * game: the game state
 * x,y: map coordinates
 * 
 * Returns: character to be displayed
 */
char locationChar(const Game *game, int x, int y)
{
	const Map *map = &game->map;
	char c = '?';
	switch(map->tile[y][x]) {
	case TILE_WALL:
		c = '#';
		break;
	case TILE_OPEN:
		c = '.';
		break;
	case TILE_ROOM:
		c = '.';
		break;
	}

        for (unsigned int i = 0; i < game->numMonsters; i++) {
            if (game->monsters[i].pos.x == x && game->monsters[i].pos.y == y) {
                c = game->monsters[i].sign;
                break;
            }
        }
	
	if (game->position.x == x && game->position.y == y) {
		c = '*';
	}
	return c;
}


/* Show full map, without adhering to the visibility rules
 */
void printMap(const Game *game)
{
    const Options *opt = &game->opts;
	for (int i = 0; i < (int) opt->mapHeight; i++) {
		for (int j = 0; j < (int) opt->mapWidth; j++) {
			char c = locationChar(game, j, i);
			printf("%c", c);
		}
		printf("\n");
	}
}

// determine whether x1,y1 is within line of sight from x0,y0
// (assume |x1-x0| > |y1-y0|)
int isVisibleX(const Map *map,int x0, int x1, int y0, int y1)
{
	int x = x0;
	int y = y0;
	int dx = (x1 >= x0) ? 1 : -1;
	float cy = y0;
	int vis = 1;
	while (x != x1) {
		float dy = ((float)y1 - y) / abs(x1 - x);
		if (!vis) return 0;
		if (map->tile[y][x] == TILE_WALL) {
			vis = 0;
		}
		if (dy < 0)
			cy += ceil(dy);
		else
			cy += floor(dy);
		y = cy;
		x += dx;
	}
	return vis;
}

// determine whether x1,y1 is within line of sight from x0,y0
// (assume |y1-y0| > |x1-x0|)
int isVisibleY(const Map *map,int x0, int x1, int y0, int y1)
{
	int x = x0;
	int y = y0;
	int dy = (y1 >= y0) ? 1 : -1;
	float cx = x0;
	int vis = 1;
	while (y != y1) {
		float dx = ((float)x1 - x) / abs(y1 - y);
		if (!vis) return 0;
		if (map->tile[y][x] == TILE_WALL) {
			vis = 0;
		}
		if (dx < 0)
			cx += ceil(dx);
		else
			cx += floor(dx);
		x = cx;
		y += dy;
	}
	return vis;
}

// Crude algorithm for determining whether x1,y1 is within line of sight from x0,y0
int isVisible(const Map *map, int x0, int x1, int y0, int y1)
{
	if (x0 == x1 && y0 == y1)
		return 1;

	if (abs(x1-x0) > abs(y1-y0)) {
		return(isVisibleX(map, x0, x1, y0, y1));
	} else {
		return(isVisibleY(map, x0, x1, y0, y1));
	}
}


/* Show map around character, adhering to the visibility rules
 */
void printMe(const Game *game)
{      
    const Options *opt = &game->opts;
	for (int i = game->position.y - (int)opt->visibility; 
	     i <= game->position.y + (int)opt->visibility; i++) {
		for (int j = game->position.x - (int)opt->visibility;
		     j <= game->position.x + (int)opt->visibility; j++) {
			char c = ' ';
			if (i >= 0 && i < (int) opt->mapHeight &&
			    j >= 0 && j < (int) opt->mapWidth) {
				if (isVisible(&game->map, game->position.x, j,
					      game->position.y, i))
					c = locationChar(game, j, i);
			}
			printf("%c", c);
		}
		printf("\n");
	}
}

/* Exercise (a)
 *
 * Returns 1, if player character is not allowed to move to
 * given position (x,y). Returns 0, if moving is allowed
 */
int isBlocked(Game *game, int x, int y)
{
	(void) game;
	(void) x;
	(void) y;
    return 0;
}

/* Attack the given monster
 */
void attackMonster(Creature *monst)
{
    int hitprob = 50;
    int maxdam = 4;
    if (rand() % 100 < hitprob) {
        printf("Hit! ");
        int dam = rand() % maxdam + 1;
        printf("Damage: %d ", dam);
        monst->hp = monst->hp - dam;
        if (monst->hp <= 0) {
            printf("Monster died!");
            monst->pos.x = -1;
            monst->pos.y = -1;
        } else {
            printf("Monster HP: %d (%d) ", (int)monst->hp, monst->maxhp);
        }

    } else {
        printf("Miss!");
    }
}

/* Check if there is monster in given location.
 * If yes, attack it.
 */
int checkMonster(Game *game, int x, int y)
{
    Creature *monst = game->monsters;
    for (unsigned int i = 0; i < game->numMonsters; i++) {
        if (monst[i].pos.x == x && monst[i].pos.y == y) {
            printf("Attacking monster! ");
            attackMonster(&monst[i]);
            printf("\n");
            return 1;
        }
    }
    return 0;
}

/* Move to given location, if possible
 */
void moveIfCan(Game *game, int x, int y)
{
    if (checkMonster(game, x, y)) {
        return;
    }
    if (!isBlocked(game, x, y)) {
        game->position.x = x;
        game->position.y = y;
    } else {
        printf("Blocked\n");
    }
}

/* Show map and player hit points
 * Either full map is shown, or just the visible portion around player,
 * depending on opts.showAll value
 */
void showMap(const Game *game)
{
    if (game->opts.showAll) {
        printMap(game);
    } else {
        printMe(game);
    }
    printf("HP: %d(%d)\n", (int)game->hp, game->maxhp);
}

/* Parse command given by user
 * 
 * Parameters:
 * game: game state
 * buf: one line read from user
 * 
 * Returns: 1, if game continues; 0 if game ends
 */
int doCommand(Game *game, char *buf)
{
    int newx = game->position.x;
    int newy = game->position.y;
    switch(tolower((int)buf[0])) {
	case 'n':
		newy--;
		break;
	case 's':
		newy++;
		break;
	case 'w':
		newx--;
		break;
	case 'e':
		newx++;
		break;
        case 'q':
                return 0; // game over
                
	default:
		printf("what???\n");
		break;
	}
        moveIfCan(game, newx, newy);
        monsterAction(game);
        checkIntent(game);
        if (game->hp <= 0)
            return 0;  // game over!
        if (game->hp < game->maxhp)
            game->hp = game->hp + 0.1;  // heals a bit every turn
        
        return 1;
}

