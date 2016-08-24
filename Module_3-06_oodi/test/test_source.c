#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "../src/oodi.h"

static const unsigned int num_entries = 4;
static char *students[] = {"123456", "555666", "773466", "234567"};
static char *names[] = {"ELEC-A7110", "ELEC-A7110", "A little bit longer course name", "Short"};
static unsigned char grades[] = {0, 2, 3, 5};
static struct date dates[] = { {1,1,2015}, {3, 4, 2013}, {31, 12, 2014}, {31, 12, 2014}};
    

int test_oodi(char *buf, struct oodi *pr, const char *student, const char *course,
        unsigned char grade, struct date cdate) {
    if (pr->course == course || pr->course == NULL) {
        sprintf(buf, "Memory for the course string not dynamically allocated");
        return 0;
    }
    if (strcmp(pr->course, course)) {
        remove_nonascii(pr->course);
        sprintf(buf, "Incorrect title. You: \"%s\", expected: \"%s\"",
                pr->course, course);
        return 0;
    }

    if (strlen(pr->student) > 6) {
        sprintf(buf, "Student ID is too long. Max. length is 6 characters");
        return 0;
    }

    if (strcmp(pr->student, student)) {
        remove_nonascii(pr->student);
        sprintf(buf, "Incorrect student ID. You: \"%s\", expected: \"%s\"",
                pr->student, student);
        return 0;
    }
    if (pr->grade != grade) {
        sprintf(buf, "Incorrect grade. You: %d, expected: %d",
                pr->grade, grade);
        return 0;
    }
    if (pr->compdate.day != cdate.day) {
        sprintf(buf, "Incorrect day in date. You: %d, expected %d",
                pr->compdate.day, cdate.day);
        return 0;
    }
    if (pr->compdate.month != cdate.month) {
        sprintf(buf, "Incorrect day in date. You: %d, expected %d",
                pr->compdate.month, cdate.month);
        return 0;
    }
    if (pr->compdate.year != cdate.year) {
        sprintf(buf, "Incorrect day in date. You: %d, expected %d",
                pr->compdate.year, cdate.year);
        return 0;
    }
        
    return 1;
}


START_TEST(test_init_record)
{
    struct oodi *p = malloc(sizeof(struct oodi));
    
    for (unsigned int i = 0; i < num_entries; i++) {
        memset(p, '#', sizeof(struct oodi));
        p->course = NULL;
        int ret = init_record(p, students[i], names[i], grades[i], dates[i]);
        if (strlen(students[i]) > 6) {
            if (ret != 0) {
                if (p->course && p->course != names[i])
                    free(p->course);
		free(p);
                fail("[M3.06.a] With invalid student ID should return 0. You returned: %d",
                        ret);
            }
        } else {
            if (ret != 1) {
                if (p->course && p->course != names[i])
		  free(p->course);
		free(p);
                fail("[M3.06.a] With valid student ID should return 1. You returned: %d",
                        ret);
            }
            char buf[200];
            buf[0] = 0;
            ret = test_oodi(buf, p, students[i], names[i], grades[i], dates[i]);
            if (!ret) {
                if (p->course && p->course != names[i])
                    free(p->course);
		free(p);
                fail("[M3.06.a] Struct not initialized properly: %s", buf);
            }
        }
        if (p->course && p->course != names[i])
            free(p->course);
    }
    free(p);
}
END_TEST


void freeall(struct oodi *arr, unsigned int num)
{
    for (unsigned int i = 0; i < num; i++) {
        free(arr[i].course);
    }
    free(arr);
}

START_TEST(test_add_record)
{
    struct oodi *array = NULL;
    
    unsigned int i;
    for (i = 0; i < num_entries; i++) {
        struct oodi nr;
        strcpy(nr.student, students[i]);
        nr.course = names[i];
        nr.grade = grades[i];
        nr.compdate = dates[i];
        struct oodi *newarray = add_record(array, i, nr);

	if (!newarray) {
	  if (array)
	    freeall(array, i);
	  fail("[M3.06.b] add_record returned NULL");
	}
	array = newarray;
        
        if (nr.course == array[i].course) {
            freeall(array, i);
            fail("[M3.06.b] Memory for course is not dynamically allocated.");
        }
        
        if (!array) {
            fail("[M3.06.b] add_record returned NULL");
        }
        char buf[200];
        buf[0] = 0;
        int ret = test_oodi(buf, &array[i], nr.student, nr.course, nr.grade, nr.compdate);
        if (!ret) {
            freeall(array, i + 1);
            fail("[M3.06.b] Array member %d not initialized properly: %s", i, buf);
        }
    }
    freeall(array, i);
}
END_TEST


