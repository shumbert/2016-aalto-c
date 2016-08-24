#include "myprint.h"

int main(void)
{
    myprint("Hello!\n");
    myprint("Number: &\n", 5);
    myprint("Number one: &, number two: &\n", 120, 1345);
    int ret = myprint("Three numbers: & & &\n", 12, 444, 5555);
    myprint("I just printed & integers\n", ret);
}
