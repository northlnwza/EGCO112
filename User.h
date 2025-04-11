#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    std::string username;
    std::string password;
    int studentID;
    float balance; 
    User* next;

    User(std::string uname, std::string pwd, int id);
};

#endif
