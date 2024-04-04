#include <linux/limits.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

void do_find(char *filename, char *startpath);

void add_to_current_path(char *current_path, const char *new_entry) {
    strcat(current_path, "/");
    strcat(current_path, new_entry);
}

void mode_to_string(int mode, char str[]){
    strcpy(str, "----------");
    if (S_ISDIR(mode)) str[0]='d'; // directory?
    if (S_ISCHR(mode)) str[0]='c'; // terminal?
    if (S_ISBLK(mode)) str[0]='b'; // disk?
    if (S_ISLNK(mode)) str[0]='l'; // link?

    if (mode & S_IRUSR) str[1]='r'; // bits for the user
    if (mode & S_IWUSR) str[2]='w';
    if (mode & S_IXUSR) str[3]='x';

    if (mode & S_IRGRP) str[4]='r'; // bits for the group
    if (mode & S_IWGRP) str[5]='w';
    if (mode & S_IXGRP) str[6]='x';
    
    if (mode & S_IROTH) str[7]='r'; // bits for the others
    if (mode & S_IROTH) str[8]='w';
    if (mode & S_IXOTH) str[9]='x';
}
//
// display stat information for a single file
void show_dir_entry(struct stat *info, char *dir_entry_name) {
    char modestring[11];
    mode_to_string(info->st_mode, modestring);
    printf("\t%s ", dir_entry_name);
    printf("(/%s)\n", modestring);
}

void process_entry(char *filename, char *path, char *dir_entry_name) {
    char full_path[PATH_MAX];
    strcpy(full_path, path);
    add_to_current_path(full_path, dir_entry_name);
    struct stat info;
    if(stat(full_path, &info)==-1) {
        perror(full_path);
    } else {
        if(S_ISDIR(info.st_mode)) {
                printf("%s:\n", path);
            do_find(filename, full_path); 
        } else {
            if(strstr(dir_entry_name, filename)) {
                show_dir_entry(&info, dir_entry_name);
            }
        }
    }
}

// explore all entries of the given directory
void do_find(char *filename, char *path) {
    DIR *dir_ptr;                   // pointer to a directory structure
    struct dirent *dirent_ptr;      // pointer to the current directory entry
    dir_ptr = opendir(path);
    if(dir_ptr == 0) {              // opendir could fail, possibly because
        perror(path);           // the directory does not exist
    } else {                        // iterate over all directory entries 
        while ((dirent_ptr=readdir(dir_ptr))!=0) {
            if(strcmp(dirent_ptr->d_name, ".")==0 || strcmp(dirent_ptr->d_name, "..")==0) {
                continue;
            }
            process_entry(filename, path, dirent_ptr->d_name);
        }
    closedir(dir_ptr);
    }
}

int main(int ac, char *av[]) {
    char path[PATH_MAX];
    getcwd(path, sizeof(path));
    if(ac==2) {
        do_find(av[1], path);
    } else if(ac==3) {
        add_to_current_path(path, av[2]);
        do_find(av[1],path);
    } else {
        printf("Usage: myfind [filename] [startpath]\n");
        return 1;
    }
    return 0;
}
