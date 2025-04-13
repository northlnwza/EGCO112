#ifndef TIMETABLE_H
#define TIMETABLE_H

#include "UI_tools.h"

#include <ncurses.h>
#include <cstring>
#include <iostream> //(input-output)stream
#include <fstream> //(file)stream


const int NUM_DAYS = 5;
const int NUM_HOURS = 10;
const int COLUMN_WIDTH = 12;

char timetable[NUM_HOURS][NUM_DAYS][11]; // 10 chars + null terminator

const char* days[NUM_DAYS] = { "Mon", "Tue", "Wed", "Thu", "Fri" };

void initTimetable();
int getDayIndex(const char* day);
void addCourseToTimetable(const char* course, const char* day, int start_hour, int duration);
void loadCoursesFromFile(const char* filename);
void drawTimetable(WINDOW* win);

void initTimetable() {
    int i,j;
    for (i = 0; i < NUM_HOURS; ++i)
        for (j = 0; j < NUM_DAYS; ++j)
            strcpy(timetable[i][j], "");
}

int getDayIndex(const char* day) {
    for (int i = 0; i < NUM_DAYS; ++i)
        if (strcmp(days[i], day) == 0)
            return i;
    return -1; // not found
}

void addCourseToTimetable(const char* course, const char* day, int start_hour, int duration) {
    int day_col = getDayIndex(day);
    if (day_col == -1) return;

    int start_index = start_hour - 8;
    for (int i = 0; i < duration; ++i) {
        if (start_index + i >= 0 && start_index + i < NUM_HOURS)
            strncpy(timetable[start_index + i][day_col], course, 10);
    }
}

void loadCoursesFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Failed to open course.txt\n";
        return;
    }

    char course[11], day[4];
    int start_hour, duration;

    while (file >> course >> day >> start_hour >> duration) {
        addCourseToTimetable(course, day, start_hour, duration);
    }

    file.close();
}

void drawTimetable(WINDOW* win) {
    int start_y = 5;
    int start_x = 3;

    // ┌ Top Border
    mvwaddch(win, start_y, start_x, ACS_ULCORNER);
    for (int i = 0; i <= 5; ++i) {
        whline(win, ACS_HLINE, COLUMN_WIDTH);
        mvwaddch(win, start_y, start_x + (i + 1) * COLUMN_WIDTH, ACS_TTEE);
    }
    mvwaddch(win, start_y, start_x + 6 * COLUMN_WIDTH, ACS_URCORNER);

    // Day Labels (row 1 under border)
    mvwaddch(win, start_y + 1, start_x, ACS_VLINE);
    wattron(win,A_BOLD | COLOR_PAIR(4));
    mvwprintw(win, start_y + 1, start_x + 1, "   Time ");
    wattroff(win,A_BOLD | COLOR_PAIR(4));
    for (int i = 0; i < 5; ++i) {
        mvwaddch(win, start_y + 1, start_x + (i + 1) * COLUMN_WIDTH, ACS_VLINE);
        wattron(win,A_BOLD);
        mvwprintw(win, start_y + 1, start_x + (i + 1) * COLUMN_WIDTH + 1, "    %-6s", days[i]);
        wattroff(win,A_BOLD);
    }
    mvwaddch(win, start_y + 1, start_x + 6 * COLUMN_WIDTH, ACS_VLINE);

    // ├ Header Separator (row 2 under labels)
    mvwaddch(win, start_y + 2, start_x, ACS_LTEE);
    for (int i = 0; i <= 5; ++i) {
        whline(win, ACS_HLINE, COLUMN_WIDTH);
        mvwaddch(win, start_y + 2, start_x + (i + 1) * COLUMN_WIDTH, ACS_PLUS);
    }
    mvwaddch(win, start_y + 2, start_x + 6 * COLUMN_WIDTH, ACS_RTEE);

    // │ Content Rows: 08:00 to 17:00
    for (int row = 0; row < NUM_HOURS; ++row) {
        int y = start_y + 3 + row;
        int hour = 8 + row;

        // Left border
        mvwaddch(win, y, start_x, ACS_VLINE);

        // Time label
        wattron(win,A_BOLD);
        mvwprintw(win, y, start_x + 1, " %02d:00 ", hour);
        wattroff(win,A_BOLD);

        // Each day cell
        for (int col = 0; col < NUM_DAYS; ++col) {
            // Vertical line separator between days
            mvwaddch(win, y, start_x + (col + 1) * COLUMN_WIDTH, ACS_VLINE);

            // Course content
            mvwprintw(win, y, start_x + (col + 1) * COLUMN_WIDTH + 1, "  %-10s", timetable[row][col]);
        }

        // Right edge line
        mvwaddch(win, y, start_x + 6 * COLUMN_WIDTH, ACS_VLINE);
    }

    // └ Bottom Border
    int bottom_y = start_y + 3 + NUM_HOURS;
    mvwaddch(win, bottom_y, start_x, ACS_LLCORNER);
    for (int i = 0; i <= 5; ++i) {
        whline(win, ACS_HLINE, COLUMN_WIDTH);
        mvwaddch(win, bottom_y, start_x + (i + 1) * COLUMN_WIDTH, ACS_BTEE);
    }
    mvwaddch(win, bottom_y, start_x + 6 * COLUMN_WIDTH, ACS_LRCORNER);

    // Footer Hint
    showCentered(win,22,"[ Press 'm' to go menu ]");

    wrefresh(win);
}


#endif