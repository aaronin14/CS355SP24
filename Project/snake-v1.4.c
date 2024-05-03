#include <curses.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


// Richard
#define INITIAL_LENGTH 3
// Trophy
int trophy_flag;
int trophy_x=5;
int trophy_y=10;
int trophy_value;
int trophy_timer;
// Snake is drawn by character '0'
char snake_ch = '0';
// Snake's length
int snake_len = INITIAL_LENGTH;
int current_snake_len = INITIAL_LENGTH;
int snake_max_len;
// Snake's starting head position
int start_x = 2+INITIAL_LENGTH;
int start_y = 2;
// Snake starting direction
int direction_x = 1;
int direction_y = 0;
// Snake's position is stored in an array of Postition struct
struct Position {
    int y,x;
};

// Aaron
// Generate random a integer from a range
int random_number(int min, int max) {
    return min+rand()%(max-min+1);
}

// Richard
// Create trophy
void create_trophy(int (*holder)[COLS]){
    trophy_x = random_number(1, COLS-1);
    trophy_y = random_number(1, LINES-1);
    trophy_value = random_number(1, 9);
    trophy_timer = random_number(1, 9) * 1000;
    trophy_flag=1;
    holder[trophy_y][trophy_x] = trophy_value;
}

// Aaron
// Remove trophy
void remove_trophy(int (*holder)[COLS]){
    trophy_flag=0;
    holder[trophy_y][trophy_x]=0;
}

// Aaron
// Initialize the snake pit, the snake, and the trophy
void init_game(int (*holder)[COLS], struct Position *snake) {
    clear();
    // Initialize the Snake pit
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
    // Initialize the Snake
    snake[0].x = start_x;
    snake[0].y = start_y;
    for(int i=0; i<snake_len; i++) {
        snake[i].x=start_x-i;
        snake[i].y=start_y;
        holder[snake[0].y][snake[0].x-i]=-1;    // Snake's value is -1
    }
    // Initialize the trophy
    create_trophy(holder);
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
            if(holder[y][x]>0 && holder[y][x]<10 && trophy_flag==1)
                mvaddch(y,x,holder[y][x]+'0');
        }
    }
    refresh();
}

// Aaron
// Print the check_gameover screen
void print_gameover(char ch){
    clear();
    box(stdscr, 0, 0);
    int menu_x=COLS/2-6;
    int menu_y=LINES/2;
    mvprintw(menu_y,menu_x,"GAMEOVER");
    switch(ch) {
        case 'b':
            mvprintw(menu_y+1,menu_x-5,"Ran into the border");
            break;
        case 's':
            mvprintw(menu_y+1,menu_x-3,"Ran into itself");
            break;
        case 'r':
            mvprintw(menu_y+1,menu_x-3,"Tried to reverse");
            break;
        case 'w':
            mvprintw(menu_y+1,menu_x-1,"You Won!!!");
            break;
    }
    nodelay(stdscr, FALSE);
    getch();
    endwin();
    raise(SIGINT);
}

// Aaron
// Increase snake length or keep it moving
void update_snake_position(int (*holder)[COLS], struct Position *snake) {
    if(snake_len < current_snake_len){
        snake_len++;
        int tail_x=snake[snake_len-1].x;
        int tail_y=snake[snake_len-1].y;
        holder[tail_y][tail_x]=-1;
    } else {
        int tail_x=snake[snake_len-1].x;
        int tail_y=snake[snake_len-1].y;
        holder[tail_y][tail_x]=0;
    }
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

// Richard
// Gameover logic
void check_gameover(int (*holder)[COLS], struct Position *snake) {
    // Snake hits Right border or Bottom Border
    if(snake[0].x + direction_x == COLS || snake[0].y + direction_y == LINES) {
        print_gameover('b');
    }
    // Snake hits Left border or Top Border
    if(snake[0].x + direction_x == 0 || snake[0].y + direction_y == 0) {
        print_gameover('b');
    }
    // Snake hits itself
    if(holder[snake[0].y + direction_y][snake[0].x + direction_x] == -1) {
        print_gameover('s');
    }
}

// Richard
// Check Collision
void check_collision(int (*holder)[COLS], struct Position *snake) {
    // Check if the game is over
    check_gameover(holder, snake);
    // Snake reached the trophy
    if(snake[0].x == trophy_x && snake[0].y == trophy_y) {
        current_snake_len += trophy_value;
        create_trophy(holder);
        if(current_snake_len>=snake_max_len)
            print_gameover('w');
    }
    update_snake_position(holder, snake);
}


// Richard
//
void game(int (*holder)[COLS], struct Position *snake) {
    int ch;
    int delay_speed;
    while(1) {
        delay_speed = 500000 / (current_snake_len);
        if(trophy_timer<=0) {
            remove_trophy(holder);
            create_trophy(holder);
            refresh();
        }
        ch=getch();
        switch(ch) {
            case KEY_UP:
            case 'W':
            case 'w':
                if(direction_y==1)
                    print_gameover('r');
                else {
                    direction_x=0;
                    direction_y=-1;
                }
                break;
            case KEY_LEFT:
            case 'A':
            case 'a':
                if(direction_x==1)
                    print_gameover('r');
                else {
                    direction_x=-1;
                    direction_y=0;
                }
                break;
            case KEY_DOWN:
            case 'S':
            case 's':
                if(direction_y==-1)
                    print_gameover('r');
                else {
                    direction_x=0;
                    direction_y=1;
                }
                break;
            case KEY_RIGHT:
            case 'D':
            case 'd':
                if(direction_x==-1)
                    print_gameover('r');
                else {
                    direction_x=1;
                    direction_y=0;
                }
                break;
            case 'X':
            case 'x':
                endwin();
                raise(SIGINT);
            default:
                break;
        }
        check_collision(holder, snake);
        print_game(holder);
        usleep(delay_speed);
        trophy_timer -=50;
    }
}


// Aaron
int main(){
    initscr();
    clear();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    // Initialize the Snake pit
    int holder[LINES][COLS];
    // Snake Max Length / Half of the terminal Perimeter
    snake_max_len=(LINES+COLS)/2;
    // Initialize Snake Position
    struct Position snake[snake_max_len];
    // Game Menu and Control
    box(stdscr, 0, 0);
    int menu_x=COLS/2-8;
    int menu_y=LINES/2-6;
    mvprintw(menu_y   ,menu_x  ,"SNAKE GAME");
    mvprintw(menu_y+ 2,menu_x-1,"'Enter' Play");
    mvprintw(menu_y+ 3,menu_x-1,"'X'     Exit");
    mvprintw(menu_y+ 5,menu_x-1,"How to play:");
    mvprintw(menu_y+ 7,menu_x-8,"'W' or 'UP-ARROW' to move up");
    mvprintw(menu_y+ 8,menu_x-8,"'A' or 'LEFT-ARROW' to move left");
    mvprintw(menu_y+ 9,menu_x-8,"'S' or 'DOWN-ARROW' to move down");
    mvprintw(menu_y+10,menu_x-8,"'D' or 'RIGHT-ARROW' to move right");

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
