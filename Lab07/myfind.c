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
    strcpy(str, "0000/----------");

    if(mode & S_ISUID) str[0]+=4;
    if(mode & S_ISGID) str[0]+=2;
    if(mode & S_ISVTX) str[0]+=1;

    if (S_ISDIR(mode)) str[5]='d'; // directory?
    if (S_ISCHR(mode)) str[5]='c'; // terminal?
    if (S_ISBLK(mode)) str[5]='b'; // disk?
    if (S_ISLNK(mode)) str[5]='l'; // link?

    if (mode & S_IRUSR) {
        str[6]='r';
        str[1]+=4;
    }
    if (mode & S_IWUSR) {
        str[7]='w';
        str[1]+=2;
    }
    if (mode & S_IXUSR) {
        str[8]='x';
        str[1]+=1;
    }

    if (mode & S_IRGRP) {
        str[9]='r'; 
        str[2]+=4;
    }
    if (mode & S_IWGRP) {
        str[10]='w';
        str[2]+=2;
    }
    if (mode & S_IXGRP) {
        str[11]='x';
        str[2]+=1;
    }
    
    if (mode & S_IROTH) {
        str[12]='r'; // bits for the others
        str[3]+=4;
    }
    if (mode & S_IROTH) {
        str[13]='w';
        str[3]+=2;
    }
    if (mode & S_IXOTH) {
        str[14]='x';
        str[3]+=1;
    }
}

// display stat information for a single file
void show_dir_entry(struct stat *info, char *dir_entry_name) {
    char modestring[15];
    mode_to_string(info->st_mode, modestring);
    printf("\t%s ", dir_entry_name);
    printf("(%s)\n", modestring);
}

void process_entry(char *filename, char *path, char *dir_entry_name, int *found_match) {
    char full_path[PATH_MAX];
    strcpy(full_path, path);
    add_to_current_path(full_path, dir_entry_name);
    struct stat info;
    if(stat(full_path, &info)==-1) {
        perror(full_path);
    } else {
        if(S_ISDIR(info.st_mode)) {
            do_find(filename, full_path); 
        } else {
            if(strstr(dir_entry_name, filename)) {
                if(!*found_match) {
                    printf("%s\n", path);
                    *found_match=1;
                }
                show_dir_entry(&info, dir_entry_name);
            }
        }
    }
}

// explore all entries of the given directory
void do_find(char *filename, char *path) {
    int found_match=0;
    DIR *dir_ptr;                   // pointer to a directory structure
    struct dirent *dirent_ptr;      // pointer to the current directory entry
    dir_ptr = opendir(path);
    if(dir_ptr == 0) {              // opendir could fail, possibly because
        perror(path);           // the directory does not exist
    } else {                        // iterate over all directory entries 
        while ((dirent_ptr=readdir(dir_ptr))!=0) {
            if(strcmp(dirent_ptr->d_name, ".")==0 || strcmp(dirent_ptr->d_name, "..")==0) { // ignore "." and ".." entries
                continue;
            }
            process_entry(filename, path, dirent_ptr->d_name, &found_match);
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
        printf("Usage: %s [filename] [startpath]\n", av[0]);
        return 1;
    }
    return 0;
}
