#include <stdio.h>
#include <string.h>
#include "source.h"


struct vessel create_vessel(const char *p_name,
			    double p_length,
			    double p_depth,
			    struct cargo p_crg)
{
    struct vessel v;

    strncpy(v.name, p_name, 30);
    v.name[30] = '\0';
    v.length = p_length;
    v.depth = p_depth;
    v.crg = p_crg;

    return v;
}

void print_vessel(const struct vessel *ship)
{
    printf("%s\n",   ship->name);
    printf("%.1f\n", ship->length);
    printf("%.1f\n", ship->depth);
    printf("%s\n",   ship->crg.title);
    printf("%d\n",   ship->crg.quantity);
    printf("%.1f\n", ship->crg.weight);
}
