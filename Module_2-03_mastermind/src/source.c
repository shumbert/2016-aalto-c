#include <stdio.h>
#include "source.h"


#ifndef MAWKKE
// longer solution by Pasi

/* 03-mastermind
 */
void mastermind(const int *solution, const int *guess, char *result, unsigned int len)
{
    for (unsigned int i = 0; i < len; i++) {
        result[i] = '-';
        if (guess[i] == solution[i])
            result[i] = '+';
        else {
            for (unsigned int j = 0; j < len; j++)
                if (guess[i] == solution[j]) {
                    result[i] = '*';
                    break;
                }
        }
    }
}
#endif
