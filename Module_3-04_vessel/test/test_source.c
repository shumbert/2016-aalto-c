#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/source.h"

struct cargo* create_cargo() {
    char *titles[] = { "Bananas", "Apples", "Strawberries", "Cars", "People" };
    int quantities[] = { 3, 1, 10000000, 29, 18 };
    double weights[] = { 7.5, 80.7, 3.13, 459680.5436, 1045.456};

    struct cargo* c = malloc(sizeof(struct cargo));
    c->title = titles[rand()%5];
    c->quantity = quantities[rand()%5];
    c->weight = weights[rand()%5];

    return c;
}

START_TEST(test_create_vessel) {
    srand(time(0));
    struct cargo *c = create_cargo();

    char *names[] = { "Mariella", "Cargoship", "XRPS", "Symphony" };
    double lengths[] = { 154.5, 455.7, 345.15, 480.65, 235.06 };
    double depths[] = { 34.6, 76.4, 85.5, 14.8, 56.9 };

    char* name = names[rand()%4];
    double length = lengths[rand()%5];
    double depth = depths[rand()%5];

    struct vessel v = create_vessel(name, length, depth, *c);

    if(strcmp(v.name, name)) {
        fail("[M3.04] Wrong name! Given was %s, you had %s", name, v.name);
        free(c);
    }
    if(v.length != length) {
        fail("[M3.04] Wrong length! Given was %f, you had %f", length, v.length);
        free(c);
    }
    if(v.depth != depth) {
        fail("[M3.04] Wrong depth! Given was %f, you had %f", depth, v.depth);
        free(c);
    }

    if(strcmp(v.crg.title, c->title)) {
        fail("[M3.04] Wrong cargo title! Given was %s, you had %s", c->title, v.crg.title);
        free(c);
    }
    if(v.crg.weight != c->weight) {
        fail("[M3.04] Wrong cargo weight! Given was %f, you had %f", c->weight, v.crg.weight);
        free(c);
    }
    if(v.crg.quantity != c->quantity) {
        fail("[M3.04] Wrong cargo quantity! Given was %d, you had %d", c->quantity, v.crg.quantity);
        free(c);
    }

    const char *longname = "Too_long_name_for_30_chars_lalalalallalalala";
    const char *longright = "Too_long_name_for_30_chars_lal";
    struct vessel v2 = create_vessel(longname, length, depth, *c);

    if(strcmp(v2.name, longright)) {
        fail("[M3.04] Wrong resulting name trying to create vessel named %s. Expected %s, you had %s",
	     longname, longright, v2.name);
        free(c);
    }

    free(c);
}
END_TEST

START_TEST(test_print_vessel) {
    char stu[2048];
    char mod[2048];
    memset(stu, 0, 2048);
    memset(mod, 0, 2048);

    srand(time(0));
    struct cargo *c = create_cargo();

    char *names[] = { "Mariella", "Cargoship", "XRPS", "Symphony" };
    double lengths[] = { 154.5, 455.7, 345.15, 480.65, 235.06 };
    double depths[] = { 34.6, 76.4, 85.5, 14.8, 56.9 };

    char* name = names[rand()%4];
    double length = lengths[rand()%5];
    double depth = depths[rand()%5];

    struct vessel v = create_vessel(name, length, depth, *c);

    freopen("mockoutput", "w", stdout);
    print_vessel(&v); 
    read_stdout(stu, 2048);

    sprintf(mod, "%s\n%.1f\n%.1f\n%s\n%d\n%.1f\n", v.name, v.length, v.depth, v.crg.title, v.crg.quantity, v.crg.weight);

    char infostr[100] = "";
    if (mycompare(stu, mod, infostr)) {
        free(c);
        fail("[M3.04] Wrong print output! Your output:\n%s\nReference output:\n%s\nReason: %s\n",
               stu, mod, infostr);
    }
    free(c);
}
END_TEST

int main(int argc, const char *argv[]) {
    srand((unsigned) time(NULL));
    Suite *s = suite_create("Test-04_join");

    tmc_register_test(s, test_create_vessel, "M3.04");
    tmc_register_test(s, test_print_vessel, "M3.04");

    return tmc_run_tests(argc, argv, s);
}
