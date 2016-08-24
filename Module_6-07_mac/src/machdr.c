#include "machdr.h"

/* a) Implement all get_* functions. <header> points to the start of the
 * MAC header. The functions return the value of the respective field.
 * For flags, any non-zero return value indicates that flag is set, and zero
 * means it is not set.
 */

int get_proto_version(const unsigned char *header)
{
    (void) header;
    return 0;
}

int get_type(const unsigned char *header)
{
    (void) header;
    return 0;
}

int get_subtype(const unsigned char *header)
{
    (void) header;
    return 0;
}

int get_to_ds(const unsigned char *header)
{
    (void) header;
    return 0;
}

int get_from_ds(const unsigned char *header)
{
    (void) header;
    return 0;
}

int get_retry(const unsigned char *header)
{
    (void) header;
    return 0;
}

int get_more_data(const unsigned char *header)
{
    (void) header;
    return 0;
}

/* b) Implement all set_* functions that set the values of respective
 * fields in the MAC header. <header> points to the start of the header,
 * and the second parameter indicates the value to be set.
 */

void set_proto_version(unsigned char *header, int version)
{
    (void) header;
    (void) version;
}

void set_type(unsigned char *header, int type)
{
    (void) header;
    (void) type;
}

void set_subtype(unsigned char *header, int subtype)
{
    (void) header;
    (void) subtype;
}

void set_to_ds(unsigned char *header, int flag)
{
    (void) header;
    (void) flag;
}

void set_from_ds(unsigned char *header, int flag)
{
    (void) header;
    (void) flag;
}

void set_retry(unsigned char *header, int flag)
{
    (void) header;
    (void) flag;
}

void set_more_data(unsigned char *header, int flag)
{
    (void) header;
    (void) flag;
}
