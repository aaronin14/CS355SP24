#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFERSIZE 1024
int flagB=0, flagE=0, flagN=0, flagS=0;

char * my_strcat(char *dest, const char *src) { // String concatenation 
    char *return_dest = dest; // Save the starting address of dest
    while (*dest)   // Go to the end of the dest string
        dest++;
    while (*src)    // Adding characters to the dest string
        *dest++ = *src++;
    return return_dest; // Return to the starting address of the string
}

int is_empty_line(char *str, int *position) {  // Check if empty line
    int i = *position+1;
    while ((str[i]!='\n') && (str[i]!='\0'))  { // Loop until new line or end of string
        if ((str[i]!=' ') && str[i]!='\t' && str[i]!='\n' && str[i]!='\r') {
            return 0; // return false if there is a characters
        }
        i++; 
    }
    return i; // return the new position if it is empty
}

// Handling flags
void flag_handling(char *str) { 
    int i=0, bCount=1, nCount=1;

    if (flagN==1) {
        printf("%2d ", nCount);
        nCount++;
    }

    if (flagB==1) {
        printf("%2d ", bCount);
        bCount++;
    }

    while (str[i]!=0) {
        if ((flagE==1) && (str[i+1]=='\n')) 
            printf("$");

        printf("%c",str[i]);

        if ((flagS==1) && (str[i]=='\n')) {
            int skip;
            while ((skip = is_empty_line(str, &i)) != 0) {
                i=skip;
            }
        }

        if ((flagN==1) && (str[i]=='\n')) {
            printf("%2d ", nCount);
            nCount++;
        }

        if ((flagB==1) && (str[i]=='\n') && (!is_empty_line(str, &i))) {
            printf("%2d ", bCount);
            bCount++;
        }
        i++;
    }
}

int do_cat(char *file_name, char *the_string) {
    int file_ptr;
    char buffer[BUFFERSIZE];
    int numbytes;

    file_ptr = open(file_name, O_RDONLY);
    if (file_ptr < 0) {
        perror(file_name);
        return 1;
    }

    while ((numbytes = read(file_ptr, buffer, BUFFERSIZE)) > 0) {
        my_strcat(the_string, buffer);
    }            
   
    if (numbytes<0) {
        perror("Read error");
        return 1;
    }

    if (close(file_ptr)<0) {
        perror("Error closing files\n");
        return 1;
    }
    return 0;
}

int main(int ac, char *av[]) {
    char option;
    char the_string[10000];
    while((option = getopt(ac, av, "bens")) != -1) {
        switch(option) {
            case 'b':
                flagB=1;
                break;
            case 'e':
                flagE=1;
                break;
            case 'n':
                flagN=1;
                break;
            case 's':
                flagS=1;
                break;
        }
    }
    for (int i=1; i<ac; i++) {
        if (av[i][0] != '-') {
            do_cat(av[i],the_string);
        }
    }
            flag_handling(the_string);
    return 0;
}
