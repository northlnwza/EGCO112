#ifndef BUTTON_H
#define BUTTON_H

#include <ncurses.h>
#include <string>

class Button {
public:
    Button(WINDOW* win, int y, int x, const std::string& label)
        : win(win), y(y), x(x), label(label) {}

    void draw(bool highlighted = false) {               //ถ้าประกาศboxก่อนหน้าwinที่ส่งมา
        if (highlighted) wattron(win, A_REVERSE);   
        mvwprintw(win, y, x, "[ %s ]", label.c_str());
        if (highlighted) wattroff(win, A_REVERSE);
        wrefresh(win);
    }

    bool isClicked(int mouseY, int mouseX) {
        int width = label.length() + 4; // [ label ]
        return (mouseY == y && mouseX >= x && mouseX <= x + width - 1);
    }

    std::string getLabel() { return label; }

private:
    WINDOW* win;
    int y, x;
    std::string label;
};

#endif
