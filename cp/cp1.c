#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFERSIZE 1024

int main(int ac, char *av[]) {
    int src, dst;
    int buffer[BUFFERSIZE];
    int numbytes;

    if (ac!=3) {
        printf("Usage: %s <source> <destination>\n", av[0]);
        return 1;
    }

    src = open(av[1], O_RDONLY);
    if (src < 0) {
        perror(av[1]);
        return 1;
    }

    dst = creat(av[2], 0644);
    if (dst < 0) {
        perror(av[2]);
        return 1;
    }

    while ((numbytes = read(src, buffer, BUFFERSIZE))>0) {
        if (write(dst, buffer, numbytes)!=numbytes) {
            perror("Write error");
            return 1;
        }
    }

    if (numbytes<0) {
        perror("Read error");
        return 1;
    }

    close(src);
    close(dst);
    return 0;
}
