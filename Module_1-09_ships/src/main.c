#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "ships.h"

int main()
{
    // Re-seed random number generator using clock
    srand((unsigned) time(NULL));

    // We play with 5 ships
    unsigned int num = 5;
    create_field();
    set_ships(num);
    printf("ships set\n");
    
    // Repeat until are ships are destroyed
    while(!game_over(num)) {
        printf("new turn\n");
        print_field();
        printf("Enter coordinates: ");
        int i = shoot();
        if (i < 0) {
            printf("Invalid coordinates\n");
        } else if (i == 0) {
            printf("Miss\n");
        } else {
            printf("Hit!\n");
        }
    }
}
