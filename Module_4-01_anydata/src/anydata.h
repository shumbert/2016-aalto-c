#ifndef AALTO_ANYDATA_H
#define	AALTO_ANYDATA_H

typedef enum {
    UNDEF,
    BYTE,            
    INT,
    DOUBLE
} numType;

typedef struct {
    numType type;
    union {
        int ival;  // if INT
        double dval;  // if DOUBLE
        char bval;  // if BYTE
    } value;
} AnyData;

AnyData setDouble(double value);
AnyData setInt(int value);
AnyData setByte(char value);

void printValue(AnyData val);

AnyData calcSum(AnyData *first, AnyData *last);

#endif	/* AALTO_ANYDATA_H */
