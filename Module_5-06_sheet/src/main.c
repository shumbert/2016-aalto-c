#include <stdio.h>
#include "spreadsheet.h"

int main(void)
{
    Sheet *s = create_sheet(8,16);

    while (1) {
        char buf[40];
        print_sheet(s);
        printf("Syntax: XY <value>  --OR--  XY <func> UL DR\n");
        fgets(buf, sizeof(buf), stdin);
        if (!parse_command(s, buf)) {
            printf("Invalid command\n");
        }
    }
}
