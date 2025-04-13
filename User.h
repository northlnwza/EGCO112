#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    std::string username;
    std::string password;
    int id;
    User* next;

    User(std::string uname=0, std::string pwd=0, int id=0);
};

#endif
