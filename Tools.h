#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <string>
#include <ncurses.h>
using namespace std;

void showCentered(WINDOW*,int,const string&);

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

#endif