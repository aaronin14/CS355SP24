#include <curses.h>
#include <unistd.h>
#include <signal.h>


struct Position {
    int y,x;
};

// Legendary
char snake_ch='0';
// Snake's initial length
int snake_len = 5;
// Snake's starting head position
int start_x = 7;
int start_y = 2;
// Snake starting direction
int direction_x = 1;
int direction_y = 0;
// Snake's movement
struct Position snake[20];
int head_x, head_y;
int old_direction_x = 1;
int old_direction_y = 0;
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


// Aaron Nguyen
// Printing the whole game
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
    holder[head_y][head_x]=-1;
}


void game(int (*holder)[COLS]) {
    int ch;
    while(1) {
        print_game(holder);
        ch=getch();
        switch(ch) {
            case 'W':
            case 'w':
                if(direction_y!=1) {
                    direction_y = -1;
                    direction_x = 0;
                }
                break;
            case 'A':
            case 'a':
                if(direction_x!=1) {
                    direction_y = 0;
                    direction_x = -1;
                }
                break;
            case 'S':
            case 's':
                if(direction_y!=-1){
                    direction_y = 1;
                    direction_x = 0;
                }
                break;
            case 'D':
            case 'd':
                if(direction_x!=-1) {
                    direction_y = 0;
                    direction_x = 1;
                }
                break;
            case 'P':
            case 'p':
                // Should pause the game
                break;
            default:
                mvprintw(LINES-3,3,"You pressed \"%c\" key ",(char)ch);
                refresh();
        }
        snake_movement(holder);
        usleep(100000);
    }
    raise(SIGINT);
}


int main(){
    initscr();
    clear();
    noecho();
    curs_set(0);
    int holder[LINES][COLS]; // Snake pit

    game_init(holder);
    game(holder);

    // Aaron Nguyen
    // Game Menu and Control
//     box(stdscr, 0, 0);
//     mvprintw( 1,1,"SNAKE GAME");
//     mvprintw( 2,1,"- Play 'Enter'");
//     mvprintw( 3,1,"- Exit 'X'");
//     mvprintw( 6,1,"How to play:");
//     mvprintw( 7,1,"- 'W' to move up");
//     mvprintw( 8,1,"- 'A' to move left");
//     mvprintw( 9,1,"- 'S' to move down");
//     mvprintw(10,1,"- 'D' to move right");
//     while(1) {
//         int ch=getch();
//         switch(ch) {
//             case '\n':
//                 game_init(holder);
//                 snake_movement(holder);
//                 getch();
//                 break;
//             case 'X':
//             case 'x':
//                 endwin();
//                 return 0;
//             default:
//                 continue;
//         }
//         refresh();
//     }
//     endwin();
}
