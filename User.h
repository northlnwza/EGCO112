#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

enum Role { STUDENT, STAFF };
class User 
{
public:
    string username;
    string password;
    int id;
    float balance;
    Role role;
    User* next;

    User(string uname=0, string pwd=0, int id=0, Role r=STAFF);
};

class Staff : public User
{
    public:
        Staff(string uname=0, string pwd=0, int id=0);
};

class Student : public User
{
    public:
        Student(string uname=0, string pwd=0, int id=0);
};

#endif
