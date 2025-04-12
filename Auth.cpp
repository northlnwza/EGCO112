#include "Auth.h"
#include "UserList.h"
#include "passdata.h"

bool Auth::login(const std::string& username, const std::string& password) {
    UserList list;
    bool    status;
    list.loadFromFile("users.txt");
    status = list.verifyUser(username, password);
    /*
    if (status)
        testpass(list, username);
    */
    return status;
}

bool Auth::registerUser(const std::string& username, const std::string& password) {
    UserList list;
    list.loadFromFile("users.txt");
    if (list.exists(username)) return false;
    list.insertUser(username, password);
    list.saveToFile("users.txt");
    return true;
}

User* Auth::getData(const string & username) // in case after login
{
    UserList list;
    User* curr;

    list.loadFromFile("users.txt");
    curr = list.findByID(list.getID(username));
    return new User(curr->username, curr->password, curr->studentID);
}

std::string Auth::recoverPassword(const std::string& username) {
    UserList list;
    list.loadFromFile("users.txt");
    return list.getPassword(username);
}
