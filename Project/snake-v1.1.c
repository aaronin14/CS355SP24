#include <curses.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


#define INITIAL_LENGTH 5
#define SNAKE_MAX_LENGTH 25
//Richard
int trophy_x = -1;
int trophy_y = -1;
// Snake is drawn by character '0'
char snake_ch = '0';
// Snake's initial length
int snake_len = INITIAL_LENGTH;
// Snake's starting head position
int start_x = 2+INITIAL_LENGTH;
int start_y = 2;
// Snake starting direction
int direction_x = 1;
int direction_y = 0;
int old_direction_x = 1;
int old_direction_y = 0;
int trophy_flag;
// Aaron
// Snake's position is stored in an array of Postition struct
struct Position {
    int y,x;
};
struct Position snake[SNAKE_MAX_LENGTH];


// Initialize the snake pit, and the snake
void init_game(int (*holder)[COLS]) {
    clear(); // Clear the screen
    // Snake pit
    for(int y=0; y<LINES-1; y++){   // Empty space's value is 0
        for(int x=0; x<COLS-1; x++)
            holder[y][x]=0;
    }
    for(int y=0; y<LINES-1; y++){   // Borders's value is -2
        holder[y][0]=-2;                 // Left Border
        holder[y][COLS-1]=-2;            // Right Border
    }
    for(int x=0; x<COLS-1; x++){
        holder[0][x]=-2;                 // Top Border
        holder[LINES-1][x]=-2;           // Bottom Border
    }
    // Snake init
    snake[0].x = start_x;
    snake[0].y = start_y;
    for(int i=0; i<snake_len; i++) {
        snake[i].x=start_x-i;
        snake[i].y=start_y;
        holder[snake[0].y][snake[0].x-i]=-1;    // Snake's value is -1
    }
}

// Richard
// Trophy
void trophy_creation(int (*holder)[COLS]){
    if(trophy_flag == 1){
        if(trophy_x != -1){
            holder[trophy_y][trophy_x] = 0;
        }
        trophy_x = rand() % 100 + 1;
        trophy_y = rand() % 10 + 1;
        holder[trophy_y][trophy_x] = -10;

    }
}


//Richard
// Printing the whole game
void print_game(int (*holder)[COLS]) {
    trophy_creation(holder);
    box(stdscr, 0, 0);
    for(int y=0; y<LINES-1; y++){
        for(int x=0; x<COLS-1; x++){
            if(holder[y][x]==-1)
                mvaddch(y,x,'0');
            if(holder[y][x]==0)
                mvaddch(y,x,' ');
            if(holder[y][x] == -10){
                mvaddch(y,x,'t');
            }
        }
    }
    refresh();
}

void snake_movement(int (*holder)[COLS]) {
    int tail_x = snake[snake_len-1].x;
    int tail_y = snake[snake_len-1].y;
    holder[tail_y][tail_x]=0;           // Assign 0 to the last tail position
    for(int i=snake_len-1; i>0; i--) {  // Move forward
        snake[i].x=snake[i-1].x;
        snake[i].y=snake[i-1].y;
    }
    snake[0].x += direction_x;
    snake[0].y += direction_y;
    int head_x = snake[0].x;
    int head_y = snake[0].y;
    holder[head_y][head_x]=-1;          // Assing -1 to the new head position
}


void game(int (*holder)[COLS]) {
    int ch;
    snake_movement(holder);
    while(1) {
        timeout(200);
        direction_x = old_direction_x;
        direction_y = old_direction_y;
        print_game(holder);
        //Richard
        ch=getch();
        switch(ch) {
            case 'W':
            case 'w':
                if(direction_y!=1) {
                    direction_x=0;
                    direction_y=-1;
                    old_direction_x = direction_x;
                    old_direction_y = direction_y;

                }
                break;
            case 'A':
            case 'a':
                if(direction_x!=1) {
                    direction_x=-1;
                    direction_y=0;
                    old_direction_x = direction_x;
                    old_direction_y = direction_y;
                }
                break;
            case 'S':
            case 's':
                if(direction_y!=-1) {
                    direction_x=0;
                    direction_y=1;
                    old_direction_x = direction_x;
                    old_direction_y = direction_y;
                }
                break;
            case 'D':
            case 'd':
                if(direction_x!=-1) {
                    direction_x=1;
                    direction_y=0;
                    old_direction_x = direction_x;
                    old_direction_y = direction_y;
                }
                break;
            case 'X':
            case 'x':
                endwin();
                raise(SIGINT);
            default:
                break;
        }
        snake_movement(holder);
    }
}


int main(){
    initscr();
    clear();
    noecho();
    curs_set(0);
    int holder[LINES][COLS]; // Snake pit
    int trophy_flag = 0;
    // Game Menu and Control
    box(stdscr, 0, 0);
    mvprintw( 1,1,"SNAKE GAME");
    mvprintw( 2,1,"- Play 'Enter'");
    mvprintw( 3,1,"- Exit 'X'");
    mvprintw( 6,1,"How to play:");
    mvprintw( 7,1,"- 'W' to move up");
    mvprintw( 8,1,"- 'A' to move left");
    mvprintw( 9,1,"- 'S' to move down");
    mvprintw(10,1,"- 'D' to move right");

  time_t start_time;
  time_t current_time;

  start_time = time(NULL);
  current_time = time(NULL);

    while(1) {
        if(current_time-start_time > 2){
            break;
           // start_time = time(NULL);
        }
        current_time = time(NULL);
        trophy_flag = 0;
        //trophy_creation();
        int ch=getch();
        switch(ch) {
            case '\n':
                init_game(holder);
                game(holder);
                break;
            case 'X':
            case 'x':
                endwin();
                return 0;
            default:
                continue;
        }
        refresh();
    }
    endwin();
}
