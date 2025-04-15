#include <ncurses.h>
#include <string>
using namespace std;

#include "Auth.h"
#include "UserList.h"
#include "User.h"
#include "passdata.h"
#include "menu.h"
#include "UI_tools.h"

void auth_header(WINDOW*);

void loginScreen() {
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    start_color();
    use_default_colors();
    if (!has_colors()) {
        endwin();
        printf("Your terminal doesn't support color!\n");
        exit(0);
    } else setup_color();

    int height = 24, width = 80;
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;

    WINDOW* win = newwin(height, width, starty, startx);
    keypad(win, TRUE);
    screenLoading(win, "Starting...", 2);

    char uname[30], pass[30];
    int choice;

    const char* menuItems[] = {
        "Login",
        "Register",
        "Forgot Password",
        "Exit"
    };
    int numItems = sizeof(menuItems) / sizeof(menuItems[0]);
    static int highlight = 0;
    int input;

    while (true) {
        // Draw the menu
        auth_header(win);
        bottom(win,"-");

        wattron(win, A_BOLD);
        for (int i = 0; i < numItems; ++i) {
            if (i == highlight) wattron(win, A_REVERSE);
            mvwprintw(win, 6 + i * 2, 3, "[%d]  %s ", i + 1, menuItems[i]);
            if (i == highlight) wattroff(win, A_REVERSE);
        }
        wattroff(win, A_BOLD);
        //mvwprintw(win, 14, 3, "Use ↑ ↓ arrows and press Enter.");
        wrefresh(win);

        input = wgetch(win);

        if (input == KEY_UP) {
            highlight = (highlight - 1 + numItems) % numItems;
        } else if (input == KEY_DOWN) {
            highlight = (highlight + 1) % numItems;
        } 
        else if (input == '1') highlight = 0;
        else if (input == '2') highlight = 1;
        else if (input == '3') highlight = 2;
        else if (input == '4') highlight = 3;

        else if (input == 10) { // Enter key
            choice = highlight + 1;
            curs_set(1);
            
            if (choice == 1) { // Login
                auth_header(win);
                mvwprintw(win, 6, 3, "Username: ");
                wrefresh(win);
                wgetnstr(win, uname, 30);
                mvwprintw(win, 7, 3, "Password: ");
                wrefresh(win);
                wgetnstr(win, pass, 30);
                curs_set(0);             
                screenChecking(win,"Authenticating...",1);      
                if (Auth::login(uname, pass)) {
                    menu(uname);
                    wrefresh(win);
                    wgetch(win);
                } else {
                    wattron(win,A_BOLD | COLOR_PAIR(2));
                    bottom(win,"- Login Failed!");
                    wattroff(win,A_BOLD | COLOR_PAIR(2));
                }
            } else if (choice == 2) { // Register
                auth_header(win);
                char new_uname[30], new_pass[30];
                mvwprintw(win, 6, 3, "New Username: ");
                wgetnstr(win, new_uname, 30);
                mvwprintw(win, 7, 3, "New Password: ");
                wgetnstr(win, new_pass, 30);
                curs_set(0);
                screenChecking(win,"Authenticating...",1.5);
                if (Auth::registerUser(new_uname, new_pass)) {
                    wattron(win,A_BOLD | COLOR_PAIR(3));
                    bottom(win,"- Registration Successful!");
                    wattron(win,A_DIM);
                    mvwprintw(win,21,29,"(Constructor [%s])",new_uname);
                    wattroff(win,A_BOLD | COLOR_PAIR(3) | A_DIM);
                } else {
                    wattron(win,A_BOLD | COLOR_PAIR(2));
                    bottom(win,"- Registration Failed!");
                    wattroff(win,A_BOLD | COLOR_PAIR(2));
                }
                wrefresh(win);
            } else if (choice == 3) { // Forgot Password
                auth_header(win);
                char uname[30];
                mvwprintw(win, 6, 3, "Enter Username: ");
                wgetnstr(win, uname, 30);
                curs_set(0);
                screenChecking(win,"Authenticating...",1);
                string recovered = Auth::recoverPassword(uname);
                wattron(win,A_DIM);
                mvwprintw(win, 8, 25, "Recovered Password: %s", recovered.c_str());
                wattroff(win,A_DIM);
                wrefresh(win);
                wgetch(win);
            } else if (choice == 4) {
                break;
            }
        }
    }
    screenLoading(win,"Closing...",2);
    delwin(win);
    endwin();
}

void auth_header(WINDOW* win){
    clearbody(win);
    wattron(win, A_BOLD | COLOR_PAIR(2));
    showCentered(win, 2, "-- Welcome to WeEGCO AUTH SYSTEM --");
    wattroff(win, A_BOLD | COLOR_PAIR(2));
    mvwhline(win, 4, 1, ACS_HLINE, 78);
    wrefresh(win);
}