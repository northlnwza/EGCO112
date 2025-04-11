#ifndef MENU_CPP
#define MENU_CPP

#include "User.h"
#include "Tools.h"

#include <ncurses.h>
#include <string>
using namespace std;

void menu(){
    initscr();                    // Start ncurses
    cbreak();                     // Line buffering disabled
    noecho();                     // Don't echo input
    keypad(stdscr, TRUE);         // Enable special keys
    //mousemask(ALL_MOUSE_EVENTS, NULL); // Enable all mouse events
    curs_set(0);                  // Hide the cursor

    int win_height = 24, win_width = 80;
    int starty = (LINES - win_height) / 2;
    int startx = (COLS - win_width) / 2;

    WINDOW* win = newwin(win_height, win_width, starty, startx);
    box(win, 0, 0); // Draw border

    int i;string ten="Ten";
    wattron(win,A_BOLD);
    showCentered(win,2,"Welcome Student : "+ten);
    wattroff(win,A_BOLD);
    for (i=1;i<79;i++) {mvwprintw(win,4,i,"-");}
    
    wrefresh(win);
    wgetch(win);
    delwin(win);
    endwin();
}

void showCentered(WINDOW* win, int y, const string& text) {
    int x = (getmaxx(win) - text.length()) / 2;
    mvwprintw(win, y, x, "%s", text.c_str());
}

#endif