char *printday(char *buf, const struct date *d)
{
    sprintf(buf, "%d.%d.%d", d->day, d->month, d->year);
    return buf;
}


int same_date(const struct date *d1, const struct date *d2)
{
  if (d1->day != d2->day)
    return 0;
  if (d1->month != d2->month)
    return 0;
  if (d1->year != d2->year)
    return 0;
  return 1;
}

int test_change(char *buf, struct oodi *array, const char *student, const char *course,
        unsigned char newg, const struct date *newd, unsigned int aidx, int retref)
{
    int ret = change_grade(array, num_entries, student, course, newg, *newd);
    if (retref == 1 && ret != 1) {
        freeall(array, num_entries);
        sprintf(buf, "[M3.06.c] After change_grade for existing student '%s', course '%s', you returned %d, should have returned %d",
                student, course, ret, retref);
        return 0;
    } else if (retref == 0 && ret != 0) {
        freeall(array, num_entries);
        sprintf(buf, "[M3.06.c] After change_grade for nonexisting student '%s', course '%s', you returned %d, should have returned %d",
                student, course, ret, retref);
        return 0;
    }
    
    char strbuf[40];
    if (array[aidx].grade != newg || !same_date(&array[aidx].compdate, newd)) {
        sprintf(buf, "[M3.06.c] After change_grade for student '%s', course '%s', new grade should be %d, new date should be %s. Your grade: %d, date: %s",
                student, course, newg, printday(strbuf, newd), array[aidx].grade, printday(strbuf, &array[aidx].compdate));
	freeall(array, num_entries);
        return 0;
    }
    return 1;
}

struct oodi *add_all(struct oodi *array)
{
    for (unsigned int i = 0; i < num_entries; i++) {
        struct oodi nr;
        strcpy(nr.student, students[i]);
        nr.course = names[i];
        nr.grade = grades[i];
        nr.compdate = dates[i];
        array = add_record(array, i, nr);
	if (!array)
	  return NULL;
    }
    return array;
}

START_TEST(test_change_grade)
{
    struct oodi *array = NULL;    
    array = add_all(array);
    if (!array) {
      fail("[M3.06.c] Implement add_record first");
    }
    
    struct date day1 = {20, 1, 2015};
    struct date day2 = {23, 2, 2016};
    char buf[160];

    if (!test_change(buf, array, "555666", "ELEC-A7110", 4, &day1, 1, 1)) {
        fail("%s", buf);
    }
    if (!test_change(buf, array, "234567", "Short", 1, &day2, 3, 1)) {
        fail("%s", buf);
    }
    if (!test_change(buf, array, "111111", "ELEC-A7110", 1, &day2, 3, 0)) {
        fail("%s", buf);
    }
    if (!test_change(buf, array, "234567", "nocourse", 1, &day2, 3, 0)) {
        fail("%s", buf);
    }
    freeall(array, num_entries);
}
END_TEST


#if 0
START_TEST(test_delete_array)
{
    struct oodi *array = NULL;    
    array = add_all(array);
    if (!array) {
      fail("[M3.06.d] Implement add_record first");
    }
    if (!delete_array(array, num_entries)) {
        freeall(array, num_entries);
        fail("[M3.06.d] delete_array should return 1");
    }
    array = NULL;
}
END_TEST
#endif


int main(int argc, const char *argv[]) {
    srand((unsigned) time(NULL));
    Suite *s = suite_create("Test-06_oodi");

    tmc_register_test(s, test_init_record, "M3.06.a");
    tmc_register_test(s, test_add_record, "M3.06.b");
    tmc_register_test(s, test_change_grade, "M3.06.c");
    //tmc_register_test(s, test_delete_array, "M3.06.d");
    
    return tmc_run_tests(argc, argv, s);
}
