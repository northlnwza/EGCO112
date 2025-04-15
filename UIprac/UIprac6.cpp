#include <ncurses.h>
#include <cstring>
#include <cctype>
using namespace std;

void animatedBannerLogin(WINDOW* win) {
    const char* banner = ">>> Welcome to WeEGCO AUTH SYSTEM <<<";
    int banner_len = strlen(banner);
    int max_x = 80; // your terminal width
    int x = 0;
    int direction = 1; // 1 = right, -1 = left

    char uname[30], pass[30];
    int ch;

    nodelay(win, TRUE); // non-blocking input
    keypad(win, TRUE);

    int inputStep = 0; // 0 = ask for username, 1 = password, 2 = done
    uname[0] = '\0';
    pass[0] = '\0';
    int uname_len = 0, pass_len = 0;

    while (1) {
        werase(win);
        box(win, 0, 0);

        // Move banner
        mvwprintw(win, 1, x, "%s", banner);
        x += direction;
        if (x <= 0 || x + banner_len >= max_x - 2)
            direction *= -1;

        // Ask for login info
        mvwprintw(win, 4, 3, "Username: %s", uname);
        mvwprintw(win, 5, 3, "Password: %s", pass); // can hide chars if you want
        mvwprintw(win, 7, 3, "Press Enter to continue...");

        wrefresh(win);

        // Handle input
        ch = wgetch(win);
        if (ch == ERR) {
            // No input, continue animation
            napms(50); // small delay for animation
            continue;
        }

        if (ch == '\n') {
            if (inputStep == 0) inputStep = 1;
            else if (inputStep == 1) break;
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            if (inputStep == 0 && uname_len > 0) {
                uname[--uname_len] = '\0';
            } else if (inputStep == 1 && pass_len > 0) {
                pass[--pass_len] = '\0';
            }
        } else if (isprint(ch)) {
            if (inputStep == 0 && uname_len < 29) {
                uname[uname_len++] = ch;
                uname[uname_len] = '\0';
            } else if (inputStep == 1 && pass_len < 29) {
                pass[pass_len++] = ch;
                pass[pass_len] = '\0';
            }
        }

        napms(30); // animation speed
    }

    nodelay(win, FALSE); // restore blocking input
}

int main(){
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int win_height = 10, win_width = 40;
    int starty = (LINES - win_height) / 2;
    int startx = (COLS - win_width) / 2;

    WINDOW* win = newwin(win_height, win_width, starty, startx);
    box(win, 0, 0);
    animatedBannerLogin(win);
    /*
    int i=1;
    while(1){
        mvwprintw(win,4,i%win_width,"Hello");
        napms(500);
        wrefresh(win);
        i++;

    }*/

    wrefresh(win);
    wgetch(win);
    delwin(win);
    endwin();
}

