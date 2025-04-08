#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    string username;
    string password;
    string studentID;

public:
    User(string uname = "", string pass = "", string sid = "");

    virtual void display();
    string getUsername() const;
    string getPassword() const;
    string getStudentID() const;

    void setPassword(string newPass);
    void setStudentID(string sid);
};

#endif
