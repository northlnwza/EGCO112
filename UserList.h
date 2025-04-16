#ifndef USERLIST_H
#define USERLIST_H

#include "User.h"

using namespace std;

class UserList {
private:
    User* head;
    int currentID;

public:
    UserList();
    ~UserList();

    void insertUser(const string& username, const string& password, Role role);
    bool verifyUser(const string& username, const string& password);
    bool exists(const string& username);
    string getPassword(const string& username);
    void loadFromFile(const string& filename);
    void saveToFile(const string& filename);
    User* findByID(int id);
    int getID(const string& username);
};

void makedir(const string & username, string & password, int id, Role role, float balance);
const char * roleToString(Role r);
#endif
