#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <string>
#include <ncurses.h>
#include <unistd.h>
using namespace std;

void showCentered(WINDOW*,int,const string&);
void screenLoading(WINDOW*);
void header(WINDOW*);

void setup_color(); //for setup

class Button{
    
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
    

void screenLoading(WINDOW* win){
        int i;
        string load=" ";

        showCentered(win,10,"Loading...");
        wattron(win,COLOR_PAIR(9));
        for (i=0;i<21;i++){
            mvwprintw(win,12,29,load.c_str());
            usleep(80000);
            wrefresh(win);
            load+=" ";
        }
        wattroff(win,COLOR_PAIR(9));
        werase(win);
        box(win,0,0);
    }


void header(WINDOW* win,const string& text){
    int i;
    wattron(win,A_BOLD);
    showCentered(win,1,"-- WeEGCO Menu System --");
    wattron(win,COLOR_PAIR(5));
    showCentered(win,2,"Welcome Student : "+text);
    wattroff(win,COLOR_PAIR(5) | A_BOLD);
    mvwhline(win,4, 1, '-', 78);
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
}

#endif