#include "User.h"

User::User(std::string uname, std::string pwd, int id, Role r)
    : username(uname), password(pwd), studentID(id), balance(0.0), role(r), next(nullptr) {}
