#include <stdio.h>
#include "source.h"

int main(void)
{
    /* Feel free to modify this code to test with different inputs */
    printf("Length of vector (1,2,3): %f\n", vectorlength(1,2,3));
    printf("Length of vector (1,1,1): %f\n", vectorlength(1,1,1));
    printf("Length of vector (1,0,0): %f\n", vectorlength(1,0,0));    
    printf("Length of vector (0.3, 0.3, 0.1): %f\n",
	   vectorlength(0.3, 0.3, 0.1));
}
