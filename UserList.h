#ifndef USERLIST_H
#define USERLIST_H

#include "User.h"
#include "Student.h"
#include "Staff.h"
#include <string>

class UserList {
private:
    User* head;
    int currentID;

public:
    UserList();
    ~UserList();

    void insertUser(const std::string& username, const std::string& password, Role role);
    User* findByID(int id);
    int getID(const std::string& username);
    bool exists(const std::string& username);
    bool verifyUser(const std::string& username, const std::string& password);
    User* getUser(const std::string& username);

    void deposit(int id, float amount);
    bool withdraw(int id, float amount);
    bool transfer(int fromID, int toID, float amount);

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};

#endif
