/*
A very basic implementation of ls:
list the names of all directory entries

Pseudocode:
    open directory
    while not end of directory
        read directory entry
        display entry info
    close directory    
*/

#include <stdio.h>
#include <dirent.h>

// list all entries of the given directory
void do_ls(char *dir_name){
    DIR *dir_ptr;                   // pointer to a directory structure
    struct dirent *dirent_ptr;      // pointer to the current directory entry
    dir_ptr = opendir(dir_name);
    // The line below is equivalent to this
    // if (!dir_ptr==0) {
    if(dir_ptr == 0) {              // opendir could fail, possibly because
        perror(dir_name);           // the directory does not exist
    } else {                        // iterate over all directory entries
        while ((dirent_ptr=readdir(dir_ptr))!=0) {
            printf("Directory entry: %s\n",dirent_ptr->d_name); 
        }
    closedir(dir_ptr);
    }
}

int main() {
    do_ls(".");                     // list the contents of the current directory
    return 0;
}
