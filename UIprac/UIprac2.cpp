#include <ncurses.h>

int main() {
    initscr();              // Start ncurses
    cbreak();               // Disable line buffering
    noecho();               // Don't echo keypresses
    keypad(stdscr, TRUE);   // Enable arrow keys
    curs_set(0);            // Hide the cursor

    int x = 10, y = 5;
    int ch;

    // Initial position
    mvaddch(y, x, '@');
    refresh();

    while ((ch = getch()) != 'q') { // Press 'q' to quit
        // Clear old position
        mvaddch(y, x, ' ');

        switch (ch) {
            case KEY_UP:    y--; break;
            case KEY_DOWN:  y++; break;
            case KEY_LEFT:  x--; break;
            case KEY_RIGHT: x++; break;
        }

        // Draw new position
        mvaddch(y, x, '@');
        refresh();
    }

    endwin(); // Restore terminal
    return 0;
}