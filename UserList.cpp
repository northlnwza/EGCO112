#include "UserList.h"
#include <fstream>
#include <sstream>

User::User(std::string uname, std::string pwd, int id)
    : username(uname), password(pwd), studentID(id), next(nullptr) {}

UserList::UserList() : head(nullptr), currentID(1000) {}

UserList::~UserList() {
    User* curr = head;
    while (curr) {
        User* tmp = curr;
        curr = curr->next;
        delete tmp;
    }
}

void UserList::insertUser(const std::string& username, const std::string& password) {
    User* newUser = new User(username, password, currentID++);
    newUser->next = head;
    head = newUser;
}

bool UserList::verifyUser(const std::string& username, const std::string& password) {
    User* curr = head;
    while (curr) {
        if (curr->username == username && curr->password == password)
            return true;
        curr = curr->next;
    }
    return false;
}

bool UserList::exists(const std::string& username) {
    User* curr = head;
    while (curr) {
        if (curr->username == username)
            return true;
        curr = curr->next;
    }
    return false;
}

std::string UserList::getPassword(const std::string& username) {
    User* curr = head;
    while (curr) {
        if (curr->username == username)
            return curr->password;
        curr = curr->next;
    }
    return "Not found";
}

void UserList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string uname, pwd;
        int id;
        ss >> uname >> pwd >> id;
        User* newUser = new User(uname, pwd, id);
        newUser->next = head;
        head = newUser;
        if (id >= currentID) currentID = id + 1;
    }
    file.close();
}

void UserList::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    User* curr = head;
    while (curr) {
        file << curr->username << " " << curr->password << " " << curr->studentID << std::endl;
        curr = curr->next;
    }
    file.close();
}
