#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
public:
    string username;
    string password;
    int id;
    User* next;

    User(string uname=0, string pwd=0, int id=0);
};

#endif
