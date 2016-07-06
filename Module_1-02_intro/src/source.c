#include <stdio.h>
#include <math.h>
#include "source.h"


void three_lines(void)
{
    printf("January\n");
    printf("February\n");
    printf("March\n");
}


void fix_types(void)
{
    char a1 = 2.1;
    char a2 = 3.2;
    char result_a = a1 + a2;
    
    char b1 = 100;
    char b2 = 80000;
    char result_b = b1 * b2;
    
    char c1 = 100000;
    char c2 = 1.5;
    char result_c = c1 / c2;

    
    // Do not change the following line
    printf("%.1f  %d  %d\n", result_a, result_b, result_c);
}
