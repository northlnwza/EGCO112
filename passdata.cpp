#include "passdata.h"



void    testpass(const string & username, WINDOW*& win)
{
    User    *loggedInUser;

    loggedInUser = Auth::getData(username);
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 2, 2, (loggedInUser->username).c_str());
    mvwprintw(win, 3, 2, (loggedInUser->password).c_str());
    mvwprintw(win, 4, 2, to_string(loggedInUser->id).c_str());
    mvwprintw(win, 5, 2, roleToString(loggedInUser->role));
    wrefresh(win);
    /*
    cout << loggedInUser->username << endl;
    cout << loggedInUser->password << endl;
    cout << loggedInUser->id << endl;
    cout << loggedInUser->role << endl;
    */
    delete loggedInUser;
}
