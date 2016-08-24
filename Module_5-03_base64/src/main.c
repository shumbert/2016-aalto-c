#include <stdio.h>
#include "base64.h"

int main(int argc, char *argv[])
{
    /* You can modify this file as needed, for example to test different
     * files. If you run on command line, this function optionally reads
     * the filename from command line, if one is given. */
    
    char *filename = "testi.txt";
    if (argc > 1) {
        filename = argv[1];
    }
    
    // Write encoded file to 'testi.enc'
    int n = to_base64("testi.enc", filename);
    printf("to_base64 returned: %d\n", n);
    
    // Follow with reverse operation -- 'testi.ver' should be same as
    // your original source file
    n = from_base64("testi.ver", "testi.enc");
    printf("from_base64 returned: %d\n", n);
}
