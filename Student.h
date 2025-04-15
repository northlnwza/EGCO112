#ifndef STUDENT_H
#define STUDENT_H
#include "User.h"
#include "UserList.h"
#include "Score.h"
#include <map>
using namespace std;

class Student : public User {
private:
    map<string, Score> subjects;

public:
    Student(string uname, string pwd, int id);
    void showMenu(UserList& userList) override;
    void shop() override;
    void openShopMenu(UserList& userList);
    void enterScore();
    void showScores();
    void deleteScores();
    void saveToFile();
};

#endif

