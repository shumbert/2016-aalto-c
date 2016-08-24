/* main.c -- the main operation loop for the dungeon game
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "dungeon.h"


/* Sets global options for the game (map size, num. of monsters, etc.)
 * 
 * Parameters:
 * game: the game state
 * argc: number of command line arguments
 * argv: array of command line arguments
 */
void setOptions(Game *game, int argc, char **argv)
{
	(void) argc;
	(void) argv;
    Options *opt = &game->opts;
    opt->numRooms = 12;
    opt->minRoomSize = 3;
    opt->maxRoomSize = 8;
    opt->mapWidth = 70;
    opt->mapHeight = 40;
    opt->numMonsters = 10;
    opt->visibility = 5;
    opt->showAll = 0;
}


int main(int argc, char **argv)
{
	Game game;
        memset(&game, 0, sizeof(game));
	srand((unsigned)time(NULL));
	//srand(1);
        setOptions(&game, argc, argv);
        if (game.map.tile == NULL) {
            // NULL, unless setOptions loaded previous game
	    generateMap(&game);
            createMonsters(&game);
            game.maxhp = 12;
            game.hp = game.maxhp;
        }
        int gameOn = 1;
        while(gameOn) {
		char buffer[80];
		showMap(&game);
		printf("command >");
		fgets(buffer, sizeof(buffer), stdin);
		gameOn = doCommand(&game, buffer);
	}
	freeAll(&game);
}
