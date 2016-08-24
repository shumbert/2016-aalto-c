#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "oodi.h"


int main()
{
    /* Feel free to modify
     * for example function for printing the current array content is useful */

    struct oodi antti;
    struct date anttidate = {24, 1, 2015};
    if (init_record(&antti, "123456", "ELEC-A7100", 4, anttidate )) {
        printf("Initialization succeeded\n");
    } else {
        printf("Initialization failed\n");
    }
    
    struct oodi students[] = {
        { "123456", "ELEC-A7110", 0, {1,1,2015} },
        { "555666", "ELEC-A7110", 2, {3,4,2015} },
        { "773466", "A little bit longer course name", 3, {31, 12, 2014} },
        { "234567", "Short", 5, {31, 12, 2014} }
    };
    
    struct oodi *array = NULL;
    unsigned int len = 0;
    for (unsigned int i = 0; i < sizeof(students) / sizeof(struct oodi); i++) {
        struct oodi *newarray = add_record(array, len, students[i]);
        if (!newarray) {
            delete_array(array, len);
            exit(EXIT_FAILURE);
        }
        len++;
        array = newarray;
    }

    struct date day1 = {20, 1, 2015};
    struct date day2 = {23, 2, 2016};
    if (!change_grade(array, len, "555666", "ELEC-A7110", 4, day1))
        printf("failed '555666'\n");
    if (!change_grade(array, len, "234567", "Short", 3, day2))
        printf("failed '234567'\n");
    if (!change_grade(array, len, "111111", "ELEC-A7110", 3, day2))
        printf("failed '111111'\n");
    if (!change_grade(array, len, "234567", "no course", 3, day2))
        printf("failed '234567', no course\n");   
    
    delete_array(array, len);
}
