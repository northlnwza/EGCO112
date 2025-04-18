#include <ncurses.h>
#include <cstring>

void fadeOutWeEGCO(WINDOW* win, int yStart, int xStart, const char* ascii[], int lines) {
    for (int step = 0; step < lines; ++step) {
        // Clear one line at a time
        mvwhline(win, yStart + step, xStart, ' ', strlen(ascii[step]));
        box(win, 0, 0);
        wrefresh(win);
        napms(150); // adjust for speed
    }
}

void introWeEGCO(WINDOW* win) {
    const char* text[] = {
        " __        __         ______   ______   _____   _____   ____   ",
        " \\ \\      / /  /\\    |  ____| |  ____| |_   _| |_   _| |  _ \\  ",
        "  \\ \\ /\\ / /  /  \\   | |__    | |__      | |     | |   | |_) | ",
        "   \\ V  V /  / /\\ \\  |  __|   |  __|     | |     | |   |  _ <  ",
        "    \\_/\\_/  /_/  \\_\\ |_|      |_|        |_|     |_|   |_| \\_\\ ",
    };
    int lines = 5;
    int width = strlen(text[0]);
    int startx = (80 - width) / 2;
    int targetY = 8;

    start_color();
    init_pair(1, COLOR_CYAN, -1);
    wattron(win, A_BOLD | COLOR_PAIR(1));
    curs_set(0);

    // Drop down from top smoothly
    for (int y = -5; y <= targetY; ++y) {
        werase(win);
        box(win, 0, 0);

        for (int i = 0; i < lines; ++i) {
            int drawY = y + i;
            if (drawY >= 1 && drawY < 23)
                mvwprintw(win, drawY, startx, "%s", text[i]);
        }

        wrefresh(win);
        napms(40); // ~6 lines × 40ms = ~240ms drop
    }

    wattroff(win, A_BOLD | COLOR_PAIR(1));
    fadeOutWeEGCO(win, yStart, xStart, text, lines);
    napms(1500); // ~1.5 sec pause before starting program
}

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    WINDOW *win=newwin(24,80,5,30);

    introWeEGCO(win); // show intro splash

    endwin();
    return 0;
}