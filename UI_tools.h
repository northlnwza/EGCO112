#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <string>
#include <ncurses.h>
#include <unistd.h>
#include "Auth.h"
#include "User.h"
using namespace std;

void showCentered(WINDOW*,int,const string&);
void screenLoading(WINDOW*,const string&,int);
void screenChecking(WINDOW*,const string&,int);
void header(WINDOW*, User *& u);
void bottom(WINDOW*,const string&);
void clearbody(WINDOW*);

void setup_color(); //for setup

class Button{ //for mouse
    
    private:
        WINDOW* win;
        int y, x;
        string label;

    public:
        Button(WINDOW* win, int y, int x, const string& label): win(win), y(y), x(x), label(label) {}
    
        void draw(bool highlighted = false) {               //ถ้าประกาศboxก่อนหน้าwinที่ส่งมา
            if (highlighted) wattron(win, A_REVERSE);   
            mvwprintw(win, y, x, "[ %s ]", label.c_str());
            if (highlighted) wattroff(win, A_REVERSE);
            wrefresh(win);
        }
    
        bool isClicked(int mouseY, int mouseX) {
            int width = label.length() + 4;                 // [ label ]
            return (mouseY == y && mouseX >= x && mouseX <= x + width - 1);
        }
    
        string getLabel() { return label; }
    
    };


void showCentered(WINDOW* win, int y, const string& text) {
        int x = (getmaxx(win) - text.length()) / 2;
        mvwprintw(win, y, x, "%s", text.c_str());
    }

    void showSpinner(WINDOW* win, const char* message, int y, int x, int duration_ms) {
        const char spinner[] = {'|', '/', '-', '\\'};
        int spinnerLen = sizeof(spinner);
        int delay = 100; // ms per frame
        int cycles = duration_ms / delay;
    
        wattron(win,A_BOLD);
        for (int i = 0; i < cycles; ++i) {
            mvwprintw(win, y, x, "%c %s %c", spinner[i % spinnerLen], message, spinner[i % spinnerLen]);
            wrefresh(win);
            napms(delay);
        }
        wattroff(win,A_BOLD);
    }
    

void screenLoading(WINDOW* win,const string& text ,int duration){
        int i;
        string load=" ";

        werase(win);
        box(win,0,0);
        wattron(win,A_BOLD);
        showCentered(win,10,text);
        wattron(win,COLOR_PAIR(9));
        for (i=0;i<21;i++){
            mvwprintw(win,12,29,load.c_str());
            usleep(duration*50000);
            wrefresh(win);
            load+=" ";
        }
        wattroff(win,COLOR_PAIR(9) | A_BOLD);
        werase(win);
        box(win,0,0);
        wrefresh(win);
    }

void screenChecking(WINDOW* win,const string& text ,int duration){
        int i;
        string load=" ";

        werase(win);
        box(win,0,0);
        wattron(win,A_BOLD | COLOR_PAIR(4));
        showCentered(win,10,text);
        wattron(win,COLOR_PAIR(10));
        for (i=0;i<21;i++){
            mvwprintw(win,12,29,load.c_str());
            usleep(duration*50000);
            wrefresh(win);
            load+=" ";
        }
        sleep(1);
        wattroff(win,COLOR_PAIR(10) | A_BOLD | COLOR_PAIR(4));
        werase(win);
        box(win,0,0);
        wrefresh(win);
    }


void header(WINDOW* win,User* & u,const string& menu){
    //User    *u;
    //u = Auth::getData(uname);
    wattron(win,A_BOLD);
    showCentered(win,1,"-- WeEGCO Menu System --");
    wattron(win,COLOR_PAIR(5));
    showCentered(win,2,"Welcome Student : "+u->username+ "     ID : "+to_string(u->id));
    wattroff(win,COLOR_PAIR(5));
    showCentered(win,3,"* "+menu+" *");
    wattroff(win, A_BOLD);
    mvwhline(win, 4, 1, ACS_HLINE, 78);
    wrefresh(win);
    //delete u;
}

void bottom(WINDOW* win,const string& text){
    mvwhline(win,20,1,ACS_HLINE, 78);
    //mvwhline(win,20,0,ACS_LTEE,1);
    //mvwhline(win,20,79,ACS_RTEE,1);
    mvwhline(win,22,1,ACS_HLINE, 78);
    //mvwhline(win,22,0,ACS_LTEE,1);   
    //mvwhline(win,22,79,ACS_RTEE,1);

    mvwprintw(win,21,3,text.c_str());
    wrefresh(win);
}

void clearbody(WINDOW* win){
    int i;
    for (i=5;i<25;i++)
        mvwprintw(win,i,0,"\n");
    wrefresh(win);
    box(win,0,0);
}


void setup_color(){
    //Font
    init_pair(1, COLOR_BLACK, -1);   // Default tex
    init_pair(2, COLOR_RED, -1);     // Errors
    init_pair(3, COLOR_GREEN, -1);   // Success / active
    init_pair(4, COLOR_YELLOW, -1);  // Warnings
    init_pair(5, COLOR_CYAN, -1);    // Prompts or info
    init_pair(6, COLOR_WHITE, -1);   // Highlighted text (menu selection)
    //Background
    init_pair(9, -1, COLOR_GREEN);   // Highlighted
    init_pair(10, -1,COLOR_YELLOW);
    init_pair(11, -1,COLOR_BLACK);
}

#endif