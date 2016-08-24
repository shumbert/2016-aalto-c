/* Prevent student from calling these functions, otherwise check
 * framework shows them as "Passed" */
#include <stdio.h>
#include <stdlib.h>

// exit
void __wrap_exit(int status){
    (void)status;
    fprintf(stderr, ">>> Captured call to exit(), shame on you!\n");
    abort();
}

// _exit
void __wrap__exit(int status){
    (void)status;
    fprintf(stderr, ">>> Captured call to _exit(), shame on you!\n");
    abort();
}

// _Exit
void __wrap__Exit(int status){
    (void)status;
    fprintf(stderr, ">>> Captured call to _Exit(), shame on you!\n");
    abort();
}
