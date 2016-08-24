#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "../src/dungeon.h"

int readMap(const char *filename, Game *game) {
    Map *map = &game->map;
    //Options *opt = &game->opts;
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        return 0;
    }
    int count = 0;
    map->tile = NULL;
    char buffer[100];
    char *ret = NULL;

    do {
        map->tile = realloc(map->tile, sizeof (Tile *) * (count + 1));
        ret = fgets(buffer, sizeof (buffer), fp);
        if (ret && strlen(buffer) > 1) {
            map->tile[count] = malloc(sizeof (Tile) * strlen(buffer));
            for (unsigned int i = 0; i < strlen(buffer); i++) {
                switch (buffer[i]) {
                    case '.':
                        map->tile[count][i] = TILE_OPEN;
                        break;
                    case '#':
                    default:
                        map->tile[count][i] = TILE_WALL;
                        break;
                }
            }
            game->opts.mapWidth = strlen(buffer) - 1; // newline in the end
            count++;
        }
    } while (ret);
    game->opts.mapHeight = count;
    return 1;
}

void addMonster(Game *game, int x, int y) {
    game->monsters = realloc(game->monsters, sizeof (Creature) * (game->numMonsters + 1));
    Creature *m = &game->monsters[game->numMonsters];
    memset(m, 0, sizeof(Creature));
    m->pos.x = x;
    m->pos.y = y;
    m->hp = 12;
    m->maxhp = 12;
    strcpy(m->name, "test");
    m->sign = 'T';
    game->numMonsters++;
}

START_TEST(test_isBlocked) {
    Game game;
    memset(&game, 0, sizeof (game));
    if (!readMap("testmap", &game)) {
        if (!readMap("test/testmap", &game)) {
            freeAll(&game);
            fail("[M6.08.a] Failed to read the test map");
        }
    }

    //printMap(&game);

    // test wall
    int ret = isBlocked(&game, 2, 2);
    if (!ret) {
        freeAll(&game);
        fail("[M6.08.a] Testing isBlocked on wall (testmap:2,2). isBlocked returned %d, should have returned non-zero",
                ret);
    }

    // test open space
    ret = isBlocked(&game, 1, 1);
    if (ret) {
        freeAll(&game);
        fail("[M6.08.a] Testing isBlocked on open space (testmap:1,1). isBlocked returned %d, should have returned 0",
                ret);
    }

    // test out of bounds
    ret = isBlocked(&game, -1, -1);
    if (!ret) {
        freeAll(&game);
        fail("[M6.08.a] Testing isBlocked on out-of-bounds location -1,-1. isBlocked returned %d, should have returned non-zero",
                ret);
    }

    // test monster
    addMonster(&game, 1, 1);
    ret = isBlocked(&game, 1, 1);
    if (!ret) {
        freeAll(&game);
        fail("[M6.08.a] Testing isBlocked on location with monster. isBlocked returned %d, should have returned non-zero",
                ret);
    }

    freeAll(&game);
    test_complete();
}
END_TEST

