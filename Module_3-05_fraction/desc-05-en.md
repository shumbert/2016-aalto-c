title: Fraction
task_id: 05_fraction
points: 4

We practice abstract data types by implementing a new number type,
[fraction], that consists of numerator and denominator. For example
2/3 and 4/6 are equivalent values, where 2 and 4 are numerators, and 3
and 6 are denominators. A new data type, `Fraction` is used to
represent fractions.

[fraction]: http://en.wikipedia.org/wiki/Fraction_(mathematics)

Implement the following functions. In this exercise, you are only
given header **fraction.h** that specifies the public
interface. **fraction.c** is nearly empty, and you will need to
implement everything, starting from the definition of **struct
fraction_st**.

(a) Set value
---------------

Implement function `Fraction* setFraction(unsigned int numerator,
unsigned int denominator)` that allocates a new Fraction from heap,
sets its value as given in parameters, and returns the created object.

In addition, implement also the following simple functions

  * `void freeFraction(Fraction* f)` that releases the memory used by
  the Fraction.

  * `unsigned int getNum(const Fraction *f)` that returns the
  numerator part of the fraction.

  * `unsigned int getDenom(const Fraction *f)` that returns the
  denominator part of the fraction. 

(b) Compare values
--------------------

Implement function `int compFraction(const Fraction *a, const
Fraction *b)` that returns -1 if a < b, 0 if a == b, or 1 if a > b.
The function should work correctly also when denominators are
different.

**Note:** The local tests for the following parts of this exercise use
this function to test the outcome. Therefore it is recommended that
you implement this part before (c) and (d). If you get silly error
message incorrectly complaining about wrong result in them, the reason
might be incorrect compare implementation. The tests on (c) and (d) on
TMC server do not depend on your comparison code.

(c) Add values
----------------

Implement function `Fraction *add(const Fraction *a, Fraction *b)`
that adds values '**a**' and '**b**', and returns the result in a new
object allocated from heap. Again, the denominators may be different
in the two numbers. The resulting value does **not** need to be
reduced to smallest possible denominator.

**Hint:** start by modifying the two numbers such that they have the
same denominator.

(d) Reduce value
------------------

Implement function `void reduce(Fraction *val)`, that reduces the
value to the smallest possible denumerator. For example, using this
function 3/6 should reduce to 1/2. For doing this, you'll need to find
the greatest common divisor for the numerator and denominator. The
exercise template contains function `unsigned int gcd(unsigned int u,
unsigned int v)` (source:
[wikipedia](http://en.wikipedia.org/wiki/Binary_GCD_algorithm)), that
you can use from your function.
