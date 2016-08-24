#include <stdio.h>
#include <stdlib.h>
#include "fraction.h"

/* Algorithm for determining greatest common divisor, needed in (d) */
/* The function returns gcd between the two parameters, u and v */
/* Taken from http://en.wikipedia.org/wiki/Binary_GCD_algorithm */
unsigned int gcd(unsigned int u, unsigned int v)
{
    // simple cases (termination)
    if (u == v)
        return u;
 
    if (u == 0)
        return v;
 
    if (v == 0)
        return u;
 
    // look for factors of 2
    if (~u & 1) // u is even
    {
        if (v & 1) // v is odd
            return gcd(u >> 1, v);
        else // both u and v are even
            return gcd(u >> 1, v >> 1) << 1;
    }
 
    if (~v & 1) // u is odd, v is even
        return gcd(u, v >> 1);
 
    // reduce larger argument
    if (u > v)
        return gcd((u - v) >> 1, v);
 
    return gcd((v - u) >> 1, u);
}

struct fraction_st {
    unsigned int numerator;
    unsigned int denominator;
};

/* Exercise a: Set fraction
 * Parameters: numerator and denominator
 * Returns: pointer to allocated fraction
 */
Fraction* setFraction(unsigned int numerator, unsigned int denominator)
{
    Fraction *fraction = malloc(sizeof(struct fraction_st));
    fraction->numerator = numerator;
    fraction->denominator = denominator;
    return fraction;
}

unsigned int getNum(const Fraction *f)
{
    return f->numerator;
}

unsigned int getDenom(const Fraction *f)
{
    return f->denominator;
}

void freeFraction(Fraction *f)
{
    free(f);
}


/* Exercise b: Compare values
 * Parameters: two fractions to be compared
 * Returns:
 * -1 if a is smaller than b
 * 0 if the fractions are equal
 * 1 if a is larger than b
 */
int compFraction(const Fraction *a, const Fraction *b)
{
    unsigned int value_a = getNum(a) * getDenom(b);
    unsigned int value_b = getNum(b) * getDenom(a);
    if (value_a == value_b)
        return 0;
    else if (value_a > value_b)
        return 1;
    else
        return -1;
}

/* Exercise c: Add values
 * Parameters: two fractions to be added
 * Returns: sum of the fractions
 */
Fraction* addFraction(const Fraction *a, const Fraction *b)
{
    unsigned int numerator = getNum(a) * getDenom(b) + getNum(b) * getDenom(a);
    unsigned int denominator = getDenom(a) * getDenom(b);
    return setFraction(numerator, denominator);
}


/* Reduce fraction
 * Parameters: Fraction to be reduced. Reduction happens on the object itself */
void reduceFraction(Fraction* val)
{
    unsigned int divisor = gcd(getNum(val), getDenom(val));
    val->numerator = getNum(val) / divisor;
    val->denominator = getDenom(val) / divisor;
}

/* Not needed, but it will be useful to implement this */
void printFraction(const Fraction *val)
{
    printf("%u/%u", getNum(val), getDenom(val));
}
