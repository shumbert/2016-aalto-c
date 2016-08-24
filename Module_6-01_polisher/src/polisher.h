#ifndef AALTO_POLISHER_H
#define AALTO_POLISHER_H

char *read_file(const char *filename);
char *remove_comments(char *input);
char *indent(char *input, const char *pad);

#endif
