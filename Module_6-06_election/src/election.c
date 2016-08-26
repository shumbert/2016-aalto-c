#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "election.h"

struct votes *read_votes(const char *filename)
{
    struct votes *array;
    char current[40];
    int size = 1;
    int found;

    array = malloc(size * sizeof(struct votes));
    if (array == NULL)
        return NULL;
    array->name[0] = '\0';

    FILE *f = fopen(filename, "r");
    if (!f) {
        return NULL;
    }

    while (fgets(current, 40, f)) {
        current[strlen(current) - 1] = '\0';

        struct votes *cur = array;
        found = 0;

        while (strlen(cur->name)) {
            if (strcmp(cur->name, current) == 0) {
                cur->votes++;
                found = 1;
                break;
            }
            cur++;
        }

        //printf("%s %d\n", current, found);
        if (!found) {
            struct votes *tmp = malloc((size + 1) * sizeof(struct votes));
            if (tmp == NULL) {
                free(array);
                return NULL;
            }
            memcpy(tmp, array, (size - 1) * sizeof(struct votes));
            free(array);
            array = tmp;

            strncpy(array[size - 1].name, current, strlen(current) + 1);
            array[size - 1].votes = 1;
            array[size].name[0] = '\0';

            size++;
        }
    }

    fclose(f);
    return array;
}

int compare(const void *a, const void *b)
{
    const struct votes *votes_a = a;
    const struct votes *votes_b = b;

    if (votes_a->votes != votes_b->votes)
        return votes_a->votes < votes_b->votes;
    else
        return strcmp(votes_a->name, votes_b->name);
}

void results(struct votes *vlist)
{
    struct votes *cur = vlist;
    int size = 0;

    while (strlen((cur++)->name))
        size++;

    qsort(vlist, size, sizeof(struct votes), compare);

    cur = vlist;
    while (strlen((cur)->name)) {
        printf("%s: %d\n", cur->name, cur->votes);
        cur++;
    }
}
