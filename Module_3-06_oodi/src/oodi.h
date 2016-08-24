#ifndef AALTO_C2015_33
#define AALTO_C2015_33

// Date in numeric format
struct date {
    unsigned char day;
    unsigned char month;
    int year;
};

// Single course entry
struct oodi {
    char student[7]; // student ID (6 characters) + terminating '\0'
    char *course; // course code or name (string)
    unsigned char grade; // grade 0 -- 5
    struct date compdate;  // date of completion
};


int init_record(struct oodi *or, const char *p_student, const char *p_course,
        unsigned char p_grade, struct date p_compdate);

struct oodi *add_record(struct oodi *array, unsigned int size, struct oodi newrec);

int change_grade(struct oodi *array, unsigned int size, const char *p_student,
        const char *p_course, unsigned char newgrade, struct date newdate);

int delete_array(struct oodi *array, unsigned int size);

#endif
