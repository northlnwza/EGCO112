#ifndef AUTH_H
#define AUTH_H

#include <string>
#include "User.h"
using namespace std;

class Auth {
public:
    static bool login(const string& username, const string& password);
    static bool registerUser(const string& username, const string& password, Role role);
    static string recoverPassword(const string& username);
    static User * getData(const string & username);
};
// A Class that only have method is called 'stateless'.
#endif
