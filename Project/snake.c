#include <curses.h>
#include <unistd.h>

int direction_x = 1;
int direction_y = 0;
int old_direction_x, old_direction_y;
int turnPoint_x, turnPoint_y;
int head_x, head_y;
int snake_len = 5;

char border_ch='#';
char snake_ch='0';

void menu() {
    mvprintw(0,0,"SNAKE");
    mvprintw(1,0,"> Play");
    mvprintw(2,0,"  Quit");
}

void snake_pit_init(int **holder, int rows, int cols) {
    for(int y=0; y<rows-1; y++){
        holder[y][0]=4;
        holder[y][cols-2]=4;
    }
    for(int x=0; x<cols-1; x++){
        holder[0][x]=4;
        holder[rows-2][x]=4;
    }
    for(int y=1; y<rows-2; y++){
        for(int x=1; x<cols-2; x++){
            holder[y][x]=0;
        }
    }
}

void print_snake_pit(int **holder, int rows, int cols) {
    for(int y=0; y<rows-1; y++){
        for(int x=0; x<cols-1; x++){
            if(holder[y][x]==4)
                mvaddch(y,x,border_ch);
            else
                mvaddch(y,x,' ');
        }
    }
}


int main(){
    int holder[LINES][COLS]; // Snake pit matrix
    timeout(50);
    initscr();
    refresh();
    noecho();
    // menu();
    // getch();
    snake_pit_init((int **)holder, LINES, COLS);
    print_snake_pit((int **)holder, LINES, COLS);
    getch();
    endwin();

//     while(1){
//         if (ch == 'Q' || ch == 'q') {
//             // turnPoint_x = ;
//             // turnPoint_y = ;
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
}
