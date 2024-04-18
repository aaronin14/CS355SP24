#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>


void quit(int); 

int prime=2;		  

void loop() {
    int count=0, i=2; 
    while (1==1) {
        for(int j=1; j<=i; j++)
            if(i%j==0)
                count++;
        
        if(count==2 && i>prime) {
            prime=i;
        }
        i++;
        count=0;
        usleep(10000);
    }
}

int main() {
    signal(SIGINT, quit); // reprograms the interrupt signal handler
    loop();
    return 0;
}

void quit(int signum) {
    struct termios original_termios, temp_termios;

    // Get current terminal settings
    if (tcgetattr(STDIN_FILENO, &original_termios) < 0) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    // Copy original settings to temporary settings
    temp_termios = original_termios;

    // Disable canonical mode
    temp_termios.c_lflag &= ~(ICANON);

    // Set the new terminal settings
    if (tcsetattr(STDIN_FILENO, TCSANOW, &temp_termios) < 0) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }

    char inputChar;
    printf("\r%-8d Quit [y/n]? ", prime);
    inputChar=getchar();
    if (inputChar=='y') {
        // Restore original terminal settings
        if (tcsetattr(STDIN_FILENO, TCSANOW, &original_termios) < 0) {
            perror("tcsetattr");
            exit(EXIT_FAILURE);
        }
        signal(SIGINT, SIG_DFL); // restore the default interrupt signal handler
        raise(SIGINT); // generate an interrupt signal, which kills the process
    }  else
        printf("\n");
}

