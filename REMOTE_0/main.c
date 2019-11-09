#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{

    char buf[32];

    if(argc < 2)
    {
        printf("https://www.youtube.com/watch?v=gvdf5n-zI14\n");
        return 0;
    }

    setuid(0);

    read(atoi( argv[1] ) - 0x1337, buf, 32);
    if(!strcmp("SCSCTF-2019\n", buf)){
        system("/bin/cat flag.txt");
        exit(0);
    }

    printf("Oopsies!\n");

    return 0;
}

