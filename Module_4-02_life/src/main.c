#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gameoflife.h"


int main(void)
{
    /* Feel free to modify this function to test different things */

    // re-seed random number generator
    srand((unsigned)time(NULL));

    Field *f = createField(20,10);
    initField(f, 90);

    unsigned int round = 0;

    /* The below loop runs through the generations, expecting one line of
     * input from user after each generation. */
    while (1) {
        char buf[8];
        printf("Round: %u\n", round++);
        printField(f);
        fgets(buf, sizeof(buf), stdin);  // just wait user to press enter
        tick(f);
    }
    releaseField(f);
}
