#include <ncurses.h>
#include <unistd.h> // For sleep()

void draw_button(WINDOW* win, int y, int x, const char* label) {
    mvwprintw(win, y, x, "[ %s ]", label);
    wrefresh(win);
}

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    printf("\033[?1003h\n");

    int win_height = 10, win_width = 40;
    int starty = (LINES - win_height) / 2;
    int startx = (COLS - win_width) / 2;

    // Create centered popup window
    WINDOW* win = newwin(win_height, win_width, starty, startx);
    box(win, 0, 0);
    mvwprintw(win, 1, 2, "Click a button below:");
    wrefresh(win);

    // Draw buttons inside window
    int btn_ok_x = 10;
    int btn_cancel_x = 24;
    int btn_y = 5;
    draw_button(win, btn_y, btn_ok_x, "OK");
    draw_button(win, btn_y, btn_cancel_x, "Cancel");

    // Wait for mouse click
    MEVENT event;
    int ch;
    while ((ch = wgetch(win)) != 'q') {
        if (ch == KEY_MOUSE && getmouse(&event) == OK) {
            int click_y = event.y ;
            int click_x = event.x ;

            // Check click position inside window
            if (click_y == btn_y) {
                if (click_x >= btn_ok_x && click_x <= btn_ok_x + 5) {
                    mvwprintw(win, 7, 2, "You clicked OK!     ");
                    break;
                }
                if (click_x >= btn_cancel_x && click_x <= btn_cancel_x + 9) {
                    mvwprintw(win, 7, 2, "You clicked Cancel! ");
                    break;
                }
            }
        }
    }

    wrefresh(win);
    sleep(1); // Pause to see the result
    wgetch(win);
    delwin(win);
    endwin();
    return 0;
}
