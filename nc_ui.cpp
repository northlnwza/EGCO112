#include <ncurses.h>
#include <string>
#include "Auth.h"
#include "UserList.h"
#include "User.h"
#include "passdata.h"

using namespace std;

void showCentered(WINDOW* win, int y, const string& text)
{
    int x = (getmaxx(win) - text.length()) / 2;
    mvwprintw(win, y, x, "%s", text.c_str());
}

void loginScreen() {
    initscr();
    //noecho();
    cbreak();
    keypad(stdscr, TRUE);

    int height = 15, width = 50;
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;

    WINDOW* win = newwin(height, width, starty, startx);
    box(win, 0, 0);
    refresh();
    wrefresh(win);

    char uname[30], pass[30];
    int choice;

    while (true) {
        werase(win);
        box(win, 0, 0);
        showCentered(win, 1, "AUTH SYSTEM - NCURSES");
        mvwprintw(win, 3, 2, "[1] Login");
        mvwprintw(win, 4, 2, "[2] Register");
        mvwprintw(win, 5, 2, "[3] Forgot Password");
        mvwprintw(win, 6, 2, "[4] Exit");
        mvwprintw(win, 8, 2, "Enter choice: ");
        wrefresh(win);
        wscanw(win, "%d", &choice);

        if (choice == 1) {
            werase(win); box(win, 0, 0);
            mvwprintw(win, 2, 2, "Username: ");
            wrefresh(win);
            wgetnstr(win, uname, 30);
            mvwprintw(win, 3, 2, "Password: ");
            wrefresh(win);
            wgetnstr(win, pass, 30);
            if (Auth::login(uname, pass)) 
            {
                showCentered(win, 5, "Login Successful!");
                testpass(uname, win);
                wrefresh(win);
                wgetch(win);
            } else {
                showCentered(win, 5, "Login Failed!");
                wrefresh(win);
                wgetch(win);
            }
        } else if (choice == 2) {
            werase(win); box(win, 0, 0);
            char new_uname[30], new_pass[30];
            Role role;
            int roleInput;
            mvwprintw(win, 2, 2, "New Username: ");
            wgetnstr(win, new_uname, 30);
            mvwprintw(win, 3, 2, "New Password: ");
            wgetnstr(win, new_pass, 30);
            mvwprintw(win, 4, 2, "Role (0 = Student, 1 = Staff): ");
            wscanw(win, "%d", &roleInput);
            role = static_cast<Role>(roleInput);
            if (Auth::registerUser(new_uname, new_pass, role)) 
            {
                showCentered(win, 5, "Registration Successful!");
            } 
            else {
                showCentered(win, 5, "Registration Failed!");
            }
            wrefresh(win);
            wgetch(win);
        } else if (choice == 3) {
            werase(win); box(win, 0, 0);
            char uname[30];
            mvwprintw(win, 2, 2, "Enter Username: ");
            wgetnstr(win, uname, 30);
            string recovered = Auth::recoverPassword(uname);
            mvwprintw(win, 4, 2, "Recovered Password: %s", recovered.c_str());
            wrefresh(win);
            wgetch(win);
        } else {
            break;
        }
    }

    endwin();
}
