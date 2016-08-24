#include <stdio.h>
#include <stdlib.h>
#include "polisher.h"


int main(void)
{
    char *code = read_file("test/tcp_vegas.c");
    if (!code) {
        printf("No code read");
        return -1;
    }
    printf("-- Original:\n");
    fputs(code, stdout);

    //code = remove_comments(code);
    //printf("-- Comments removed:\n");
    //fputs(code, stdout);

    code = indent(code, "    ");
    printf("-- After indenting:\n");
    fputs(code, stdout);
   
    free(code);
}
