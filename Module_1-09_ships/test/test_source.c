#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "../src/ships.h"

extern struct field_st **field;

void clear_field(void)
{
    for (unsigned int y = 0; y < 10; y++) {
        for (unsigned int x = 0; x < 10; x++) {
            field[y][x].ship = NOSHIP;
        }
    }
}

void free_fields(void)
{
    for (unsigned int y = 0; y < 10; y++) {
        free(field[y]);
    }
    free(field);
}

START_TEST(test_set_ships)
{
    create_field();
    for(unsigned int i = 0; i <= 5; i++) {
        clear_field();
        set_ships(i);
        
        unsigned int count = 0;
        for (unsigned int y = 0; y < 10; y++) {
            for (unsigned int x = 0; x < 10; x++) {
                if (field[y][x].ship == SHIP) {
                    count++;
                }
            }
        }
        if (count != i * 3) {
            free_fields();
            fail("[Task 1.9.a] With %u ships, expected %u occupied positions. You have: %u",
                    i, i * 3, count);
        }
    }
    free_fields();
}
END_TEST

static void fill_func(unsigned param, struct field_st *f, char *r)
{
    int mshp[2][3] = { {'?', '?', '?'}, {'.', '+', '#'} };
    unsigned v = param % 2;
    unsigned s = (param / 2) % 3;
    f->ship = mshp[1][s];
    f->vis = v;
    *r = mshp[v][s];
}

START_TEST(test_print_field)
{
    char refbuf[400] = { 0 };
    
    create_field();
    
    int refptr = 0;
    for (unsigned int y = 0; y < 10; y++) {
        for (unsigned int x = 0; x < 10; x++)
            fill_func((x + y) ^ (y << x), &field[y][x], refbuf + refptr++);
        refbuf[refptr++] = '\n';
    }
    
    freopen("mockoutput", "w", stdout);
    print_field();
    fclose(stdout);
    
    FILE *fp = fopen("mockoutput", "r");
    char str[400] = { 0 };
    fread(str, 399, 1, fp);
    fclose(fp);
    char infostr[100] = "";
    
    int ret = mycompare(str, refbuf, infostr);
    free_fields();
    fail_unless(!ret, "[Task 1.9.b] Your output:\n%s\nReference output:\n%s\nReason: %s\n",
            str, refbuf, infostr);
    
}
END_TEST

