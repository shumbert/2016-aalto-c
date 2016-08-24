#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "arraytool.h"

int main(void)
{
#ifdef MAKE_ARRAY
    void *ptr = MAKE_ARRAY(int, 10);
#else
    printf("Implement MAKE_ARRAY first");
#endif
    
#ifdef CHECK    
    CHECK(5 > 10, "5 > 10 failed\n");
#endif    
    
#ifdef ARRAY_IDX
    for (int i = 0; i < 10; i++) {
        ARRAY_IDX(int, ptr, i) = i * 2;
    }
    
    for (int i = 0; i < 10; i++) {
        printf("%d ", ARRAY_IDX(int, ptr, i));
    }
    free(ptr);
#else
    printf("Implement ARRAY_IDX first");
#endif
}
