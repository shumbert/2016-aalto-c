#ifndef AALTO_MACHDR_H
#define AALTO_MACHDR_H

int get_proto_version(const unsigned char *header);
int get_type(const unsigned char *header);
int get_subtype(const unsigned char *header);
int get_to_ds(const unsigned char *header);
int get_from_ds(const unsigned char *header);
int get_retry(const unsigned char *header);
int get_more_data(const unsigned char *header);

void set_proto_version(unsigned char *header, int version);
void set_type(unsigned char *header, int type);
void set_subtype(unsigned char *header, int subtype);
void set_to_ds(unsigned char *header, int flag);
void set_from_ds(unsigned char *header, int flag);
void set_retry(unsigned char *header, int flag);
void set_more_data(unsigned char *header, int flag);

#endif
