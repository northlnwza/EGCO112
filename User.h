#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User;
class Teacher;
class Student;

class User {
protected:
    string Name;
public:
    string username;
    string password;
    int studentID;
    User* next;

    User(string uname, string pwd, int id);
};



class Teacher:public User {
    string course[3] = {"-","-","-"};
    string faculty="-";
public:
    
    Teacher(string uname, string pwd, int id):User(uname,pwd,id) {};
    void editgpa(int id,float newgpa);
};



class Student:public User {
    float studentGPA=0;
    string course[5] = {"-","-","-","-","-"};
    string major="-";
public:

    Student(string uname, string pwd, int id):User(uname,pwd,id) {};
    friend void Teacher::editgpa(int id,float newgpa);
};



#endif
