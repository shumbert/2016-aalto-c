#ifndef AALTO_ELECTION_H
#define AALTO_ELECTION_H

struct votes {
    char name[40];
    unsigned int votes;
};

struct votes *read_votes(const char *filename);
void results(struct votes *vlist);

#endif
