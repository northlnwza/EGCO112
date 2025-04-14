#ifndef STAFF_H
#define STAFF_H

#include "User.h"

class Staff : public User {
public:
    Staff(std::string uname, std::string pwd, int id);
    void showMenu() override;
    void shop() override;
};

#endif
