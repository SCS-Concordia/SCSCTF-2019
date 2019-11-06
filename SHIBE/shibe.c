#include <bsd/md5.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define MAX_LENGTH 128

char data[MAX_LENGTH];

char *get_md5(const char *input)
{
    MD5_CTX md5;
    MD5Init(&md5);
    MD5Update(&md5, input, strlen(input));
    char *res = MD5End(&md5, NULL);
    return res;
}

void init_data(void)
{
    memset(data, 0, MAX_LENGTH);

    FILE *fd = fopen("/tmp/data.txt", "r");
    if (!fd) {
        printf("The shibe is unimpressed\n");
        exit(1);
    }

    char line[256];
    int ln = 0;
    while (fgets(line, sizeof(line), fd) && ln < (MAX_LENGTH - 1)) {
        data[ln] = (char)atoi(line);
        ++ln;
    }

    fclose(fd);
}

void give_flag(void)
{
    char *hash = get_md5(data);

    int values[] = { 100, 98, 53, 98, 53, 102, 54, 55, 97, 51, 102, 102, 102, 55, 99, 56, 98, 57, 48, 99, 50, 101, 55, 56, 98, 51, 56, 48, 54, 52, 48, 100 };
    int len = strlen(hash);

    if (len != sizeof(values) / sizeof(values[0])) {
        printf("The shibe is unimpressed\n");
        free(hash);
        exit(1);
    }

    int show_flag = 1;
    for (int i = 0; i < len; ++i) {
        if (values[i] != hash[i]) {
            show_flag = 0;
            break;
        }
    }

    if (show_flag) {
        printf("FLAG-{%s}\n", data);
    } else {
        printf("The shibe does not see fit to bestow you with its secret\n");
    }
    free(hash);
}

int main(int argc, char **argv)
{
    printf("         ▄              ▄    \n");
    printf("        ▌▒█           ▄▀▒▌   \n");
    printf("        ▌▒▒█        ▄▀▒▒▒▐   \n");
    printf("       ▐▄▀▒▒▀▀▀▀▄▄▄▀▒▒▒▒▒▐   \n");
    printf("     ▄▄▀▒░▒▒▒▒▒▒▒▒▒█▒▒▄█▒▐   \n");
    printf("   ▄▀▒▒▒░░░▒▒▒░░░▒▒▒▀██▀▒▌   \n");
    printf("  ▐▒▒▒▄▄▒▒▒▒░░░▒▒▒▒▒▒▒▀▄▒▒▌  \n");
    printf("  ▌░░▌█▀▒▒▒▒▒▄▀█▄▒▒▒▒▒▒▒█▒▐  \n");
    printf(" ▐░░░▒▒▒▒▒▒▒▒▌██▀▒▒░░░▒▒▒▀▄▌ \n");
    printf(" ▌░▒▄██▄▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒▌ \n");
    printf("▀▒▀▐▄█▄█▌▄░▀▒▒░░░░░░░░░░▒▒▒▐ \n");
    printf("▐▒▒▐▀▐▀▒░▄▄▒▄▒▒▒▒▒▒░▒░▒░▒▒▒▒▌\n");
    printf("▐▒▒▒▀▀▄▄▒▒▒▄▒▒▒▒▒▒▒▒░▒░▒░▒▒▐ \n");
    printf(" ▌▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒░▒░▒░▒░▒▒▒▌ \n");
    printf(" ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▒▄▒▒▐  \n");
    printf("  ▀▄▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▄▒▒▒▒▌  \n");
    printf("    ▀▄▒▒▒▒▒▒▒▒▒▒▄▄▄▀▒▒▒▒▄▀   \n");
    printf("      ▀▄▄▄▄▄▄▀▀▀▒▒▒▒▒▄▄▀     \n");
    printf("         ▒▒▒▒▒▒▒▒▒▒▀▀        \n");

    init_data();
    give_flag();

    return 0;
}
