#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// FLAG-{385BE16C8A682C843C986DCA59E8C46B7E99DCF6}

const char* ok_message = "Flag OK!";
const char* invalid_message = "Flag INVALID!";

const char* txt = "RkxBRy17Mzg1QkUxNkM4QTY4MkM4NDNDOTg2RENBNTlFOEM0NkI3RTk5RENGNn0=";

const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
size_t enc_size(size_t inlen)
{
    size_t ret;

    ret = inlen;
    if (inlen % 3 != 0)
        ret += 3 - (inlen % 3);
    ret /= 3;
    ret *= 4;

    return ret;
}

char* enc(const unsigned char *in, size_t len)
{
    char   *out;
    size_t  elen;
    size_t  i;
    size_t  j;
    size_t  v;

    if (in == NULL || len == 0)
        return NULL;

    elen = enc_size(len);
    out  = malloc(elen+1);
    out[elen] = '\0';

    for (i=0, j=0; i<len; i+=3, j+=4) {
        v = in[i];
        v = i+1 < len ? v << 8 | in[i+1] : v << 8;
        v = i+2 < len ? v << 8 | in[i+2] : v << 8;

        out[j]   = chars[(v >> 18) & 0x3F];
        out[j+1] = chars[(v >> 12) & 0x3F];
        if (i+1 < len) {
            out[j+2] = chars[(v >> 6) & 0x3F];
        } else {
            out[j+2] = '=';
        }
        if (i+2 < len) {
            out[j+3] = chars[v & 0x3F];
        } else {
            out[j+3] = '=';
        }
    }

    return out;
}

int main(int argc, char** argv)
{
    char buf[50];

    printf("Flag: ");
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;

    unsigned long input_length = strlen(buf);
    char* out = enc(buf, input_length);

    printf("%s\n", strcmp(txt, out) == 0 ? ok_message : invalid_message);
}
