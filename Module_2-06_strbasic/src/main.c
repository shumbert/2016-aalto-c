#include <stdio.h>
#include <string.h>
#include "source.h"

int main()
{
    /* Count alpha */
    char *str = "How many alpha in this string?";
    printf("count_alpha: %d\n", count_alpha(str));

    /* Count substr */
    char str2[] = "one two one twotwo three";
    printf("count_substr: %d\n", count_substr(str2, "two"));
        
    return 0;
}
