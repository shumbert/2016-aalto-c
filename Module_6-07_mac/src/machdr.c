#include <stdio.h>
#include "machdr.h"

/* a) Implement all get_* functions. <header> points to the start of the
 * MAC header. The functions return the value of the respective field.
 * For flags, any non-zero return value indicates that flag is set, and zero
 * means it is not set.
 */

int get_proto_version(const unsigned char *header)
{
    return header[0] >> 6;
}

int get_type(const unsigned char *header)
{
    return (header[0] >> 4) & 0x3;
}

int get_subtype(const unsigned char *header)
{
    return header[0] & 0xf;
}

int get_to_ds(const unsigned char *header)
{
    return header[1] >> 7;
}

int get_from_ds(const unsigned char *header)
{
    return (header[1] >> 6) & 0x1;
}

int get_retry(const unsigned char *header)
{
    return (header[1] >> 4) & 0x1;
}

int get_more_data(const unsigned char *header)
{
    return (header[1] >> 2) & 0x1;
}

/* b) Implement all set_* functions that set the values of respective
 * fields in the MAC header. <header> points to the start of the header,
 * and the second parameter indicates the value to be set.
 */

void set_proto_version(unsigned char *header, int version)
{
    char tmp = header[0] & 0x3f;
    header[0] = (version << 6) + tmp;
}

void set_type(unsigned char *header, int type)
{
    char tmp = header[0] & 0xcf;
    header[0] = (type << 4) | tmp;
}

void set_subtype(unsigned char *header, int subtype)
{
    char tmp = header[0] & 0xf0;
    header[0] = tmp + subtype;
}

void set_to_ds(unsigned char *header, int flag)
{
    char tmp = header[1] & 0x7f;
    header[1] = (flag << 7) | tmp;
}

void set_from_ds(unsigned char *header, int flag)
{
    char tmp = header[1] & 0xbf;
    header[1] = (flag << 6) | tmp;
}

void set_retry(unsigned char *header, int flag)
{
    char tmp = header[1] & 0xef;
    header[1] = (flag << 4) | tmp;
}

void set_more_data(unsigned char *header, int flag)
{
    char tmp = header[1] & 0xfb;
    header[1] = (flag << 2) | tmp;
}
