#ifndef AALTO_FRACTION_H
#define	AALTO_FRACTION_H

typedef struct fraction_st Fraction;

/* Allocates a new Fraction from heap */
Fraction* setFraction(unsigned int numerator, unsigned int denominator);

/* Returns the numerator of the given fraction */
unsigned int getNum(const Fraction *f);

/* Returns the denominator of the given fraction */
unsigned int getDenom(const Fraction *f);

/* Releases the Fraction from heap */
void freeFraction(Fraction *f);

/* Compares two fractions */
int compFraction(const Fraction *a, const Fraction *b);

/* Adds the given fractions and creates new object for the result */
Fraction* addFraction(const Fraction *a, const Fraction *b);

/* Reduce fraction */
void reduceFraction(Fraction *val);

/* Print fraction (optional, does not give points) */
void printFraction(const Fraction *val);

#endif	/* AALTO_FRACTION_H */
