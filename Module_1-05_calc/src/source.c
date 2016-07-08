#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "source.h"



void simple_sum(void)
{
    int a, b;
    if (scanf("%d %d", &a, &b) != 2)
        exit(1);
    printf("%d + %d = %d\n", a, b, a + b);
}


void simple_math(void)
{
    double a, b;
    char operator;

    if (scanf("%lf %c %lf", &a, &operator, &b) != 3)
        printf("ERR\n");
    else {
        switch(operator) {
            case '+':
                printf("%.1f\n", a + b);
                break;
            case '-':
                printf("%.1f\n", a - b);
                break;
            case '*':
                printf("%.1f\n", a * b);
                break;
            case '/':
                printf("%.1f\n", a / b);
                break;
            default:
                printf("ERR\n");
                
        }
    }
}
