#ifndef AUTH_H
#define AUTH_H

#include <string>

class Auth {
public:
    static bool login(const std::string& username, const std::string& password);
    static bool registerUser(const std::string& username, const std::string& password);
    static std::string recoverPassword(const std::string& username);
};

#endif
