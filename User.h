#ifndef USER_H
#define USER_H

#include <string>
//#include "UserList.h"
using namespace std;

class UserList;

enum Role { STUDENT, STAFF };

class User {
public:
    string username;
    string password;
    int studentID;
    float balance;
    Role role;
    User* next;

    User (string uname,string pwd, int id, Role r);
    virtual ~User() {}

    virtual void showMenu(UserList& userList) = 0;
    virtual void shop() = 0;
};

#endif
