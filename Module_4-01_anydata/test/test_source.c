#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/anydata.h"

void printType(char *buf, numType type)
{
    if (type == BYTE)
        strcpy(buf, "BYTE");
    else if (type == INT)
        strcpy(buf, "INT");
    else if (type == DOUBLE)
        strcpy(buf, "DOUBLE");
    else
        strcpy(buf, "UNDEF");
}

int checkAD(char *buf, AnyData *stu, AnyData *ref) {
    if (stu->type != ref->type) {
        char bufs[10];
        char bufr[10];
        printType(bufs, stu->type);
        printType(bufr, ref->type);
        sprintf(buf, "type should be %s, you had %s", bufr, bufs);
        return 0;
    }
    if (stu->type == BYTE && stu->value.bval != ref->value.bval) {
        sprintf(buf, "value should be %d, you had %d",
                ref->value.bval, stu->value.bval);
        return 0;
    }
    if (stu->type == INT && stu->value.ival != ref->value.ival) {
        sprintf(buf, "value should be %d, you had %d",
                ref->value.ival, stu->value.ival);
        return 0;
    }    
    if (stu->type == DOUBLE && stu->value.dval != ref->value.dval) {
        sprintf(buf, "value should be %lf, you had %lf",
                ref->value.dval, stu->value.dval);
        return 0;
    }
    return 1;
}

START_TEST(test_set)
{
    char v1 = rand() % 0xff;
    AnyData ad, ref;
    char buffer[200];
    memset(&ad, 0xde, sizeof(ad));
    ad = setByte(v1);
    ref.type = BYTE; ref.value.bval = v1;
    if (!checkAD(buffer, &ad, &ref)) {
        fail("[M4.01.a] After setByte(%d), %s", v1, buffer);
    }
    
    int v2 = rand() % 0xffff;
    ad = setInt(v2);
    ref.type = INT; ref.value.ival = v2;
    if (!checkAD(buffer, &ad, &ref)) {
        fail("[M4.01.a] After setInt(%d), %s", v2, buffer);
    }
        
    ad = setDouble(5.555);
    ref.type = DOUBLE; ref.value.dval = 5.555;
    if (!checkAD(buffer, &ad, &ref)) {
        fail("[M4.01.a] After setDouble(%lf), %s", 5.555, buffer);
    }
}
END_TEST


void helper(AnyData *ad, char *buffer, unsigned int n)
{
        freopen("mockoutput", "w", stdout);
        printValue(*ad);
        fflush(stdout);
        FILE *fp = fopen("mockoutput", "r");
        fgets(buffer, n, fp);
        fclose(fp);
}

START_TEST(test_print)
{
    AnyData ad;
    ad = setByte(4);
    char buffer[80] = { 0 };
    helper(&ad, buffer, 79);
    if (strcmp(buffer, "B:4")) {
        remove_nonascii(buffer);
        fail("[M4.01.b] After setByte(4) should output '%s', you printed: '%s'",
                "B:4", buffer);
    }
    
    ad = setInt(20000);
    helper(&ad, buffer, 79);   
    if (strcmp(buffer, "I:20000")) {
        remove_nonascii(buffer);
        fail("[M4.01.b] After setInteger(20000) should output '%s', you printed: '%s'",
                "I:20000", buffer);
    }
    
    ad = setDouble(6.6666);
    helper(&ad, buffer, 79);   
    if (strcmp(buffer, "D:6.666600")) {
        remove_nonascii(buffer);
        fail("[M4.01.b] After setDouble(6.6666) should output '%s', you printed: '%s'",
                "D:6.666600", buffer);
    }    
}
END_TEST


#if 0
START_TEST(test_sum)
{
    AnyData array[5];
    array[0] = setDouble(3.14159);
    array[1] = setByte(2);
    array[2] = setByte(3);
    array[3] = setInt(10000);
    array[4] = setDouble(5.555);
    
    AnyData ad = calcSum(&array[1], &array[2]);
    if (ad.type == UNDEF) {
	    fail("[Task 4.1.c] calcSum returned unspecified type");
    }
    AnyData ref;
    char buffer[200];
    ref.type = BYTE; ref.value.bval = 5;
    if (!checkAD(buffer, &ad, &ref)) {
        fail("[Task 4.1.c] After countSum{B:2, B:3}, %s", buffer);
    }   

    ad = calcSum(&array[1], &array[3]);
    ref.type = INT; ref.value.ival = 10005;
    if (!checkAD(buffer, &ad, &ref)) {
        fail("[Task 4.1.c] After countSum{B:2, B:3, I: 10000}, %s", buffer);
    }   

    ad = calcSum(&array[1], &array[4]);
    ref.type = DOUBLE; ref.value.dval = 10010.555000;
    if (!checkAD(buffer, &ad, &ref)) {
        fail("[Task 4.1.c] After countSum{B:2, B:3, I: 10000, D: 10010.555000}, %s", buffer);
    }   
}
END_TEST
#endif


int main(int argc, const char *argv[])
{
        srand((unsigned) time(NULL));
    	Suite *s = suite_create("Test-01_anydata");

	tmc_register_test(s, test_set, "M4.01.a");
	tmc_register_test(s, test_print, "M4.01.b");
	//tmc_register_test(s, test_sum, "4.1.c");
        
	return tmc_run_tests(argc, argv, s);
}
