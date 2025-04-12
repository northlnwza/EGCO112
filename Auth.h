#ifndef AUTH_H
#define AUTH_H

#include <string>
#include "User.h"
using namespace std;

class Auth {
public:
    static bool login(const std::string& username, const std::string& password);
    static bool registerUser(const std::string& username, const std::string& password);
    static std::string recoverPassword(const std::string& username);
    static User * getData(const string & username);
};
// A Class that only have method is called 'stateless'.
#endif