int try_shoot(unsigned int px, unsigned int py, int expected, char *str)
{
    char mshp[3][3] = { {'+', '#', '.'}, {'.', '+', '+'}, {'.', '+', '.'} };
    
    create_field();
    
    for (unsigned int y = 0; y < 10; y++) {
        for (unsigned int x = 0; x < 10; x++) {
            field[y][x].ship = mshp[y % 3][x % 3];
            field[y][x].vis = 0;
        }
    }   
    
    FILE *mock_input = freopen("mockinput", "w+", stdin);
    fprintf(mock_input, "%u %u", px, py);
    fseek(mock_input, 0, SEEK_SET);
    int ret = shoot();
    fclose(mock_input);
    
    if (expected == -1) {
        if (ret != -1) {
            sprintf(str, "When entering invalid coordinates (%u,%u), you returned %d. Should return %d",
                    px, py, ret, -1);
            free_fields();
            return 0;
        }
        for (unsigned int y = 0; y < 10; y++) {
            for (unsigned int x = 0; x < 10; x++) {
                if (field[y][x].vis != 0) {
                    sprintf(str, "Should not check field on invalid coordinates (%u,%u)", px, py);
                    free_fields();
                    return 0;
                }
                if (field[y][x].ship != mshp[y % 3][x % 3]) {
                    sprintf(str, "Should not modify game field on invalid coordinates (%u,%u)", px, py);
                    free_fields();
                    return 0;
                }
            }
        }
    } else {
        if (!(ret == 0 || ret == 1)) {
            sprintf(str, "When entering valid coordinates (%u,%u), you returned %d. Should return 0 or 1",
                    px, py, ret);
            free_fields();
            return 0;
        }
        if (field[py][px].vis == 0) {
            sprintf(str, "When shooting position (%u, %u), it should be marked checked.", px, py);
            free_fields();
            return 0;
        }
        char c = mshp[py % 3][px % 3];
        if (c == '.') {
            if (field[py][px].ship != '.') {
                sprintf(str, "When shooting position (%u, %u) with no ship, the location should not be modified.",
                        px, py);
                free_fields();
                return 0;
            }
            if (ret != 0) {
                sprintf(str, "When shooting position (%u, %u) with no ship, function should return 0.",
                        px, py);
                free_fields();
                return 0;
            }
        }
        if (c == '+' || c == '#') {
            if (field[py][px].ship != '#') {
                sprintf(str, "When shooting position (%u, %u) with ship, the location should be marked as hit.",
                        px, py);
                free_fields();
                return 0;
            }
            if (ret != 1) {
                sprintf(str, "When shooting position (%u, %u) with ship, function should return 1.",
                        px, py);
                free_fields();
                return 0;
            }
        }
        for (unsigned int y = 0; y < 10; y++) {
            for (unsigned int x = 0; x < 10; x++) {
                if (x != px || y != py) {
                    if (field[y][x].vis != 0) {
                        sprintf(str, "When shooting position (%u,%u), location (%u,%u) should not become checked",
                                px, py, x, y);
                        free_fields();
                        return 0;
                    }
                    if (field[y][x].ship != mshp[y % 3][x % 3]) {
                        sprintf(str, "When shooting position (%u,%u), should not modify location (%u,%u)",
                                px, py, x, y);
                        free_fields();
                        return 0;
                    }
                }
            }
        }   
    }
    
    return 1;
}

START_TEST(test_shoot)
{
    
    int scoords[][3] = { {100, 100, -1}, {1 , 1, '#'}, {2, 0, '.'}, {2, 1, '#'} };
    
    char infostr[100];
    for (int i = 0; i < 4; i++) {
        memset(infostr, 0, sizeof(infostr));
        if (!try_shoot(scoords[i][0], scoords[i][1], scoords[i][2], infostr)) {
            fail("[Task 1.9.c] %s", infostr);
        }
    }
}
END_TEST

START_TEST(test_game_over)
{
    for (unsigned int n = 1; n <= 5; n++) {
        create_field();
        set_ships(n);
        
        unsigned int count = (n * 3) - 2;
        unsigned int y = 0, x = 0;
        unsigned int orcount = count;
        while (count) {
            if (field[y][x].ship == '+') {
                field[y][x].ship = '#';
                field[y][x].vis = 1;
                count--;
            }
            x++;
            if (x >= 10) {
                x = 0;
                y++;
            }
            if (y >= 10)
                break;
        }
        if (count) {
            free_fields();
            fail("[Task 1.9.d] function set_ships not implemented correctly.");
        }
        
        int ret = game_over(n);
        if (ret != 0) {
            free_fields();
            fail("[Task 1.9.d] Game was reported over when %u ship positions were not hit.",
                    n * 3 - orcount);
        }
        while (y < 10) {
            if (field[y][x].ship == '+') {
                field[y][x].ship = '#';
                field[y][x].vis = 1;
            }
            x++;
            if (x >= 10) {
                x = 0;
                y++;
            }
        }
        ret = game_over(n);
        if (ret == 0) {
            free_fields();
            fail("[Task 1.9.d] Game was not reported over when all ships were sunk.");
        }
    }
}
END_TEST

int main(int argc, const char *argv[]) {
    srand((unsigned) time(NULL));
    Suite *s = suite_create("Test-09-ships");

    tmc_register_test(s, test_set_ships, "M1.09.a");
    tmc_register_test(s, test_print_field, "M1.09.b");
    tmc_register_test(s, test_shoot, "M1.09.c");
    tmc_register_test(s, test_game_over, "M1.09.d");

    return tmc_run_tests(argc, argv, s);
}
