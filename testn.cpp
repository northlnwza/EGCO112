#include <ncurses.h>
#include <string>

void drawLogin() {
    initscr();              // Start ncurses
    noecho();               // Don't echo user input
    cbreak();               // React instantly to key presses
    keypad(stdscr, TRUE);   // Enable arrow keys

    int row, col;
    getmaxyx(stdscr, row, col);

    // Draw a centered box
    int boxWidth = 40;
    int boxHeight = 10;
    int startY = (row - boxHeight) / 2;
    int startX = (col - boxWidth) / 2;

    WINDOW* loginWin = newwin(boxHeight, boxWidth, startY, startX);
    box(loginWin, 0, 0);
    mvwprintw(loginWin, 1, 12, "Login");
    mvwprintw(loginWin, 3, 2, "Username: ");
    mvwprintw(loginWin, 5, 2, "Password: ");
    wrefresh(loginWin);

    char username[30], password[30];
    mvwgetnstr(loginWin, 3, 12, username, 29);
    mvwgetnstr(loginWin, 5, 12, password, 29);

    mvwprintw(loginWin, 7, 10, "Logging in...");
    wrefresh(loginWin);
    getch();

    endwin();
}

int main()
{
    drawLogin();
    return (0);
}
