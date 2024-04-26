#include <curses.h>
#include <unistd.h>
#include <signal.h>


#define INITIAL_LENGTH 5
#define SNAKE_MAX_LENGTH 25

//Richard
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
struct Position snake[SNAKE_MAX_LENGTH];


// Aaron
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

//Richard
// Printing the whole screen
void print_game(int (*holder)[COLS]) {
    box(stdscr, 0, 0);
    for(int y=0; y<LINES-1; y++){
        for(int x=0; x<COLS-1; x++){
            if(holder[y][x]==-1)
                mvaddch(y,x,'0');
            if(holder[y][x]==0)
                mvaddch(y,x,' ');
        }
    }
    refresh();
}


// Aaron
// Updating the snake position
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

    //Richard
    while(1) {
        timeout(200);
        direction_x = old_direction_x;
        direction_y = old_direction_y;
        print_game(holder);
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
    while(1) {
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
