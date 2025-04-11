#include <ncurses.h>

int main() {
    // Initialize ncurses
    initscr();              // Start curses mode
    cbreak();               // Disable line buffering
    noecho();               // Don't echo() while we do getch
    keypad(stdscr, TRUE);   // Enable special keys (arrows, etc.)

    // Print to the center of the screen
    int row, col;
    getmaxyx(stdscr, row, col); // Get screen size
    mvprintw(row / 2, (col - 20) / 2, "Hello, ncurses world!");

    // Wait for user input
    mvprintw(row - 2, 0, "Press any key to exit...");
    getch();

    // End ncurses mode
    endwin();

    return 0;
}