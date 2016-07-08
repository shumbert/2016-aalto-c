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
    float a1 = 2.1;
    float a2 = 3.2;
    float result_a = a1 + a2;
    
    int b1 = 100;
    int b2 = 80000;
    int result_b = b1 * b2;
    
    int c1 = 100000;
    float c2 = 1.5;
    int result_c = c1 / c2;

    
    // Do not change the following line
    printf("%.1f  %d  %d\n", result_a, result_b, result_c);
}
