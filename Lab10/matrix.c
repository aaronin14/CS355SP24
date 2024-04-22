#include <stdlib.h>
#include <signal.h>
#include <curses.h>
#include <unistd.h>


// Reset the terminal settings before ending the program
void quit(int signum) {
    endwin();
    signal(SIGINT, SIG_DFL);
    raise(SIGINT);
}

int main(int ac, char *av[]) {
    int speed=-1000;
    if(ac==2) {
        int n=atoi(av[1]);
        if (n<1 || n>99)
            printf("Speed is range from 1 to 99\n");
        else
            speed*=(atoi(av[1])/2);
    } else {
        printf("Usage: %s [speed = 1-99]\n",av[0]);
        return 0;
    }


    signal(SIGINT, quit);
    initscr();
    curs_set(0);
    noecho();
    clear();

    // Generate the matrix
    int MATRIX_ROWS = LINES+2;
    int MATRIX_COLS = COLS;
    char matrix[MATRIX_ROWS][MATRIX_COLS];
    for(int i=0; i<MATRIX_ROWS; i++)
        for(int j=0; j<MATRIX_COLS; j++)
            matrix[i][j]=(rand()%3==0) ? '0' : (rand()%3==1) ? '1': ' ';

    // Print matrix the first time
    for(int k=0; k<MATRIX_ROWS; k++) {
        for(int i=k; i>0; i--) {
            for(int j=0; j<MATRIX_COLS; j++) {
                mvaddch(i, j, matrix[k-i][j]);
            }
        }
        refresh();
        usleep(100000+speed);
    }

    // Update the matrix with new lines generate at (0,0)
    while (1) {
        // Move each column up by one row
        for (int i=0; i<MATRIX_ROWS; i++) {
            for (int j=0; j<MATRIX_COLS; j++) {
                matrix[i][j]=matrix[i+1][j];
            }
        }

        // Generate new random values for the top row
        for (int j=0; j<MATRIX_COLS; j++) {
            matrix[MATRIX_ROWS-1][j]=(rand()%3==0) ? '0' : ((rand()%3==1) ? '1' : ' ');
        }

        // Printing the whole matrix
        for(int i=MATRIX_ROWS-1; i>0; i--) {
            for(int j=0; j<MATRIX_COLS; j++) {
                mvaddch(i, j, matrix[MATRIX_ROWS-1-i][j]);
            }
        }
        refresh();
        usleep(100000+speed);
    }
}
