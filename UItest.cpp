#include <ncurses.h>
#include <iostream>
#include "Button.h"

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    curs_set(0);

    int i;
    for(i=0;i<140;i++){mvprintw(0,i,"%d",i%10);}

    int win_h = 10, win_w = 40;
    int win_y = (LINES - win_h) / 2;
    int win_x = (COLS - win_w) / 2;

    WINDOW* win = newwin(win_h, win_w, win_y, win_x);
    werase(win);
    mvwprintw(win, 1, 2, "Click a button:");
    box(win, 0, 0);
    getch();
    Button okBtn(win, 5, 8, "OK");
    Button cancelBtn(win, 5, 22, "Cancel");

    okBtn.draw();
    cancelBtn.draw();

    MEVENT event;
    int ch;

    while ((ch = getch()) != 'q') {
        if (ch == KEY_MOUSE && getmouse(&event) == OK) {
            int y = event.y ;
            int x = event.x ;
            mvwprintw(win,8,15,"%d %d clicked!",y,x);
            wrefresh(win);
            if (okBtn.isClicked(y-win_y, x-win_x)) {
                mvprintw(2, 0, "You clicked OK     ");
                //break;
            }
            else if (cancelBtn.isClicked(y-win_y, x-win_x)) {
                mvprintw(2, 0, "You clicked Cancel ");
                //break;
            }
            else mvprintw(2, 0, "\n");
        }
        refresh();
    }
    wrefresh(win);
    refresh();
    getch();
    delwin(win);
    endwin();
    return 0;
}
