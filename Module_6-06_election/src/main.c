#include <stdio.h>
#include <stdlib.h>
#include "election.h"

int main(int argc, char **argv)
{
    // Read file name from command line, or use a default name
    // if cmd line argument not given
    char *file = "votes.txt";
    if (argc > 1) {
	file = argv[1];
    }
    struct votes *vlist = read_votes(file);
    if (vlist) {
	results(vlist);
	free(vlist);
    }
}
