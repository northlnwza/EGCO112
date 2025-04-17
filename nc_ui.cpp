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
void inputPopup(WINDOW*);
void Interface(WINDOW*);

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
    nodelay(win, TRUE);
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
        noecho();
        // Draw the menu
        auth_header(win);
        bottom(win,"-");

        wattron(win, A_BOLD);
        for (int i = 0; i < numItems; ++i) {
            if (i == highlight) wattron(win, A_REVERSE);
            if (i != numItems-1) mvwprintw(win, 6 + i * 2, 4, "[%d]  %s ", i + 1, menuItems[i]);
                else {
                    wattron(win,COLOR_PAIR(1));
                    mvwprintw(win, 18, 4, "[%d]  %s ", i + 1, menuItems[i]);
                    wattroff(win,COLOR_PAIR(1));
                }
            if (i == highlight) wattroff(win, A_REVERSE);
        }
        wattroff(win, A_BOLD);
        //mvwprintw(win, 14, 3, "Use ↑ ↓ arrows and press Enter.");
        
        input = wgetch(win);

        if (input == ERR) { // No input
            static int j=15,move=1;
            wattron(win,COLOR_PAIR(5) | A_BOLD);
            wmove(win,2,1);
            wclrtoeol(win);
            mvwprintw(win,2,j," -- Welcome to WeEGCO AUTH SYSTEM -- ");
            wattroff(win,COLOR_PAIR(5) | A_BOLD);
            box(win,0,0);
            wrefresh(win);
            if (j>40) move=0;
            else if (move==0 && j==2) move=1;
            if (move==1) j++;
            else j--;
            napms(200);
            continue;
        }else if (input == KEY_UP) {
            highlight = (highlight - 1 + numItems) % numItems;
        }else if (input == KEY_DOWN) {
            highlight = (highlight + 1) % numItems;
        } 
        else if (input == '1') highlight = 0;
        else if (input == '2') highlight = 1;
        else if (input == '3') highlight = 2;
        else if (input == '4') highlight = 3;

        else if (input == 10) { // Enter key
            choice = highlight + 1;
            echo();
            nodelay(win, FALSE);
            auth_header(win);
            curs_set(1);
            
            if (choice == 1) { // Login

                inputPopup(win);
                showCentered(win, 6,"Login System.",3,1);
                mvwprintw(win, 10, 24, "Username: ");
                wgetnstr(win, uname, 30);
                mvwprintw(win, 12, 24, "Password: ");
                wgetnstr(win, pass, 30);

                curs_set(0);             
                screenChecking(win,"Authenticating...",1);      
                if (Auth::login(uname, pass)) {
                    wattron(win,COLOR_PAIR(3));
                    showSpinner(win,"Login Successful",11,30,1000);
                    wattroff(win,COLOR_PAIR(3));
                    menu(uname);
                    wrefresh(win);
                } else {
                    wattron(win, COLOR_PAIR(2));
                    bottom(win,"- Login Failed!");
                    wattron(win,A_DIM);
                    mvwprintw(win,21,19,"(Username or Password is incorrect.)");
                    wattroff(win,A_BOLD | COLOR_PAIR(2) | A_DIM);
                }
            } else if (choice == 2) { // Register

                inputPopup(win);
                char new_uname[30], new_pass[30];
                mvwprintw(win, 10, 24, "New Username: ");
                wgetnstr(win, new_uname, 30);
                mvwprintw(win, 12, 24, "New Password: ");
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
                noecho();
                curs_set(0);
                break;
            }
        }
        input=ERR;
    }
    screenLoading(win,"Closing...",2);
    delwin(win);
    endwin();
}

void auth_header(WINDOW* win){
    clearbody(win);
    wmove(win,2,1);
    wclrtoeol(win);
    box(win,0,0);
    wattron(win,COLOR_PAIR(5) | A_BOLD);
    showCentered(win,2," -- Welcome to WeEGCO AUTH SYSTEM -- ");
    wattroff(win,COLOR_PAIR(5) | A_BOLD);
    mvwhline(win, 4, 1, ACS_HLINE, 78);
}

void inputPopup(WINDOW* win){
    auth_header(win);
    clearbody(win);
    int boxTop = 8;
    int boxLeft = 20;
    int boxWidth = 40;
    int boxHeight = 6;

    // Draw the box using ACS characters
    // Corners
    mvwaddch(win, boxTop, boxLeft, ACS_ULCORNER);
    mvwaddch(win, boxTop, boxLeft + boxWidth, ACS_URCORNER);
    mvwaddch(win, boxTop + boxHeight, boxLeft, ACS_LLCORNER);
    mvwaddch(win, boxTop + boxHeight, boxLeft + boxWidth, ACS_LRCORNER);

    // Top and Bottom borders
    mvwhline(win, boxTop, boxLeft + 1, ACS_HLINE, boxWidth - 1);
    mvwhline(win, boxTop + boxHeight, boxLeft + 1, ACS_HLINE, boxWidth - 1);

    // Left and Right borders
    mvwvline(win, boxTop + 1, boxLeft, ACS_VLINE, boxHeight - 1);
    mvwvline(win, boxTop + 1, boxLeft + boxWidth, ACS_VLINE, boxHeight - 1);

    bottom(win,"- Input Username and Password                ");
}

void Interface(WINDOW*){

}