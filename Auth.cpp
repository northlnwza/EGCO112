#include "Auth.h"
#include "UserList.h"

bool Auth::login(const std::string& username, const std::string& password) {
    UserList list;
    list.loadFromFile("users.txt");
    return list.verifyUser(username, password);
}

bool Auth::registerUser(const std::string& username, const std::string& password) {
    UserList list;
    list.loadFromFile("users.txt");
    if (list.exists(username)) return false;
    list.insertUser(username, password);
    list.saveToFile("users.txt");
    return true;
}

std::string Auth::recoverPassword(const std::string& username) {
    UserList list;
    list.loadFromFile("users.txt");
    return list.getPassword(username);
}
