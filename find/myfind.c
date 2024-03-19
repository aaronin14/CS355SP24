#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

void process_entry(char *dir_entry_name) {
    struct stat info;
    if (stat(dir_entry_name, &info)==-1)
        perror(dir_entry_name);
    else {
        if(S_ISDIR(info.st_mode)) {
            printf("%s is a directory\n", dir_entry_name);
        }
        if(1)
    }
}

void do_find(char *dir_name){
    DIR *dir_ptr;                   
    struct dirent *dirent_ptr;      
    dir_ptr = opendir(dir_name);
    
    if(dir_ptr == 0) {              
        perror(dir_name);           
    } else {                        
        while ((dirent_ptr=readdir(dir_ptr))!=0) {
            process_entry(dirent_ptr->d_name);
        }
    closedir(dir_ptr);
    }
}

int main() {
    do_find(".");                     
    return 0;
}
