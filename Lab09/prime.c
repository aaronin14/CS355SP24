#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void quit(int); 

int prime=2;		  

void loop() {
    int count=0, i=2; 
    while (1==1) {
        for(int j=1; j<=i; j++)
            if(i%j==0)
                count++;
        
        if(count==2) {
            printf("%d\n", prime);
            prime=i;
        }
        i++;
        count=0;
        sleep(1);
    }
}

int main() {
    //signal(SIGINT, SIG_IGN); //ignors the interrupt signal
    signal(SIGINT, quit); // reprograms the interrupt signal handler
    loop();
    return 0;
}

void quit(int signum) {
    char inputChar;
    printf("%-8d Quit [y/n]? ", prime);
    inputChar=getchar();
    if (inputChar=='y') {
        signal(SIGINT, SIG_DFL); // restore the default interrupt signal handler
        raise(SIGINT); // generate an interrupt signal, which kills the process
    }  else
        printf("\n");
}
