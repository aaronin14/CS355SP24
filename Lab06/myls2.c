#include <asm-generic/ioctls.h>
#include <linux/limits.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/ioctl.h>

int flagA=0, flagR=0, flagS=0;
#define MaxWords 100
#define MaxWordLength 50

int get_screen_col() {
    struct winsize wbuf;

    if (ioctl(0, TIOCGWINSZ, &wbuf) != -1) 
       return wbuf.ws_col;
    return 0;
}

int myStringCompare(const void *a, const void *b) {
    return strcmp((const char*)a,(const char*)b);
}

int myStringCompare_reverse(const void *a, const void *b) {
    return strcmp((const char*)b,(const char*)a);
}

int remove_hidden_files(char fileNames[MaxWords][MaxWordLength], int numberOfFile) {
    for(int i=0; i<numberOfFile; i++) {
        if(fileNames[i][0]=='.') {
            strcpy(fileNames[i],fileNames[--numberOfFile]);
            strcpy(fileNames[numberOfFile],"");
        }
    }
    return numberOfFile;
}

void print_ls(char fileNames[MaxWords][MaxWordLength], int numberOfFile, int maxNameLength) {
    if(flagA==0)
        numberOfFile=remove_hidden_files(fileNames, numberOfFile);
    // Sorting the fileNames
    if(flagS==1) {
        qsort(fileNames, numberOfFile, MaxWordLength, myStringCompare);
    }
    if(flagR==1) {
        qsort(fileNames, numberOfFile, MaxWordLength, myStringCompare_reverse);
    }

    // Calculating number of Column and Row needed to print fileNames
    int termColumns=get_screen_col();
    int col=termColumns/(maxNameLength+2);
    int row=1;
    int remainder=0;

    if(numberOfFile>col) {
        row=numberOfFile/col;
        remainder=numberOfFile%col;
    } else
        col=numberOfFile;

    if(remainder>0) {
        row++;
        col=(numberOfFile/row)+1;
    }

    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            int index=i+(j*row);
            printf("%-*s  ", maxNameLength, fileNames[index]);
        }
        printf("\n"); 
    }
}

// get all entries an store them in fileNames array
void do_ls(char *dir_name) {
    char fileNames[MaxWords][MaxWordLength];
    DIR *dir_ptr;
    struct dirent *dirent_ptr;
    dir_ptr = opendir(dir_name);
   
    int maxNameLength=0;

    if (dir_ptr==0) {
        perror(dir_name);
    } else {
        int i=0;
        // Get the max length of a file name
        while ((dirent_ptr=readdir(dir_ptr))!=0 && i<MaxWords) {
            strcpy(fileNames[i], dirent_ptr->d_name);
            if (maxNameLength<strlen(fileNames[i]))
                maxNameLength=strlen(fileNames[i]);
            i++;
        }
    closedir(dir_ptr);

    print_ls(fileNames,i,maxNameLength);
    }
}

int main(int ac, char *av[]) {
    char option;
    while ((option = getopt(ac, av, "ars")) != -1) {
        switch(option) {
            case 'a':
                flagA=1;
                break;
            case 'r':
                flagR=1;
                break;
            case 's':
                flagS=1;
                break;
        }
    }
    int count=0;
    for (int i=1; i<ac; i++) {
        if (av[i][0] != '-') {
            count++;
            do_ls(av[i]);
        }
    }
    if(count==0)
        do_ls(".");
    
    return 0;
}
