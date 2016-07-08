#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "source.h"

int main()
{
    /* 03-mastermind */
    int sol[6], guess[6];
    char result[7];
    srand((unsigned) time(NULL));
    for (int i = 0; i < 6; i++) {
        sol[i] = rand() % 10;
        // uncomment below, if you want to cheat (or test)
        //printf("%d ", sol[i]);
    }
    unsigned int attempts = 10;
    do {
        printf("\nAttempts remaining: %d -- give 6 numbers: ", attempts);
        for (int i = 0; i < 6; i++)
            scanf("%d", &guess[i]);
        mastermind(sol, guess, result, 6);
        result[6] = 0;
        printf("  Result: %s", result);
    } while (attempts-- && strcmp(result, "++++++"));

    return 0;
}
