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
//int holder[LINES][COLS];
int **holder;
int add_amount = 1;
// Snake's position is stored in an array of Postition struct
struct Position {
    int y,x;
};
struct Position snake[SNAKE_MAX_LENGTH];

//Richard
void trophy_creation();
// Initialize the snake pit, and the snake
    void init_game() {
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

//Richard
void trophy_creation(){
        if(trophy_x == -1){

        }
        else{
            holder[trophy_y][trophy_x] = 0;
        }
        trophy_x = rand() % 60 + 1;
        trophy_y = rand() % 5 + 1;
        add_amount = rand() % 9 + 1;
        holder[trophy_y][trophy_x] = -10;
        alarm(20);
    }


//Richard
// Printing the whole game


void print_game() {
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

void over(){
    mvprintw(1, 1, "SNAKE GAME OVER");
}

void snake_movement() {
    int tail_x = snake[snake_len-1].x;
    int tail_y = snake[snake_len-1].y;
    //Richard
    holder[tail_y][tail_x]=0;           // Assign 0 to the last tail position
    if(snake[0].x + direction_x == 177  || snake[0].y + direction_y == 12){
        mvprintw(1, 1, "SNAKE GAME");

        exit(1);
    }
    if(snake[0].x + direction_x == 0  || snake[0].y + direction_y == 0){
        exit(1);
    }
    if(holder[snake[0].y + direction_y][snake[0].x + direction_x] == -1){
        exit(1);
    }
    else{
    for(int i=snake_len-1; i>0; i--) {  // Move forward
        snake[i].x=snake[i-1].x;
        snake[i].y=snake[i-1].y;
    }
    }
    if(snake[0].x + direction_x == trophy_x && snake[0].y + direction_y== trophy_y){
        snake_len += add_amount;
    }

    snake[0].x += direction_x;
    snake[0].y += direction_y;
    int head_x = snake[0].x;
    int head_y = snake[0].y;
    holder[head_y][head_x]=-1;          // Assing -1 to the new head position
}


//void game(int (*holder)[COLS]) {
void game() {
    int ch;
    snake_movement();
    int speed;
    while(1) {
        speed = 700 / snake_len;
        timeout(speed);
        direction_x = old_direction_x;
        direction_y = old_direction_y;
        print_game();
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
        snake_movement();
    }
}


int main() {
    holder = malloc(LINES * sizeof(int *));

    for (int i = 0; i < LINES; i++) {
        holder[i] = malloc(COLS * sizeof(int));
        // Check if memory allocation for the row succeeded
        if (holder[i] == NULL) {
            printf("Memory allocation failed\n");

            // Free previously allocated memory
            for (int j = 0; j < i; j++) {
                free(holder[j]);
            }
            free(holder);
            return 1; // Return an error code
        }
    }

    initscr();
    clear();
    noecho();
    curs_set(0);
    //holder[LINES][COLS]; // Snake pit
    int trophy_flag = 0;

    // Aaron
    // Game Menu and Control
    box(stdscr, 0, 0);
    int menu_x=COLS/2-4;
    int menu_y=LINES/2-8;
    mvprintw(menu_y,menu_x,"SNAKE GAME");
    mvprintw(menu_y+2,menu_x-2,"- 'Enter' Play");
    mvprintw(menu_y+3,menu_x-2,"- 'X'     Exit");
    mvprintw(menu_y+5,menu_x-2,"How to play:");
    mvprintw(menu_y+6,menu_x-2,"- 'W' to move up");
    mvprintw(menu_y+7,menu_x-2,"- 'A' to move left");
    mvprintw(menu_y+8,menu_x-2,"- 'S' to move down");
    mvprintw(menu_y+9,menu_x-2,"- 'D' to move right");

    signal (SIGALRM, trophy_creation);
    alarm (20);
    while (1) {
        trophy_flag = 0;
        int ch = getch();
        switch (ch) {
            case '\n':
               init_game();
               game();
                break;
            case 'X':
            case 'x':
                endwin();
                return 0;
            default:
                break;
        }
        refresh();
    }

    endwin();
    return 0;
}
