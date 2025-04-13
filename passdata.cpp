
#include "passdata.h"
#include "UserList.h"

#include "Auth.h"

void    testpass(const string & username)
{
    User    *loggedInUser;

    loggedInUser = Auth::getData(username);
    cout << loggedInUser->username << endl;
    cout << loggedInUser->password << endl;
    cout << loggedInUser->id << endl;

    delete loggedInUser;
}