START_TEST(test_createMonsters) {
    Game game;
    memset(&game, 0, sizeof (game));
    if (!readMap("testmap", &game)) {
        if (!readMap("test/testmap", &game)) {
            freeAll(&game);
            fail("[M6.08.b] Failed to read the test map");
        }
    }
    game.opts.numMonsters = 10;
    createMonsters(&game);

    // test number of monsters
    if (game.numMonsters != game.opts.numMonsters) {
        freeAll(&game);
        fail("[M6.08.b] game.numMonsters is incorrect. Was %d, should be %d",
                game.numMonsters, game.opts.numMonsters);
    }

    char buf[160];
    for (unsigned int i = 0; i < game.opts.numMonsters; i++) {
        Creature *m = &game.monsters[i];
        // monster out of bounds
        if (m->pos.x < 0 || m->pos.y < 0 ||
                m->pos.x >= (int) game.opts.mapWidth ||
                m->pos.y >= (int) game.opts.mapHeight) {
            sprintf(buf, "[M6.08.b] Monster %d location is out of bounds: (%d,%d). Map dimensions: (%d,%d)",
                    i, m->pos.x, m->pos.y, game.opts.mapWidth, game.opts.mapHeight);
            freeAll(&game);
            fail(buf);
        }

        // monster location on wall
        if (game.map.tile[m->pos.y][m->pos.x] != TILE_OPEN &&
                game.map.tile[m->pos.y][m->pos.x] != TILE_ROOM) {
            char buf2[16];
            if (game.map.tile[m->pos.y][m->pos.x] == TILE_WALL)
                strcpy(buf2, "TILE_WALL");
            else
                strcpy(buf2, "unknown");
            sprintf(buf, "[M6.08.b] Monster %d location (%d,%d) is on %s. Should be on open space",
                    i, m->pos.x, m->pos.y, buf2);
            freeAll(&game);
            fail(buf);
        }

        // two monsters on the same spot
        for (unsigned int j = 0; j < i; j++) {
            Creature *m2 = &game.monsters[j];
            if (m->pos.x == m2->pos.x && m->pos.y == m2->pos.y) {
                sprintf(buf, "[M6.08.b] Monster %d is on same location as monster %d: (%d,%d)",
                        i, j, m->pos.x, m->pos.y);
                freeAll(&game);
                fail(buf);
            }
        }

        // valid hp and maxhp
        if (m->maxhp == 0) {
            freeAll(&game);
            fail("[M6.08.b] Monster %d has invalid max HP, should be > 0", i);
        }
        if (m->hp != m->maxhp) {
            sprintf(buf, "[M6.08.b] Monster %d: HP should be initially same as max HP. HP: %d, max HP: %d",
                    i, (int) m->hp, m->maxhp);
            freeAll(&game);
            fail(buf);
        }

        // valid name and character
        if (strlen(m->name) == 0 || strlen(m->name) > 19) {
            sprintf(buf, "[M6.08.b] Monster %d should have name that has at most 19 characters. Name length: %zu",
                    i, strlen(m->name));
            freeAll(&game);
            fail(buf);
        }
        if (!isalpha((int)m->sign)) {
            sprintf(buf, "[M6.08.b] Monster %d map sign should be alphabetic character. You have: '%c'",
                    i, m->sign);
            freeAll(&game);
            fail(buf);
        }
    }
    freeAll(&game);
    test_complete();
}
END_TEST

