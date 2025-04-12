
#include "passdata.h"
#include "UserList.h"
#include "Auth.h"

/*
User getData(const string &username)
{
    User u;
    string path = "userdata/" + username + "/data.txt";
    ifstream file(path);
    string line;


    if (!file) {
        std::cerr << "Data file not found for user: " << username << std::endl;
        return u;
    }
    while (getline(file, line)) 
    {
        if (line.rfind("Username:", 0) == 0) {
            u.username = line.substr(9);// from index 9 onward
        } else if (line.rfind("ID:", 0) == 0) 
        {
            u.studentID = stoi(line.substr(3));
        } else if (line.rfind("Password:", 0) == 0)
        {
            u.password = line.substr(9);
        }
    }
    file.close();
    return u;
}
*/

void    testpass(const string & username)
{
    User    *loggedInUser;

    loggedInUser = Auth::getData(username);
    cout << loggedInUser->username << endl;
    cout << loggedInUser->password << endl;
    cout << loggedInUser->studentID << endl;

    delete loggedInUser;
}
