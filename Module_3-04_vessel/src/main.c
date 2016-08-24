#include <string.h>
#include <stdio.h>
#include "source.h"

int main()
{
    /* testing exercise. Feel free to modify */
    struct cargo c = { "Bananas", 10000, 1500 };

    struct vessel v = create_vessel( "Apinalaiva", 180, 8.5, c );

    printf("Length of the name: %lu\n", strlen(v.name));

    // shortening the name, if it is very long
    v.name[19] = 0;

    if (v.length < 1)
	printf("Length is too short!\n");

    if (v.depth > 100)
	printf("Submarines not allowed\n");

    printf("cargo: %s\n", v.crg.title);

    print_vessel(&v);

    const char *longname = "Too_long_name_for_30_chars_lalalalallalalala";
    struct vessel v2 = create_vessel(longname, 180, 8.5, c);
    print_vessel(&v2);
}
