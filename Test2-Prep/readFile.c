#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFERSIZE 1024

int main() {
    int fd;                         // File Descriptor
    char buffer[BUFFERSIZE];
    char filename[] = "text.txt";
    int numbytes;

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    while((numbytes = read(fd, buffer, BUFFERSIZE)) >0) {
        write(STDOUT_FILENO, buffer, numbytes);
    }

    if (numbytes<0) {
        perror("Read error");
        return 1;
    }

    if(close(fd)<0) {
        perror("Error clossing files\n");
        return 1;
    }
    return 0;
}
