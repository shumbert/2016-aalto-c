#include <ctype.h>
#include <stdio.h>
#include "base64.h"

/* The set of base64-encoded characters. You may use this table if you want.
 * (The last character is not part of the actual base64 set, but used for
 * padding). 
 */
const char *encoding = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

int decode(int byte)
{
    int res = 0;

    char *cur = (char *) encoding;
    while (*cur) {
        if (*cur == byte)
            break;
        cur++;
        res++;
    }

    return res;
}

void writeDec(FILE *out, int *bytes)
{
    int padding = 0;
    int decrypted[3];

    for (int i = 0; i < 4; i++)
        bytes[i] = decode(bytes[i]);

    if (bytes[2] == 0x40)
        padding = 2;
    else if (bytes[3] == 0x40)
        padding = 1;

    decrypted[0] = (bytes[0] << 2) | (bytes[1] >> 4);
    if (padding < 2)
        decrypted[1] = ((bytes[1] & 0xf) << 4) | (bytes[2] >> 2);
    if (padding < 1)
        decrypted[2] = ((bytes[2] & 0x3) << 6) | bytes[3];

    for (int i = 0; i < 3 - padding; i++)
        fprintf(out, "%c", decrypted[i]);
}

void writeEnc(FILE *out, int written, int *bytes, int padding)
{
    int encrypted[4];

    encrypted[0] = bytes[0] >> 2;
    encrypted[1] = ((bytes[0] & 0x3) << 4) | (bytes[1] >> 4);
    encrypted[2] = ((bytes[1] & 0xf) << 2) | (bytes[2] >> 6);
    encrypted[3] = bytes[2] & 0x3f;

    for (int i = 0; i < 4; i++) {
        if (((4 - i) <= padding) && (encrypted[i] == 0))
            fprintf(out, "=");
        else
            fprintf(out, "%c", encoding[encrypted[i]]);
        if (((written + i + 1) % 64) == 0)
            fprintf(out, "\n");
    }
}

/* Open file named <src_file> for reading, and convert it to Base64 format,
 * which is written to file named <dst_file>.
 * 
 * Returns: number of bytes in <src_file>, or -1 if there was an error,
 * for example if opening of <src_file> did not succeed.
 */
int to_base64(const char *dst_file, const char *src_file)
{
    FILE *in = fopen(src_file, "r");
    FILE *out = fopen(dst_file, "w");
    if (!(in && out)) {
        return -1;
    }

    int c, bytes[3];
    int read = 0;
    int written = 0;
    while ((c = fgetc(in)) != EOF) {
        bytes[read++ % 3] = c;
        if (read % 3 == 0) {
            writeEnc(out, written, bytes, 0);
            written += 4;
        }
    }

    if ((read % 3) > 0) {
        if ((read % 3) == 1) {
            bytes[1] = 0;
            bytes[2] = 0;
            writeEnc(out, written, bytes, 2);
        } else {
            bytes[2] = 0;
            writeEnc(out, written, bytes, 1);
        }
    }

    fclose(in);
    fclose(out);
    return read;
}

/* Open Base64-encoded file named <src_file> for reading, and convert it
 * to regular binary format, which is written to file named <dst_file>.
 * 
 * Returns: number of bytes in <src_file>, or -1 if there was an error,
 * for example if opening of <src_file> did not succeed.
 */
int from_base64(const char *dst_file, const char *src_file)
{
    FILE *in = fopen(src_file, "r");
    FILE *out = fopen(dst_file, "w");
    if (!(in && out)) {
        return -1;
    }

    int c, bytes[4];
    int index = 0;
    int read = 0;
    while ((c = fgetc(in)) != EOF) {
        read++;
        if (c == '\n')
            continue;
        bytes[index++ % 4] = c;
        if (index % 4 == 0)
            writeDec(out, bytes);
    }

    fclose(in);
    fclose(out);
    return read;
}
