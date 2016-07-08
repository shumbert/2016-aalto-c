#include <stdio.h>
#include <string.h>
#include "source.h"

int main()
{
    
    /* Korsoroi */
    char buf[100], dest[200];
    do {
        fgets(buf, 100, stdin);
        korsoroi(dest, buf);
        printf("korsoroi: %s\n", dest);
    } while (strlen(buf) > 1);
    
    return 0;
}
