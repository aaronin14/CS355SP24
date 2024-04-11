#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <utmp.h>

#define BUFSIZE 1024

int my_strcmp(char *str1, char *str2) {
    return strcmp(str1, str2);
}

int main(int ac, char* av[]) {
    if(ac!=2) 
        fprintf(stderr, "Usage: %s username\n", av[0]);
    else {
	char *username = av[1];

        // Open UTMP file to check if username is valid and find the user's tty path
        struct utmp utmp_entry;
        int intUTMPlength = sizeof(utmp_entry);
        int utmp_fd;
        if((utmp_fd = open(UTMP_FILE, O_RDONLY))==-1) {
            printf("Error: Unable to use the UTMP file");
            return 1;
        }

        // Iterating through each utmp record
        while(read(utmp_fd, &utmp_entry, intUTMPlength)==intUTMPlength) {

            // Check if the user exists and the record is a user process
            if(utmp_entry.ut_type == USER_PROCESS && my_strcmp(utmp_entry.ut_user, username)==0) {
                printf("%s %d", utmp_entry.ut_user, utmp_entry.ut_type);

                // Get the tty path and open it
                char tty_path[50];
                snprintf(tty_path, 50, "/dev/%s", utmp_entry.ut_line);
                int tty_fd=open(tty_path, O_WRONLY);   

                if(tty_fd==-1) {
                    perror(tty_path);
                    close(utmp_fd);
                    return 1;

                } 
                char buf[BUFSIZE];
                char hiMessage[]="Message another termimal...\n";
                char byeMessage[]="EOF";
                while(fgets(buf, BUFSIZE, stdin)!=0)    // read a string from the current terminal 
                	if(write(tty_fd, buf, strlen(buf))==-1) // and write it to the target terminal
                            break;
                write(tty_fd, byeMessage, strlen(byeMessage));
                close(tty_fd); 
            }
        }
        close(utmp_fd);
    }
    return 0;
}