float distance2(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

float moveDelta(Game *game, Point me, Point crea, void (*move)(struct game_st *, struct creature_st *)) {
    game->position = me;
    game->monsters[0].pos = crea;
    float origD = distance2(game->position, game->monsters[0].pos);

    move(game, &game->monsters[0]);

    float newD = distance2(game->position, game->monsters[0].pos);
    return newD - origD;
}

int moveTests(char *buf, Game *game, Point oldpos, float moveDelta) {
    if (fabsf(moveDelta) > 1.5) {
        sprintf(buf, "[M6.08.c] Monster at (%d,%d) moved more than one square. New location: (%d,%d)",
                oldpos.x, oldpos.y,
                game->monsters[0].pos.x, game->monsters[0].pos.y);
        return 0;
    }
    if (game->map.tile[game->monsters[0].pos.y][game->monsters[0].pos.x] == TILE_WALL) {
        sprintf(buf, "[M6.08.c] Monster at (%d,%d) moved to position with wall. New location: (%d,%d)",
                oldpos.x, oldpos.y,
                game->monsters[0].pos.x, game->monsters[0].pos.y);
        return 0;
    }
    if (game->numMonsters > 1) {
        if (game->monsters[0].pos.x == game->monsters[1].pos.x &&
                game->monsters[0].pos.y == game->monsters[1].pos.y) {
            sprintf(buf, "[M6.08.c] Monster at (%d,%d) moved to same square with other monster. New location: (%d,%d)",
                    oldpos.x, oldpos.y,
                    game->monsters[0].pos.x, game->monsters[0].pos.y);
            return 0;
        }
    }
    if (game->monsters[0].pos.x == game->position.x &&
            game->monsters[0].pos.y == game->position.y) {
        sprintf(buf, "[M6.08.c] Monster at (%d,%d) moved to same square with player. New location: (%d,%d)",
                oldpos.x, oldpos.y,
                game->monsters[0].pos.x, game->monsters[0].pos.y);
        return 0;
    }
    return 1;
}

START_TEST(test_moveTowards) {
    Game game;
    memset(&game, 0, sizeof (game));
    if (!readMap("testmap", &game)) {
        if (!readMap("test/testmap", &game)) {
            freeAll(&game);
            fail("[M6.08.c] Failed to read the test map");
        }
    }

    addMonster(&game, 1, 1);

    char buf[160];

    // test on open space
    Point myloc[] = {
        {1, 1},
        {1, 1},
        {5, 5}
    };
    Point crloc[] = {
        {5, 5},
        {1, 5},
        {1, 1}
    };
    float d;
    for (unsigned int i = 0; i < (sizeof (myloc) / sizeof (Point)); i++) {
        d = moveDelta(&game, myloc[i], crloc[i], moveTowards);
        if (d >= 0) {
            sprintf(buf, "[M6.08.c] Character at (%d,%d), monster at (%d,%d) did not move closer, even if it could. New location: (%d,%d)",
                    myloc[i].x, myloc[i].y, crloc[i].x, crloc[i].y,
                    game.monsters[0].pos.x, game.monsters[0].pos.y);
            freeAll(&game);
            fail(buf);
        }

        if (!moveTests(buf, &game, crloc[i], d)) {
            freeAll(&game);
            fail(buf);
        }
    }

    // test against wall
    Point p2 = {7, 2};
    d = moveDelta(&game, myloc[0], p2, moveTowards);
    if (!moveTests(buf, &game, p2, d)) {
        freeAll(&game);
        fail(buf);
    }

    // test against monster
    addMonster(&game, 1, 4);
    d = moveDelta(&game, myloc[1], crloc[1], moveTowards);
    if (!moveTests(buf, &game, p2, d)) {
        freeAll(&game);
        fail(buf);
    }
    
    // test against player
    Point p3 = {1,2};
    d = moveDelta(&game, myloc[1], p3, moveTowards);
    if (!moveTests(buf, &game, p3, d)) {
        freeAll(&game);
        fail(buf);
    }
    freeAll(&game);
    test_complete();
}
END_TEST

START_TEST(test_moveAway) {
    Game game;
    memset(&game, 0, sizeof (game));
    if (!readMap("testmap", &game)) {
        if (!readMap("test/testmap", &game)) {
            freeAll(&game);
            fail("[M6.08.d] Failed to read the test map");
        }
    }

    addMonster(&game, 1, 1);

    char buf[160];

    // test on open space
    Point myloc[] = {
        {1, 1},
        {1, 1},
        {5, 5}
    };
    Point crloc[] = {
        {3, 3},
        {1, 3},
        {3, 3}
    };
    float d;
    for (unsigned int i = 0; i < (sizeof (myloc) / sizeof (Point)); i++) {
        d = moveDelta(&game, myloc[i], crloc[i], moveAway);
        if (d <= 0) {
            sprintf(buf, "[M6.08.d] Character at (%d,%d), monster at (%d,%d) did not move further, even if it could. New location: (%d,%d)",
                    myloc[i].x, myloc[i].y, crloc[i].x, crloc[i].y,
                    game.monsters[0].pos.x, game.monsters[0].pos.y);
            freeAll(&game);
            fail(buf);
        }

        if (!moveTests(buf, &game, crloc[i], d)) {
            freeAll(&game);
            fail(buf);
        }
    }

    // test against wall
    Point p2 = {7, 2};
    d = moveDelta(&game, myloc[2], p2, moveAway);
    if (!moveTests(buf, &game, p2, d)) {
        freeAll(&game);
        fail(buf);
    }

    // test against monster
    addMonster(&game, 1, 4);
    d = moveDelta(&game, myloc[1], crloc[1], moveAway);
    if (!moveTests(buf, &game, p2, d)) {
        freeAll(&game);
        fail(buf);
    }
    
    // test against player
    Point p3 = {1,2};
    d = moveDelta(&game, myloc[1], p3, moveAway);
    if (!moveTests(buf, &game, p3, d)) {
        freeAll(&game);
        fail(buf);
    }
    freeAll(&game);
    test_complete();
}
END_TEST

void moveUp(Game *game, Creature *monst) {
    if (!game) return;  // never happens
    monst->pos.y--;
}

void moveDown(Game *game, Creature *monst) {
    if (!game) return;  // never happens
    monst->pos.y++;
}

void attackTest(Game *game, Creature *monst) {
    if (!monst) return;  // never happens
    game->hp = game->hp - 1;
}

START_TEST(test_monsterAction) {
    Game game;
    memset(&game, 0, sizeof (game));
    if (!readMap("testmap", &game)) {
        if (!readMap("test/testmap", &game)) {
            freeAll(&game);
            fail("[M6.08.e] Failed to read the test map");
        }
    }
    game.position.x = 1; game.position.y = 1;
    game.hp = 10;
    
    addMonster(&game, 1, 3);
    Creature *m = &game.monsters[0];
    m->move = moveUp;
    m->attack = attackTest;
    
    addMonster(&game, 1, 4);
    m = &game.monsters[1];
    m->move = moveDown;
    m->attack = NULL;
    
    game.opts.numMonsters = 2;
    
    // test movement
    monsterAction(&game);
    
    if (game.monsters[0].pos.y != 2) {
        freeAll(&game);
        fail("[M6.08.e] monsterAction() did not move monster 0 as expected");
    }
    
    if (game.monsters[1].pos.y != 5) {
        freeAll(&game);
        fail("[M6.08.e] monsterAction() did not move monster 1 as expected");
    }
    
    if (game.hp != 10) {
        freeAll(&game);
        fail("[M6.08.e] Monster attacked while not in adjacent square");
    }
    
    // test attack
    addMonster(&game, 2, 1);
    m = &game.monsters[2];
    m->move = NULL;
    m->attack = attackTest;
    
    game.opts.numMonsters = 3;
    
    monsterAction(&game);
    
    if (game.hp != 8) {
        freeAll(&game);
        fail("[M6.08.e] Monsters did not attack as expected, when player is nearby");
    }
    freeAll(&game);
    test_complete();
}
END_TEST

void randomMap(Game *game)
{
    game->map.tile = malloc(game->opts.mapHeight * sizeof(Tile*));
    for (unsigned int i = 0; i < game->opts.mapHeight; i++) {
        game->map.tile[i] = malloc(game->opts.mapWidth * sizeof(Tile));
        for (unsigned int j = 0; j < game->opts.mapWidth; j++) {
            if (rand() % 3) {
                game->map.tile[i][j] = TILE_OPEN;
            } else {
                game->map.tile[i][j] = TILE_WALL;
            }
        }
    }
}

int compareMap(Game *orig, Game *loaded, char *buf)
{
    int diff = 0;
    char buf2[16];
    sprintf(buf, "Loaded map differs from original (lines marked with >)\n");
    for (unsigned int i = 0; i < orig->opts.mapHeight; i++) {
        memset(buf2, 0, 16);
        if (memcmp(orig->map.tile[i], loaded->map.tile[i],
                orig->opts.mapWidth*sizeof(Tile))) {
            diff = 1;
            buf2[0] = '>';
        } else {
            buf2[0] = ' ';
        }
        
        unsigned int j;
        for (j = 0; j < orig->opts.mapWidth; j++) {
            if (loaded->map.tile[i][j] == TILE_WALL)
                buf2[j+1] = '#';
            else if (loaded->map.tile[i][j] == TILE_OPEN || loaded->map.tile[i][j] == TILE_ROOM)
                buf2[j+1] = '.';
            else
                buf2[j+1] = '?';
        }
        strcat(buf2, "   ");
        strcat(buf, buf2);
        memset(buf2, 0, 16);
        
        for (j = 0; j < orig->opts.mapWidth; j++) {
            if (orig->map.tile[i][j] == TILE_WALL)
                buf2[j] = '#';
            else if (orig->map.tile[i][j] == TILE_OPEN || orig->map.tile[i][j] == TILE_ROOM)
                buf2[j] = '.';
            else
                buf2[j] = '?';
        }
        strcat(buf2, "\n");
        strcat(buf, buf2);
    }
    return diff;
}


int main(int argc, const char *argv[]) {
    Suite *s = suite_create("Test-08_dungeon");

    tmc_init_tests();
    
    tmc_register_test(s, test_isBlocked, "M6.08.a");
    tmc_register_test(s, test_createMonsters, "M6.08.b");
    tmc_register_test(s, test_moveTowards, "M6.08.c");
    tmc_register_test(s, test_moveAway, "M6.08.d");
    tmc_register_test(s, test_monsterAction, "M6.08.e");

    return tmc_run_tests(argc, argv, s);
}
