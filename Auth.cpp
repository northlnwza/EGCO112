#include "Auth.h"
#include "UserList.h"
#include "passdata.h"

bool Auth::login(const string& username, const string& password) {
    UserList list;
    bool    status;

    list.loadFromFile("users.txt");
    return list.verifyUser(username, password);
}

bool Auth::registerUser(const string& username, const string& password) {
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
    return new User(curr->username, curr->password, curr->id);
}

string Auth::recoverPassword(const string & username) {
    UserList list;
    list.loadFromFile("users.txt");
    return list.getPassword(username);
}
