#include <curses.h>
#include <unistd.h>
#include <signal.h>


// Legendary
char border_ch='#';
char snake_ch='0';
// Snake's initial length
int snake_len = 5;
// Snake's starting position
int start_x = 7;
int start_y = 2;
// Snake starting direction
int direction_x = 1;
int direction_y = 0;
// Keeping track of Snake's movement
int head_x, head_y;
int old_direction_x, old_direction_y;
int turnPoint_x, turnPoint_y;


// Aaron Nguyen
// Initialize the snake pit, and the snake
void game_init(int (*holder)[COLS]) {
    clear(); // Clear the screen

    // Snake pit
    for(int y=0; y<LINES-1; y++){   // Empty space's value is 0
        for(int x=0; x<COLS-1; x++)
            holder[y][x]=0;
    }
    for(int y=0; y<LINES-1; y++){   // Borders's value is -2
        holder[y][0]=-2;                 // Left Border
        holder[y][COLS-2]=-2;            // Right Border, COLS-1 doesn't get displayed
    }
    for(int x=0; x<COLS-1; x++){
        holder[0][x]=-2;                 // Top Border
        holder[LINES-2][x]=-2;           // Bottom Border, LINES-1 doesn't get displayed
    }

    // Snake init - Snake's value is -1
    head_x = start_x;
    head_y = start_y;
    for(int i=0; i<snake_len; i++) {    //
        holder[head_y][head_x-i]=-1;
    }
}


// Aaron Nguyen
// Printing the whole game
void print_game(int (*holder)[COLS]) {
    for(int y=0; y<LINES-1; y++){
        for(int x=0; x<COLS-1; x++){
            if(holder[y][x]==-2)
                mvaddch(y,x,border_ch);
            if(holder[y][x]==-1)
                mvaddch(y,x,'0');
            if(holder[y][x]==0)
                mvaddch(y,x,' ');
        }
    }
    refresh();
}


void snake_movement(int (*holder)[COLS]) {
    while(1){
        int ch=getch();
        if (ch == 'S' || ch == 's') {
            old_direction_x = direction_x;
            old_direction_y = direction_y;
            direction_y = -1;
            direction_x = 0;
            head_x = holder[0][0];
            head_y = holder[0][1];
        }

        for(int i =0; i <= 5; i++){
            if(holder[i][0] < head_x && holder[i][1] < head_y){
                holder[i][0] = old_direction_x * holder[i][0];
                holder[i][1] = old_direction_y * holder[i][1];
            }
            if(holder[i][0] == head_x && holder[i][1] > head_y){
                holder[i][0] = direction_x * holder[i][0];
                holder[i][1] = direction_y * holder[i][1];
            }
        }

        for(int i =0; i <= 5; i++){
            if(holder[i][0] < head_x && holder[i][1] < head_y){
                holder[i][0] = old_direction_x * holder[i][0];
                holder[i][1] = old_direction_y * holder[i][1];
            }
            if(holder[i][0] == head_x && holder[i][1] > head_y){
                holder[i][0] = direction_x * holder[i][0];
                holder[i][1] = direction_y * holder[i][1];
            }
        }

        for(int i =0; i <= 5; i++){
            move(holder[i][0], holder[i][1]);
            addstr("e");
        }

    }
}


int main(){
    timeout(50);
    initscr();
    int holder[LINES][COLS]; // Snake pit
    refresh();
    noecho();

    // Aaron Nguyen
    // Game Menu and Control
    mvprintw( 0,0,"SNAKE GAME");
    mvprintw( 1,0,"---------------");
    mvprintw( 2,0,"- Play 'Enter'");
    mvprintw( 3,0,"- Exit 'X'");
    mvprintw( 6,0,"How to play:");
    mvprintw( 7,0,"- 'W' to move up");
    mvprintw( 8,0,"- 'A' to move left");
    mvprintw( 9,0,"- 'S' to move down");
    mvprintw(10,0,"- 'D' to move right");
    while(1) {
        int ch=getch();
        switch(ch) {
            case '\n':
                game_init(holder);
                print_game(holder);
                getch();
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
