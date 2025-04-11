#include <ncurses.h>
#include <string.h> // For strlen()

void draw_button(int y, int x, const char* label, bool selected) {
    if (selected) {
        attron(A_REVERSE); // Highlight selected button
    }
    mvprintw(y, x, "[ %s ]", label);
    if (selected) {
        attroff(A_REVERSE);
    }
}

int main() {
    initscr();            // Start ncurses
    cbreak();             // Disable line buffering
    noecho();             // Don’t echo input
    keypad(stdscr, TRUE); // Enable arrow keys
    curs_set(0);          // Hide cursor

    const char* buttons[2] = {"OK", "Cancel"};
    int highlight = 0; // Index of the currently selected button
    int choice = -1;

    while (true) {
        clear();
        mvprintw(5, 10, "Use LEFT/RIGHT to choose, ENTER to select:");

        // Draw both buttons
        draw_button(7, 10, buttons[0], highlight == 0);
        draw_button(7, 25, buttons[1], highlight == 1);

        int ch = getch();

        if (ch == KEY_LEFT || ch == '\t') {
            highlight = (highlight - 1 + 2) % 2; // Loop back
        } else if (ch == KEY_RIGHT) {
            highlight = (highlight + 1) % 2; // Move right
        } else if (ch == '\n') {
            choice = highlight;
            break; // Exit loop
        }
    }

    clear();
    if (choice == 0) {
        mvprintw(10, 10, "You selected OK!");
    } else {
        mvprintw(10, 10, "You selected Cancel!");
    }

    refresh();
    getch(); // Wait before closing
    endwin(); // Exit ncurses

    return 0;
}
