#ifndef MENU_CPP
#define MENU_CPP

#include "User.h"
#include "UI_tools.h"

#include <ncurses.h>
#include <string>
using namespace std;

void menu(){
    initscr();                    // Start ncurses
    cbreak();                     // Line buffering disabled
    noecho();                     // Don't echo input
    keypad(stdscr, TRUE);         // Enable special keys
    //mousemask(ALL_MOUSE_EVENTS, NULL); // Enable all mouse events
    start_color();
    use_default_colors();
    curs_set(0);                  // Hide the cursor

    if (!has_colors()) {
        endwin();
        printf("Your terminal doesn't support color!\n");
        exit(0);
    }
    else setup_color();

    int win_height = 24, win_width = 80;
    int starty = (LINES - win_height) / 2;
    int startx = (COLS - win_width) / 2;

    WINDOW* win = newwin(win_height, win_width, starty, startx);
    box(win, 0, 0); // Draw border

    screenLoading(win);

    header(win,"Ten");

    wrefresh(win);
    wgetch(win);
    delwin(win);
    endwin();
}



#endif