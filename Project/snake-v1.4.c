#include <curses.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


// Richard & Aaron
#define INITIAL_LENGTH 5
// Trophy
int trophy_flag;
int trophy_x = -1;
int trophy_y = -1;
int add_amount = 1;
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
// Snake's position is stored in an array of Postition struct
struct Position {
    int y,x;
};

// Richard & Aaron
void trophy_creation(int (*holder)[COLS]){
    int trophy_value = rand()%9+1;
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

// Aaron
// Initialize the snake pit, and the snake
void init_game(int (*holder)[COLS], struct Position *snake) {
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

// Aaron
// Printing the whole screen
void print_game(int (*holder)[COLS]) {
    box(stdscr, 0, 0);
    for(int y=0; y<LINES-1; y++){
        for(int x=0; x<COLS-1; x++){
            if(holder[y][x]==-1)
                mvaddch(y,x,'0');
            if(holder[y][x]==0)
                mvaddch(y,x,' ');
            if(holder[y][x]>0 && holder[y][x]<10)
                mvaddch(y,x,holder[y][x]);
        }
    }
    refresh();
}

// Aaron
// Print the gameover screen
void print_gameover(char c){
    clear();
    box(stdscr, 0, 0);
    int menu_x=COLS/2-6;
    int menu_y=LINES/2;
    mvprintw(menu_y,menu_x,"GAMEOVER");
    if(c=='b')
        mvprintw(menu_y+1,menu_x,"Run into the border");
    if(c=='s')
        mvprintw(menu_y+1,menu_x,"Run into itself");
    if(c=='r')
        mvprintw(menu_y+1,menu_x,"Trying to reverse");
    getch();
    endwin();
}

// Richard & Aaron
// Check if game is over
void gameover(int (*holder)[COLS], struct Position *snake) {
    // Snake hits Right border or Bottom Border
    if(snake[0].x + direction_x == COLS  || snake[0].y + direction_y == LINES){
        print_gameover('b');
        exit(1);
    }
    // Snake hits Left border or Top Border
    if(snake[0].x + direction_x == 0  || snake[0].y + direction_y == 0){
        print_gameover('b');
        exit(1);
    }
    // Snake hits itself
    if(holder[snake[0].y + direction_y][snake[0].x + direction_x] == -1){
        print_gameover('s');
        exit(1);
    }
}

// Aaron
// Updating the snake position
void update_snake_position(int (*holder)[COLS], struct Position *snake) {
    int tail_x=snake[snake_len-1].x;
    int tail_y=snake[snake_len-1].y;
    // Assign 0 to the previous tail position
    holder[tail_y][tail_x]=0;
    // Assign snake new position
    for(int i=snake_len-1; i>0; i--) {
        snake[i].x=snake[i-1].x;
        snake[i].y=snake[i-1].y;
    }
    // Assign new head position
    snake[0].x += direction_x;
    snake[0].y += direction_y;
    int head_x = snake[0].x;
    int head_y = snake[0].y;
    holder[head_y][head_x]=-1;
}


void game(int (*holder)[COLS], struct Position *snake) {
    int ch;
    update_snake_position(holder, snake);

    //Richard
    while(1) {
        timeout(200);
        direction_x = old_direction_x;
        direction_y = old_direction_y;
        print_game(holder);
        ch=getch();
        switch(ch) {
            case KEY_UP:
            case 'W':
            case 'w':
                if(direction_y!=1) {
                    direction_x=0;
                    direction_y=-1;
                    old_direction_x = direction_x;
                    old_direction_y = direction_y;
                }
                break;
            case KEY_LEFT:
            case 'A':
            case 'a':
                if(direction_x!=1) {
                    direction_x=-1;
                    direction_y=0;
                    old_direction_x = direction_x;
                    old_direction_y = direction_y;
                }
                break;
            case KEY_DOWN:
            case 'S':
            case 's':
                if(direction_y!=-1) {
                    direction_x=0;
                    direction_y=1;
                    old_direction_x = direction_x;
                    old_direction_y = direction_y;
                }
                break;
            case KEY_RIGHT:
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
        gameover(holder, snake);
        update_snake_position(holder, snake);
    }
}


int main(){
    initscr();
    clear();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    // Aaron
    // Initialize the Snake pit
    int holder[LINES][COLS];
    // Snake Max Length / Half of the terminal Perimeter
    int max_length=LINES+COLS;
    // Initialize Snake Position
    struct Position snake[max_length];
    // Game Menu and Control
    box(stdscr, 0, 0);
    int menu_x=COLS/2-8;
    int menu_y=LINES/2-8;
    mvprintw(menu_y,menu_x,"SNAKE GAME");
    mvprintw(menu_y+2,menu_x-1,"'Enter' Play");
    mvprintw(menu_y+3,menu_x-1,"'X'     Exit");
    mvprintw(menu_y+5,menu_x-3,"  How to play:");
    mvprintw(menu_y+7,menu_x-8,"'W' or 'UP-ARROW' to move up");
    mvprintw(menu_y+8,menu_x-8,"'A' or 'LEFT-ARROW' to move left");
    mvprintw(menu_y+9,menu_x-8,"'S' or 'DOWN-ARROW' to move down");
    mvprintw(menu_y+10,menu_x-8,"'D' or 'RIGHT-ARROW' to move right");

    signal(SIGALRM, trophy_creation(holder));
    alarm(20);
    while(1) {
        trophy_flag=0;
        int ch=getch();
        switch(ch) {
            case '\n':
                init_game(holder, snake);
                game(holder, snake);
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
    return 0;
}
