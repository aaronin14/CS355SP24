#include <linux/limits.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int flagA=0, flagR=0, flagS=0;
#define MaxWords 100
#define MaxWordLength 50

int myStringCompare(const void *a, const void *b) {
    return strcmp((const char*)a,(const char*)b);
}

int myStringCompare_reverse(const void *a, const void *b) {
    return strcmp((const char*)b,(const char*)a);
}

// sort and print entries based on flags
void print_ls(char file_names[MaxWords][MaxWordLength], int arr_length) {
    if(flagS==1) {
        qsort(file_names, arr_length, MaxWordLength, myStringCompare);
    }
    if(flagR==1) {
        qsort(file_names, arr_length, MaxWordLength, myStringCompare_reverse);
    }
    for(int i=0; i<arr_length; i++) {
        if(flagA==1) {
            printf("%s\n",file_names[i]);
        } else {
            if(file_names[i][0]!='.')
                printf("%s\n",file_names[i]);
        }
    }
}

// get all entries an store them in file_names array
void do_ls(char *dir_name) {
    char file_names[MaxWords][MaxWordLength];
    DIR *dir_ptr;
    struct dirent *dirent_ptr;
    dir_ptr = opendir(dir_name);

    if (dir_ptr==0) {
        perror(dir_name);
    } else {
        int i=0;
        while ((dirent_ptr=readdir(dir_ptr))!=0 && i<MaxWords) {
            strcpy(file_names[i], dirent_ptr->d_name);
            i++;
        }
    closedir(dir_ptr);

    print_ls(file_names,i);
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
