#include "User.h"
#include <iostream>
using namespace std;

User::User(string uname, string pass, string sid)
    : username(uname), password(pass), studentID(sid) {}

void User::display() {
    cout << "Username: " << username << " | Student ID: " << studentID << endl;
}

string User::getUsername() const { return username; }
string User::getPassword() const { return password; }
string User::getStudentID() const { return studentID; }

void User::setPassword(string newPass) { password = newPass; }
void User::setStudentID(string sid) { studentID = sid; }
