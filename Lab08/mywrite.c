/*
 * Working scaffolding for the write system command
 *
 * Ctrl-D sends EOF character
 * Ctrl-Z suspends the process
 *      use ps to see the lis of all processes and get pid of a suspended processes
 *      use kill (or kill -KILL) to terminate the suspended process, if needed
 *      you may also try using top or htop commands to see the list of running processes
 */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <utmp.h>

#define BUFSIZE 1024

int main(int ac, char* av[]) {
    if(ac!=2) 
        fprintf(stderr, "Usage: %s username\n", av[0]);
    else {

        // Open UTMP file to check if username is valid and find the user's tty path
        struct utmp currentRecord;
        int intUTMPlength = sizeof(currentRecord);
        int utmp_fd;
        if((utmp_fd = open(UTMP_FILE, O_RDONLY))==-1) {
            printf("Error: Unable to use the UTMP file");
            return 1;
        }

        // Iterating through each utmp record
        while(read(utmp_fd, &currentRecord, intUTMPlength)==intUTMPlength) {

            // Check if the user exists and the record is a user process
            //if((currentRecord.ut_type == USER_PROCESS) && (strcmp(currentRecord.ut_user,av[1])==0)) {
            if(currentRecord.ut_type == USER_PROCESS) {

                // Get the tty path and open it
                char ttyPath[50];
                sprintf(ttyPath, "/dev/%s", currentRecord.ut_line);
                int tty_fd=open(ttyPath, O_WRONLY);   

                if(tty_fd==-1) {
                    perror(ttyPath);
                    close(utmp_fd);
                    return 1;
                } else {
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
        }
        close(utmp_fd);
    }
    return 0;
}