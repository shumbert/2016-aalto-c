#include <stdio.h>
#include "anydata.h"


/* 01_anydata (a)
 * Return a new AnyData object based on the given input
 */
AnyData setDouble(double value)
{
    AnyData ad;
    ad.type = DOUBLE;
    ad.value.dval = value;
    return ad;
}

AnyData setInt(int value)
{
    AnyData ad;
    ad.type = INT;
    ad.value.ival = value;
    return ad;
}

AnyData setByte(char value)
{
    AnyData ad;
    ad.type = BYTE;
    ad.value.bval = value;
    return ad;
}


void printDouble(double val)
{
    printf("D:%lf", val);
}

void printInt(int val)
{
    printf("I:%d", val);
}

void printByte(char val)
{
    printf("B:%d", val);
}

/* 01_anydata (b)
 * Print the given AnyData value, using one of the above functions
 */
void printValue(AnyData val)
{
    switch(val.type) {
        case BYTE:
            printByte(val.value.bval);
            break;
        case DOUBLE:
            printDouble(val.value.dval);
            break;
        case INT:
            printInt(val.value.ival);
            break;
        case UNDEF:
            break;
    }
}
