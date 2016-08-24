#include <stdio.h>
#include <stdlib.h>
#include "machdr.h"


void print_header(const unsigned char *header)
{
    printf("Frame Control: %02x %02x\n", header[0], header[1]);
}

int main(void)
{
    const unsigned int FrameLen = 36;
    unsigned char *macframe = malloc(FrameLen);  // alloc MAC header until frame body
    
    // fill header with junk, to make this more interesting
    for (unsigned int i = 0; i < FrameLen; i++) {
        macframe[i] = 0xde;
    }
    
    set_proto_version(macframe, 1);
    set_type(macframe, 2);
    set_subtype(macframe, 6);
    set_to_ds(macframe, 0);
    set_from_ds(macframe, 1);
    set_retry(macframe, 0);
    set_more_data(macframe, 1);
    
    print_header(macframe);
    
    printf("Protocol version: %d\n", get_proto_version(macframe));
    printf("Type: %d\n", get_type(macframe));
    printf("Subtype: %d\n", get_subtype(macframe));
    printf("Flags: To DS: %d  From DS: %d  Retry: %d  More Data: %d\n",
            get_to_ds(macframe) != 0, get_from_ds(macframe) != 0,
            get_retry(macframe) != 0, get_more_data(macframe) != 0);
    
    free(macframe);
}
