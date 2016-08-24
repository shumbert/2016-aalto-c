#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/machdr.h"

struct testfields {
    int proto_version;
    int type;
    int subtype;
    int to_ds;
    int from_ds;
    int retry;
    int more_data;
};

#define NUMTESTS 5


START_TEST(test_parse_header)
{
    struct testfields tf[NUMTESTS] = {
        { 1, 2, 6, 0, 1, 0, 1 },
        { 2, 3, 5, 1, 1, 0, 0 }
    };
    unsigned char dump[NUMTESTS][2] = {
        { 0x66, 0x4e },
        { 0xb5, 0xca }
    };
    
    int num = 2;
    
    for (int i = 0; i < num; i++) {
        
        int ret = get_proto_version(dump[i]);
        if (ret != tf[i].proto_version) {
            fail("[M6.07.a] With header bytes { 0x%02x, 0x%02x } expected protocol version: %d, you got: %d",
                    dump[i][0], dump[i][1], tf[i].proto_version, ret);
        }
        ret = get_type(dump[i]);
        if (ret != tf[i].type) {
            fail("[M6.07.a] With header bytes { 0x%02x, 0x%02x } expected type: %d, you got: %d",
                    dump[i][0], dump[i][1], tf[i].type, ret);
        }
        ret = get_subtype(dump[i]);
        if (ret != tf[i].subtype) {
            fail("[M6.07.a] With header bytes { 0x%02x, 0x%02x } expected subtype: %d, you got: %d",
                    dump[i][0], dump[i][1], tf[i].subtype, ret);
        }
        ret = get_to_ds(dump[i]);
        if ((ret != 0) != (tf[i].to_ds != 0)) {
            fail("[M6.07.a] With header bytes { 0x%02x, 0x%02x } expected to_ds flag: %d, you got: %d",
                    dump[i][0], dump[i][1], tf[i].to_ds, ret);
        }
        ret = get_from_ds(dump[i]);
        if ((ret != 0) != (tf[i].from_ds != 0)) {
            fail("[M6.07.a] With header bytes { 0x%02x, 0x%02x } expected from_ds flag: %d, you got: %d",
                    dump[i][0], dump[i][1], tf[i].from_ds, ret);
        }
        ret = get_retry(dump[i]);
        if ((ret != 0) != (tf[i].retry != 0)) {
            fail("[M6.07.a] With header bytes { 0x%02x, 0x%02x } expected retry flag: %d, you got: %d",
                    dump[i][0], dump[i][1], tf[i].retry, ret);
        }
        ret = get_more_data(dump[i]);
        if ((ret != 0) != (tf[i].more_data != 0)) {
            fail("[M6.07.a] With header bytes { 0x%02x, 0x%02x } expected more_data flag: %d, you got: %d",
                    dump[i][0], dump[i][1], tf[i].more_data, ret);
        }
    }
    test_complete();
}
END_TEST

START_TEST(test_set_header)
{    
    unsigned char buf[36] = { 0 };
    
    set_proto_version(buf, 1);
    if (buf[0] != 0x40) {
        fail("[M6.07.b] After setting proto_version to 1, the first byte should be 0x%02x, you have: 0x%02x",
                0x40, buf[0]);
    }
    buf[0] = 0;
    set_type(buf, 2);
    if (buf[0] != 0x20) {
        fail("[M6.07.b] After setting type to 2, the first byte should be 0x%02x, you have: 0x%02x",
                0x20, buf[0]);
    }
    buf[0] = 0;
    set_subtype(buf, 6);
    if (buf[0] != 0x6) {
        fail("[M6.07.b] After setting subtype to 6, the first byte should be 0x%02x, you have: 0x%02x",
                0x6, buf[0]);
    }
    buf[1] = 0;
    set_to_ds(buf, 1);
    if (buf[1] != 0x80) {
        fail("[M6.07.b] After setting to_ds to 1, the second byte should be 0x%02x, you have: 0x%02x",
                0x80, buf[1]);
    }
    
    test_complete();
}
END_TEST

int main(int argc, const char *argv[]) {
    srand((unsigned)time(NULL));
    Suite *s = suite_create("Test-07_mac");

    tmc_init_tests();
    
    tmc_register_test(s, test_parse_header, "M6.07.a");
    tmc_register_test(s, test_set_header, "M6.07.b");

    return tmc_run_tests(argc, argv, s);
}
