
#include <ncurses.h>
#include <cstdlib>
#include <string>
using namespace std;
#include <iostream>

void show_popup(int h,int w,string message) {
    int height = h;
    int width = w;
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;

    // Create a new window
    WINDOW* popup = newwin(height, width, starty, startx);
    box(popup, 0, 0); // Draw border
    //mvwprintw(popup, 2, (width - message.length()) / 2, message.c_str());
    //mvwprintw(popup, 4, (width) / 2, "Press any key to close");
    wrefresh(popup);

    getch(); // Wait for user input

    delwin(popup); // Delete the window
}

int main() {
    initscr();            // Start ncurses mode
    cbreak();             // Disable line buffering
    noecho();             // Don't echo() while we do getch
    keypad(stdscr, TRUE); // Enable function keys

    printw("This is the main screen.");
    refresh();

    show_popup(7,40,"Hello from ncurses!");
    mvwprintw(popup, 2, width / 2, "hi");
    show_popup(2,38," ");
    mvwprintw(popup, 2, width / 2, "hi");

    endwin(); // End ncurses mode
    return 0;
}