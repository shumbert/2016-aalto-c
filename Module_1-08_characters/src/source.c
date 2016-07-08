#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "source.h"

/* Don't touch the definition of msgs array! Checker uses this. */
char *msgs[10] = {
    "'6=*w+~)._", "J65+~5+~=0/*69,~+9;,9*~19++=79"
};


void ascii_chart(char min, char max)
{
    int i = 0;
    for (int x = (int) min; x <= (int) max; x++) {
        if (isprint((char) x))
            printf("%3d 0x%x %c", x, x, (char) x);
        else
            printf("%3d 0x%x ?", x, x);
        if (i == 3) {
            printf("\n");
            i = 0;
        } else {
            printf("\t");
            i++;
        }
    }
}

char get_character(int msg, unsigned int cc) {
    if (msg >= 10 || !msgs[msg])
        return 0;

    if (strlen(msgs[msg]) <= cc)
        return 0;
    
    return msgs[msg][cc];
}


void secret_msg(int msg)
{
    char c;
    int cc = 0;

    while ((c = get_character(msg, cc++)) != '\0')
        printf("%c", 158 - c);
}
