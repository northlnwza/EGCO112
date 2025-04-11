#ifndef USERLIST_H
#define USERLIST_H

#include "User.h"

class UserList {
private:
    User* head;
    int currentID;

public:
    UserList();
    ~UserList();

    void insertUser(const std::string& username, const std::string& password);
    bool verifyUser(const std::string& username, const std::string& password);
    bool exists(const std::string& username);
    std::string getPassword(const std::string& username);
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);
    void deposit(int id, float amount);
    bool withdraw(int id, float amount);
    bool transfer(int fromID, int toID, float amount);
    User* findByID(int id);
    int getID(const std::string& username);



};

#endif