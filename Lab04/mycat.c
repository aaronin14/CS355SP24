#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFERSIZE 1024

int do_cat(char *file_name) {
    int file_ptr;
    int buffer[BUFFERSIZE];
    int numbytes;

    file_ptr = open(file_name, O_RDONLY);
    if (file_ptr < 0) {
        perror(file_name);
        return 1;
    }
    while ((numbytes = read(file_ptr, buffer, BUFFERSIZE)) > 0) {
    }            
    return 1;
}

int flagB=0, flagE=0, flagN=0, flagS=0;

int main(int ac, char *av[]) {
    char option;
    while((option = getopt(ac, av, "bens")) != -1) {
        switch(option) {
            case 'b':
                printf("b");
                break;
            case 'e':
                printf("e");
                break;
            case 'n':
                printf("n");
                break;
            case 's':
                printf("s");
                break;
            default:
                break;
        }
    }
    return 0;
}
