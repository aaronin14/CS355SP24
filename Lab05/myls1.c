#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

int flagA=0, flagR=0, flagS=0;
#define MaxWords 10
#define MaxWordLength 50

void mode_to_string(int mode, char str[]){
    strcpy(str, "----------");
    if (S_ISDIR(mode)) str[0]='d';
    if (S_ISCHR(mode)) str[0]='c';
    if (S_ISBLK(mode)) str[0]='b';
    if (S_ISLNK(mode)) str[0]='l';

    if (mode & S_IRUSR) str[1]='r';
    if (mode & S_IWUSR) str[2]='w';
    if (mode & S_IXUSR) str[3]='x';

    if (mode & S_IRGRP) str[4]='r';
    if (mode & S_IWGRP) str[5]='w';
    if (mode & S_IXGRP) str[6]='x';
    
    if (mode & S_IROTH) str[7]='r';
    if (mode & S_IROTH) str[8]='w';
    if (mode & S_IXOTH) str[9]='x';
}

void show_dir_entry(struct stat *info, char *dir_entry_name) {
    char modestring[11];
    mode_to_string(info->st_mode, modestring);
    printf("%s ", modestring);
    printf("%4lu ", info->st_nlink);
    printf("%8ld ", info->st_size);
    printf("%.20s ", ctime(&info->st_ctim.tv_sec));
    printf("%s\n", dir_entry_name);
}
void do_stats(char *dir_entry_name) {
    struct stat info;
    if (stat(dir_entry_name, &info)==-1)
        perror(dir_entry_name);
    else
        show_dir_entry(&info, dir_entry_name);
}

void do_ls(char *dir_name) {
    DIR *dir_ptr;
    struct dirent *dirent_ptr;
    dir_ptr = opendir(dir_name);

    if (dir_ptr==0) {
        perror(dir_name);
    } else {
        while ((dirent_ptr=readdir(dir_ptr))!=0) {
            if (flagA==1)
                do_stats(dirent_ptr->d_name);
            else {
                printf("%s ",dirent_ptr->d_name);
            }
        }
        printf("\n");
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
    do_ls(".");
    
 // char words[MaxWords][MaxWordLength];
 //    for (int i=1; i<ac; i++) {
 //        int j=0;
 //        if (av[i][0] != '-') {
 //            words[j]=av[i];
 //            j++;
 //        }
 //    }
    return 0;
}
