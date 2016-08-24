struct ipHeader {
    int version;
    int ihl;
    int dscp;
    int ecn;
    unsigned short length;
    unsigned short identification;
    int flags;
    int fragment_offset;
    int time_to_live;
    int protocol;
    unsigned short header_checksum;
    unsigned char source_ip[4];
    unsigned char destination_ip[4];
};

void parseIp(struct ipHeader *ip, const void *buffer);
void sendIp(void *buffer, const struct ipHeader *ip);

void printIp(const struct ipHeader *ip);
void hexdump(const void *buffer, unsigned int length);
