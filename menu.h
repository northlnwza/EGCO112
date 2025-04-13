#ifndef MENU_CPP
#define MENU_CPP

#include "User.h"
#include "UI_tools.h"
#include "Timetable.h"
#include "Auth.h"
#include <ncurses.h>
#include <string>
using namespace std;

void Timetable(WINDOW*);

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

    if (!has_colors()) {
        endwin();
        printf("Your terminal doesn't support color!\n");
        exit(0);
    }
    else setup_color();

    int win_height = 24, win_width = 80;
    int starty = (LINES - win_height) / 2; 
    int startx = (COLS - win_width) / 2;

    WINDOW* win = newwin(win_height, win_width, starty, startx);
    box(win, 0, 0); // Draw border

    char choice='m';
    do {
        if (choice=='m'){
        werase(win);
        box(win,0,0);
        screenLoading(win,"Starting...",1.5);
        //header(win,"Ten","MENU");
        header(win,u->username,"MENU");
        wattron(win,A_BOLD);
        mvwprintw(win,6,3,"[1]  Classroom Time Table");
        mvwprintw(win,8,3,"[2]  Add / Withdraw Courses");
        mvwprintw(win,10,3,"[3]  Grade");
        mvwprintw(win,12,3,"[4]  Weather");
        wattron(win,COLOR_PAIR(2));
        mvwprintw(win,20,3,"[9]  Log out");
        wattroff(win,A_BOLD | COLOR_PAIR(2));
        wrefresh(win);
        }

        choice = wgetch(win);

        switch (choice){
            case 'm':
                break;
            case '1':
                Timetable(win);
                break;
        }
    }while (choice != '9');

    screenLoading(win,"Closing...",2);
    delwin(win);
    endwin();
    delete u;
}

void Timetable(WINDOW* win){
    werase(win);
    box(win, 0, 0);
    menuLoading(win,"Timetable",1);
    header(win,"Ten","TIMETABLE");
    clearbody(win);
    initTimetable();
    loadCoursesFromFile("course.txt");
    drawTimetable(win);
    wrefresh(win);
}



#endif