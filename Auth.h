#ifndef AUTH_H
#define AUTH_H

#include "User.h"

class Auth : public User {
public:
    Auth(string uname = "", string pass = "", string sid = "");

    bool login(string uname, string pass);
    bool registerUser();
    bool resetPassword(string uname, string newPass);
};

#endif
