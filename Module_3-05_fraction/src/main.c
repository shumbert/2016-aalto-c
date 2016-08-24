#include <stdio.h>
#include "fraction.h"

int main()
{
    /* Hint: if you have implemented only part of the functions,
       add comments around those that you didn't yet implement.
       Feel free to modify this function as you wish. It is not checked
       by the tester.*/
    
    /* The below code uses function printFraction. Implementing it will not
     * gain you points, but will be useful for testing */
    
    Fraction *a = setFraction(2,3);
    Fraction *b = setFraction(3,4);
    
    Fraction *sum = addFraction(a, b);
    printFraction(sum);
    printf("\n");
    
    printf("Result of comparison: %d\n", compFraction(a,b));
    
    Fraction *mul = setFraction(6,12);    
    reduceFraction(mul);
    printFraction(mul);
    
    freeFraction(a);
    freeFraction(b);
    freeFraction(sum);
    freeFraction(mul);
}
