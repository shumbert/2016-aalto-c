#ifndef AALTO_CSUM14_43
#define AALTO_CSUM14_43

char **init_array(void);
void free_strings(char **array);
char **add_string(char **array, const char *string);
void make_lower(char **array);
void sort_strings(char **array);
void print_strings(char **array);

#endif
