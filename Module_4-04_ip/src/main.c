#include <arpa/inet.h>
#include "ipheader.h"

int main()
{
    /* Feel free to modify this function to test different things */
    
    unsigned char bytes[] = {
        0x45, 0x00, 0x01, 0xd3, 0xda, 0x8d, 0x40, 0x00,
        0x40, 0x06, 0x8c, 0xd5, 0xc0, 0xa8, 0x01, 0x46,
        0x6c, 0xa0, 0xa3, 0x33 };
    
    struct ipHeader ip;
    
    parseIp(&ip, bytes);
    printIp(&ip);
    
    struct ipHeader ipfields = {
        4, // version
        28, // ihl
        4, // dscp
        0, // ecn
        htons(1500), // length
        htons(1234), // id
        1, // flags
        1024, // offset
        15, // time_to_live
        33, // protocol
        htons(0x1234), // checksum (invalid)
        {1, 2, 3, 4}, // source IP
        {5, 6, 7, 8} // destination IP
    };
    unsigned char sendbuf[20];
    
    sendIp(sendbuf, &ipfields);
    hexdump(sendbuf, sizeof(sendbuf));
}
