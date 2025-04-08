#include "Auth.h"
#include <fstream>

Auth::Auth(string uname, string pass, string sid)
    : User(uname, pass, sid) {}

bool Auth::login(string uname, string pass) {
    ifstream file("users.txt");
    string u, p, sid;
    while (file >> u >> p >> sid) {
        if (u == uname && p == pass)
            return true;
    }
    return false;
}

bool Auth::registerUser() {
    ifstream file("users.txt");
    string u, p, sid;
    while (file >> u >> p >> sid) {
        if (u == username)
            return false;
    }

    ofstream outFile("users.txt", ios::app);
    outFile << username << " " << password << " " << studentID << endl;
    return true;
}

bool Auth::resetPassword(string uname, string newPass) {
    ifstream file("users.txt");
    ofstream temp("temp.txt");
    string u, p, sid;
    bool found = false;

    while (file >> u >> p >> sid) {
        if (u == uname) {
            temp << u << " " << newPass << " " << sid << endl;
            found = true;
        } else {
            temp << u << " " << p << " " << sid << endl;
        }
    }

    file.close();
    temp.close();
    remove("users.txt");
    rename("temp.txt", "users.txt");

    return found;
}
