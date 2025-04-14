#ifndef USER_H
#define USER_H

#include <string>

enum Role { STUDENT, STAFF };

class User {
public:
    std::string username;
    std::string password;
    int studentID;
    float balance;
    Role role;
    User* next;

    User(std::string uname, std::string pwd, int id, Role r);
    virtual ~User() {}

    virtual void showMenu() = 0;
    virtual void shop() = 0;
};

#endif
