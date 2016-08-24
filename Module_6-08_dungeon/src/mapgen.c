/* mapgen.c -- Generates the game map
 * 
 * dungeon creation algorithm ported (and modified) from
 * http://gamedevelopment.tutsplus.com/tutorials/create-a-procedurally-generated-dungeon-cave-system--gamedev-10099
 */


#include <stdlib.h>
#include "dungeon.h"

/* Create a new room, with given coordinates (x,y) and dimensions (w,h)
 */
void newRoom(Room *nr, int x, int y, unsigned int w, unsigned int h) {
    /*Room *nr = malloc(sizeof (Room));
    if (!nr)
        return NULL;*/
    nr->x1 = x;
    nr->x2 = x + w;
    nr->y1 = y;
    nr->y2 = y + h;
    nr->center.x = (nr->x1 + nr->x2) / 2;
    nr->center.y = (nr->y1 + nr->y2) / 2;
    //return nr;
}

/* returns 0 if the two given rooms do not overlap, non-zero otherwise
 */
int intersects(const Room *a, const Room *b) {
    return (a->x1 <= b->x2 &&
            a->x2 >= b->x1 &&
            a->y1 <= b->y2 &&
            a->y2 >= b->y2);
}

/* Initialize the map data for a given room
 */
void initRoom(Room *nr, Map *m) {
    for (int i = nr->y1; i < nr->y2; i++) {
        for (int j = nr->x1; j < nr->x2; j++) {
            m->tile[i][j] = TILE_ROOM;
        }
    }
}

/* set up a horizontal corridor at given coordinates
 */
void hCorridor(Map *map, int x1, int x2, int y) {
    int minx = (x1 < x2 ? x1 : x2);
    int maxx = (x1 < x2 ? x2 : x1);

    for (int x = minx; x <= maxx; x++) {
        map->tile[y][x] = TILE_OPEN;
    }
}

/* Set up a vertical corridor at given coordinates
 */
void vCorridor(Map *map, int y1, int y2, int x) {
    int miny = (y1 < y2 ? y1 : y2);
    int maxy = (y1 < y2 ? y2 : y1);

    for (int y = miny; y <= maxy; y++) {
        map->tile[y][x] = TILE_OPEN;
    }
}

/* Draw corridors between two rooms
 * Start randomly either to horizontal direction or vertical direction
 */
void drawCorridors(Map *m, Room *a, Room *b) {
    if (rand() & 1) {
        hCorridor(m, a->center.x, b->center.x, a->center.y);
        vCorridor(m, a->center.y, b->center.y, b->center.x);
    } else {
        vCorridor(m, a->center.y, b->center.y, a->center.x);
        hCorridor(m, a->center.x, b->center.x, b->center.y);
    }
}

/* Place rooms on the map and create corridors between them
 */
void placeRooms(Game *game) {
    Map *map = &game->map;
    Options *opt = &game->opts;
    Room *rooms;
    rooms = malloc(sizeof (Room) * opt->numRooms);
    if (!rooms) {
        // No use going on
        exit(EXIT_FAILURE);
    }
        
    int failed = 1;
    for (unsigned int i = 0; i < opt->numRooms; i++) {
        do {
            unsigned int w = opt->minRoomSize + rand() % (opt->maxRoomSize - opt->minRoomSize);
            unsigned int h = opt->minRoomSize + rand() % (opt->maxRoomSize - opt->minRoomSize);
            int x = rand() % (opt->mapWidth - w - 1) + 1;
            int y = rand() % (opt->mapHeight - h - 1) + 1;
            newRoom(&rooms[i], x, y, w, h);

            failed = 0;
            for (unsigned int j = 0; j < i; j++) {
                // if overlaps with another room, have to pick another location
                if (intersects(&rooms[i], &rooms[j])) {
                    failed = 1;
                    break;
                }
            }
            if (!failed) {
                initRoom(&rooms[i], map);
                if (i > 0)
                    drawCorridors(map, &rooms[i - 1], &rooms[i]);
                //rooms[i] = nr;
            }
        } while (failed);
    }
    // Player is initially placed in the center of first room
    game->position = rooms[0].center;
    free(rooms);  // not needed anymore
}

/* Generate game map by first filling everything as wall, then using
 * placeRooms above, to create rooms and corridors
 */
void generateMap(Game *game) {
    Map *map = &game->map;
    Options *opt = &game->opts;

    map->tile = malloc(sizeof (Tile *) * opt->mapHeight);
    for (unsigned int i = 0; i < opt->mapHeight; i++) {
        map->tile[i] = malloc(sizeof (Tile) * opt->mapWidth);
        for (unsigned int j = 0; j < opt->mapWidth; j++) {
            map->tile[i][j] = TILE_WALL;
        }
    }
    placeRooms(game);
}

/* Free all dynamically allocated memory
 */
void freeAll(Game *game) {
    if (game->map.tile) {
        for (unsigned int i = 0; i < game->opts.mapHeight; i++) {
            free(game->map.tile[i]);
        }
        free(game->map.tile);
    }
    if (game->monsters)
        free(game->monsters);
}
