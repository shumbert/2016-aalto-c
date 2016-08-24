#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strarray.h"

int main(void)
{
    char **strings = init_array();
    
    strings = add_string(strings, "oNe");
    strings = add_string(strings, "TWO");
    strings = add_string(strings, "three");
    strings = add_string(strings, "Four");
    
    print_strings(strings);
    
    make_lower(strings);
    sort_strings(strings);
    
    print_strings(strings);
    free_strings(strings);
    
    return EXIT_SUCCESS;
}
