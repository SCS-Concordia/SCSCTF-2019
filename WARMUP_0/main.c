#include <stdio.h>
#include <string.h>

const char* ok_message = "Flag OK!";
const char* invalid_message = "Flag INVALID!";

const char* txt = "FLAG-{A8842DB3711B8088477A85ED2421131BAC6B3DDD}";

int main(int argc, char** argv)
{
    char buf[50];
    printf("Flag: ");
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;

    printf("%s\n", strcmp(txt, buf) == 0 ? ok_message : invalid_message);
}

