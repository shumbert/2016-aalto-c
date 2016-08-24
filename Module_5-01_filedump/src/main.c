#include <stdio.h>
#include <string.h>
#include "fileread.h"


int main(void)
{
    if (textdump("main.c") == -1) {
        if (textdump("src/main.c") == -1) {
            fprintf(stderr, "Could not open main.c\n");
        }
    }
    
    printf("\n");
    
    if (hexdump("main.c") == -1) {
        if (hexdump("src/main.c") == -1) {
            fprintf(stderr, "Could not open main.c\n");
        }
    }
}
