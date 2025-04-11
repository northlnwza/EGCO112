#include <ncurses.h>

int main() {
    initscr();                    // Start ncurses
    cbreak();                     // Line buffering disabled
    noecho();                     // Don't echo input
    keypad(stdscr, TRUE);         // Enable special keys
    mousemask(ALL_MOUSE_EVENTS, NULL); // Enable all mouse events
    curs_set(0);                  // Hide the cursor

    printw("Click anywhere (press 'q' to quit)");
    refresh();

    // Create a centered popup window
    int win_height = 10, win_width = 40;
    int starty = (LINES - win_height) / 2;
    int startx = (COLS - win_width) / 2;
    WINDOW* win = newwin(win_height, win_width, starty, startx);
    box(win, 0, 0); // Draw border
    wrefresh(win);

    MEVENT event;
    int ch;

    while ((ch = getch()) != 'q') {
        if (ch == KEY_MOUSE) {
            if (getmouse(&event) == OK) {
                mvprintw(2, 0, "Mouse Click Detected!");
                mvprintw(3, 0, "Position: y = %d, x = %d   ", event.y, event.x);
                mvprintw(4, 0, "Button State: %ld         ", event.bstate);
                refresh();
            }
        } else {
            mvprintw(5, 0, "Key pressed: %d           ", ch);
            refresh();
        }
    }

    delwin(win); // Delete the window
    endwin();
    return 0;
}
// This code initializes a simple ncurses application that detects mouse clicks and key presses.