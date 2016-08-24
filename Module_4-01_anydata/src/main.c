#include <stdio.h>
#include "anydata.h"

int main(void)
{
    /* Feel free to modify this function to test different things */
    /* For example, you can temporarily hide unimplemented functions
     * inside comments */

    AnyData array[5];
    
    array[0] = setDouble(3.14159);
    array[1] = setByte(2);
    array[2] = setByte(3);
    array[3] = setInt(10000);
    array[4] = setDouble(5.555);
    
    for (int i = 0; i < 5; i++) {
        printValue(array[i]);
        printf("\n");
    }
}
