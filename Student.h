#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

class Student : public User {
public:
    Student(std::string uname, std::string pwd, int id);
    void showMenu() override;
    void shop() override;
};

#endif
