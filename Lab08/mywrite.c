#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <utmp.h>
#include <time.h>

#define BUFSIZE 256

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

        // get my current info
        char *my_tty = ttyname(STDIN_FILENO);
        char *my_username = getlogin();
        char my_hostname[100];
        if (gethostname(my_hostname, sizeof(my_hostname)) == -1) {
            perror("gethostname");
            return 1;
        }

        // Get current time
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        char current_time[50];
        strftime(current_time, 50, "%H:%M", timeinfo);

        // Iterating through each utmp record
        while(read(utmp_fd, &utmp_entry, intUTMPlength)==intUTMPlength) {
            // Get the tty path
            char tty_path[20];
            snprintf(tty_path, sizeof(tty_path), "/dev/%s", utmp_entry.ut_line);
            //printf("%s vs %s\n",tty_path, my_tty);

            // Skip if the tty is the same as current user, or the one that I couldn't access
            if((strcmp(my_tty, tty_path)==0) || strcmp(tty_path, "/dev/pts/0")==0 || strcmp(tty_path, "/dev/pts/1")==0)
                continue;
            // Check if the user exists and the record is a user process
            if(utmp_entry.ut_type == USER_PROCESS && my_strcmp(utmp_entry.ut_user, username)==0) {

                //  Open the tty                
                int tty_fd=open(tty_path, O_WRONLY);   
                if(tty_fd<0) {
                     continue;
                } 
                char buf[BUFSIZE];
                char hiMessage[100] = "";
                sprintf(hiMessage, "Message from %s@%s on %s at %s...\n", my_username, my_hostname, tty_path, current_time);
                char byeMessage[]="EOF\n";
                write(tty_fd, hiMessage, strlen(hiMessage));
                while(fgets(buf, BUFSIZE, stdin)!=0)    // read a string from the current terminal 
                	if(write(tty_fd, buf, strlen(buf))==-1) // and write it to the target terminal
                            break;
                write(tty_fd, byeMessage, strlen(byeMessage));
                close(tty_fd); 
            } else {
                continue;
            }
        }
        close(utmp_fd);
    }
    return 0;
}
