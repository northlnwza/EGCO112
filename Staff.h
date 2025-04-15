#ifndef STAFF_H
#define STAFF_H

#include "User.h"
//#include "UserList.h"
using namespace std;

class UserList;

class Staff : public User {
public:
    Staff(string uname, string pwd, int id);
    //void showMenu(UserList& userList) override;
    void showMenu() ;
    //void openShopMenu(UserList& userList);
    void shop() override;
};

#endif
