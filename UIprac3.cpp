
#include <ncurses.h>

int main() {
    initscr();              // Start ncurses
    cbreak();               // Disable line buffering
    noecho();               // Don't show keypresses
    keypad(stdscr, TRUE);   // Enable special keys
    curs_set(0);            // Hide cursor

    int height = 30, width = 60;
    int starty = (LINES - height) / 2;  // Calculate vertical center
    int startx = (COLS - width) / 2;   // Calculate horizontal center

    // Create a new window
    WINDOW* popup = newwin(height, width, starty, startx);
    box(popup, 0, 0); // Draw a border around the window

    // Print text inside the popup
    mvwprintw(popup, 1, (width - 24) / 2, "Welcome to ncurses UI!");
    mvwprintw(popup, 3, 4, "This is a simple popup box.");
    mvwprintw(popup, 5, 4, "Press any key to continue...");

    refresh();
    wrefresh(popup); // Refresh to show the window


    // Wait for user input
    getch(); // Wait for a keypress to exit

    // Clean up
    delwin(popup); // Delete the window
    endwin(); // End ncurses mode and restore the terminal

    return 0;
}
