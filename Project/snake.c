#include <curses.h>
#include <unistd.h>
#include <signal.h>


int direction_x = 1;
int direction_y = 0;
int old_direction_x, old_direction_y;
int turnPoint_x, turnPoint_y;
int head_x, head_y;
int snake_len = 5;

char border_ch='#';
char snake_ch='0';


void snake_pit_init(int (*holder)[COLS]) {
    for(int y=0; y<LINES-1; y++){   // Assign 0 for the whole matrix
        for(int x=0; x<COLS-1; x++){
            holder[y][x]=0;
        }
    }
    for(int y=0; y<LINES-1; y++){   // Borders's value is 2
        holder[y][0]=2;             // Left Border
        holder[y][COLS-2]=2;        // Right Border
    }
    for(int x=0; x<COLS-1; x++){
        holder[0][x]=2;             // Top Border
        holder[LINES-2][x]=2;       // Bottom Border
    }
}

void print_snake_pit(int (*holder)[COLS]) {
    for(int y=0; y<LINES-1; y++){
        for(int x=0; x<COLS-1; x++){
            if(holder[y][x]==2)
                mvaddch(y,x,border_ch);
            if(holder[y][x]==0)
                mvaddch(y,x,' ');
        }
    }
}


int main(){
    timeout(50);
    initscr();
    int holder[LINES][COLS]; // Snake pit matrix
    refresh();
    noecho();
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
                snake_pit_init(holder);
                print_snake_pit(holder);
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
//     while(1){
//         if (ch == 'Q' || ch == 'q') {
//             old_direction_x = direction_x;
//             old_direction_y = direction_y;
//             direction_y = 0;
//             direction_x = -1;
//             head_x = holder[0][0];
//             head_y = holder[0][1];
//         }
//
//         for(int i =0; i <= 5; i++){
//             if(holder[i][0] < head_x && holder[i][1] < head_y){
//                 holder[i][0] = old_direction_x * holder[i][0];
//                 holder[i][1] = old_direction_y * holder[i][1];
//             }
//             if(holder[i][0] == head_x && holder[i][1] > head_y){
//                 holder[i][0] = direction_x * holder[i][0];
//                 holder[i][1] = direction_y * holder[i][1];
//             }
//         }
//
//         for(int i =0; i <= 5; i++){
//             if(holder[i][0] < head_x && holder[i][1] < head_y){
//                 holder[i][0] = old_direction_x * holder[i][0];
//                 holder[i][1] = old_direction_y * holder[i][1];
//             }
//             if(holder[i][0] == head_x && holder[i][1] > head_y){
//                 holder[i][0] = direction_x * holder[i][0];
//                 holder[i][1] = direction_y * holder[i][1];
//             }
//         }
//
//         for(int i =0; i <= 5; i++){
//             move(holder[i][0], holder[i][1]);
//             addstr("e");
//         }
//
//     }
