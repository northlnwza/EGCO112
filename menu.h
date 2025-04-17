#ifndef MENU_CPP
#define MENU_CPP

#include "User.h"
#include "UI_tools.h"
#include "Timetable.h"
#include "Auth.h"
#include <ncurses.h>
#include <string>
using namespace std;

void Timetable(WINDOW*, User *& u);

void menu(const string & username){

    User    *u;
    u = Auth::getData(username);

    initscr();                    // Start ncurses
    cbreak();                     // Line buffering disabled
    noecho();                     // Don't echo input
    keypad(stdscr, TRUE);         // Enable special keys
    //mousemask(ALL_MOUSE_EVENTS, NULL); // Enable all mouse events
    curs_set(0);                  // Hide the cursor

    start_color();
    use_default_colors();

    int win_height = 24, win_width = 80;
    int starty = (LINES - win_height) / 2; 
    int startx = (COLS - win_width) / 2;

    WINDOW* win = newwin(win_height, win_width, starty, startx);
    box(win, 0, 0); // Draw border
    keypad(win, TRUE);
    nodelay(win, FALSE);

    const char* menuItems[] = {
        "Classroom Time Table",
        "Add / Withdraw Courses",
        "GPA",
        "Weather",
        "Log Out"
    };
    int numItems = sizeof(menuItems) / sizeof(menuItems[0]);
    int highlight = 0; // current selected item
    int input;
    bool running = true;
    
    screenLoading(win, "Home Loading...", 1.5);
    while (running) {
        werase(win);
        box(win, 0, 0);
        header(win, u, "MENU");
        //mvwprintw(win, 20, 4, "Input: %d", input);
    
        // Print menu items with highlight
        
        for (int i = 0; i < numItems; ++i) {
            int y = 6 + i * 2;
            wattron(win,A_BOLD);
            if (i == highlight) wattron(win, A_REVERSE);
            if (i != numItems-1) mvwprintw(win, 6 + i * 2, 4, "[%d]  %s ", i + 1, menuItems[i]);
                else {
                    wattron(win,COLOR_PAIR(1));
                    mvwprintw(win, 18, 4, "[%d]  %s ", i + 1, menuItems[i]);
                    wattroff(win,COLOR_PAIR(1));
                }
                wattroff(win, A_REVERSE | A_BOLD);
        }
        wrefresh(win);
    
        input = wgetch(win);
    
        // Navigation
        /*if (input == ERR) { // No input
            napms(100); 
            continue;
        }*/
        if (input == KEY_UP) {
            highlight = (highlight - 1 + numItems) % numItems;
        } else if (input == KEY_DOWN) {
            highlight = (highlight + 1) % numItems;
        } 
        else if (input == '1') highlight = 0;
        else if (input == '2') highlight = 1;
        else if (input == '3') highlight = 2;
        else if (input == '4') highlight = 3;
        else if (input == '5') highlight = 4;

        else if (input == 10) { // Enter
            switch (highlight) {
                case 0:
                    Timetable(win, u);
                    screenLoading(win, "Home Loading...", 1.5);
                    break;
                case 1:
                    // Add / Withdraw function
                    break;
                case 2:
                    // GPA function
                    break;
                case 3:
                    // Weather function
                    break;
                case 4:
                    running = false; // Log out
                    break;
            }
            input=0;
        }
    }

    screenLoading(win,"Logging out...",2);
    delete u;
}

void Timetable(WINDOW* win, User *& u){
    werase(win);
    box(win, 0, 0);
    screenLoading(win,"Timetable Loading...",1);
    header(win,u,"MENU >> TIMETABLE");
    clearbody(win);
    initTimetable();
    loadCoursesFromFile("course.txt");
    drawTimetable(win);
    wrefresh(win);

    int ch;
    while (true) {
        ch = wgetch(win);
        if (ch == 'm' || ch == 'M') {
            break;
        }
    }
}



#endif