#ifndef USERLIST_H
#define USERLIST_H

#include "User.h"

class UserNode {
public:
    User data;
    UserNode* next;

    UserNode(User u);
};

class UserList {
private:
    UserNode* head;

public:
    UserList();
    void addUser(User user);
    void displayUsers();
};

#endif
