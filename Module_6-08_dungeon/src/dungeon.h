#ifndef DUNGEON_H
#define DUNGEON_H

// Pair of coordinates in the 2-dimensional map
typedef struct {
	int x, y;
} Point;

// Room information. Used only in map creation
typedef struct {
	int x1, x2, y1, y2;
	unsigned int w, h;
	Point center;
} Room;

// Different tile types
typedef enum {
	TILE_OPEN,  // can be moved to
	TILE_WALL,  // cannot be moved to
	TILE_ROOM   // can be moved to
} Tile;

// 2-dimensional dynamically allocated array for the game map
// Dimensions are given in Options struct (mapWidth, mapHeight)
typedef struct {
    Tile **tile;   // tile[y][x]
} Map;

// Global game options
typedef struct {
    unsigned int numRooms;  // number of rooms on the map
    unsigned int minRoomSize;  // minimum size (diameter) of a room
    unsigned int maxRoomSize;  // maximum size (diameter) of a room
    unsigned int mapWidth;  // map width
    unsigned int mapHeight;  // map height
    unsigned int numMonsters;   // number of monster generated on map
    unsigned int visibility;  // number of squares that player sees
    int showAll;  // if 1, show the full map to player, if 0 show just 'visibility' squares
} Options;

struct game_st;
struct creature_st;

// Monster information
typedef struct creature_st {
    char name[20];  // name of the monster
    char sign;  // character that represents monster on the game display
    Point pos;  // location of the monster
    float hp;  // current hitpoints
    unsigned int maxhp;  // maximum hitpoints
    void (*move)(struct game_st *, struct creature_st *);  // current movement algorithm for monster
    void (*attack)(struct game_st *, struct creature_st *);  // current attack algorithm for monster
} Creature;

// Global data for the game
typedef struct game_st {
    Map map;
    unsigned int numMonsters;  // number of elements in 'monsters' array
    Creature *monsters;  // dynamic array of all monsters
    Point position;  // current position of the player
    float hp;  // hit points, should never be higher than 'maxhp'
    unsigned int maxhp;  // maximum hit points
    Options opts;
} Game;


/* Public functions in mapgen.c */
void generateMap(Game *game);
void freeAll(Game *game);

/* Public functions in userif.c */
int doCommand(Game *game, char *buf);
int isBlocked(Game *game, int x, int y);
void printMap(const Game *game);
void showMap(const Game *game);

/* Public functions in monster.c */
void createMonsters(Game *game);
void monsterAction(Game *game);
void checkIntent(Game *game);
void moveTowards(Game *game, Creature *monst);
void moveAway(Game *game, Creature *monst);
void attackPunch(Game *game, Creature *monst);

#endif // DUNGEON_H
