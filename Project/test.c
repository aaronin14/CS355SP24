#include <curses.h>

int main() {
    initscr();
    clear();
    mvprintw(0,0,"LINES = %d, COLS = %d, Perimeter = %d", LINES, COLS, LINES+COLS);
    getch();
    endwin();
    return 0;
}
