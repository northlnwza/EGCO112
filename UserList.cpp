#include "UserList.h"
#include <fstream>
#include <sstream>
#include <iostream>

UserList::UserList() : head(nullptr), currentID(1000) {}

UserList::~UserList() {
    User* curr = head;
    while (curr) {
        User* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

void UserList::insertUser(const std::string& username, const std::string& password, Role role) {
    User* newUser;
    if (role == STUDENT)
        newUser = new Student(username, password, currentID);
    else
        newUser = new Staff(username, password, currentID);

    newUser->next = head;
    head = newUser;
    currentID++;
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

bool UserList::verifyUser(const std::string& username, const std::string& password) {
    User* curr = head;
    while (curr) {
        if (curr->username == username && curr->password == password)
            return true;
        curr = curr->next;
    }
    return false;
}

User* UserList::getUser(const std::string& username) {
    User* curr = head;
    while (curr) {
        if (curr->username == username)
            return curr;
        curr = curr->next;
    }
    return nullptr;
}

User* UserList::findByID(int id) {
    User* curr = head;
    while (curr) {
        if (curr->studentID == id)
            return curr;
        curr = curr->next;
    }
    return nullptr;
}

int UserList::getID(const std::string& username) {
    User* curr = head;
    while (curr) {
        if (curr->username == username)
            return curr->studentID;
        curr = curr->next;
    }
    return -1;
}

void UserList::deposit(int id, float amount) {
    User* user = findByID(id);
    if (user) {
        user->balance += amount;
        std::cout << "Deposit successful. Balance: " << user->balance << "\n";
    }
}

bool UserList::withdraw(int id, float amount) {
    User* user = findByID(id);
    if (user && user->balance >= amount) {
        user->balance -= amount;
        std::cout << "Withdraw successful. Balance: " << user->balance << "\n";
        return true;
    }
    return false;
}

bool UserList::transfer(int fromID, int toID, float amount) {
    User* from = findByID(fromID);
    User* to = findByID(toID);
    if (from && to && from->balance >= amount) {
        from->balance -= amount;
        to->balance += amount;
        std::cout << "Transfer successful.\n";
        return true;
    }
    std::cout << "Transfer failed.\n";
    return false;
}

void UserList::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    User* curr = head;
    while (curr) {
        file << curr->username << " " << curr->password << " " << curr->studentID
             << " " << curr->balance << " " << curr->role << "\n";
        curr = curr->next;
    }
    file.close();
}

void UserList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string uname, pwd;
    int id, roleInt;
    float balance;

    while (file >> uname >> pwd >> id >> balance >> roleInt) {
        Role role = static_cast<Role>(roleInt);
        User* user;
        if (role == STUDENT)
            user = new Student(uname, pwd, id);
        else
            user = new Staff(uname, pwd, id);

        user->balance = balance;
        user->next = head;
        head = user;

        if (id >= currentID) currentID = id + 1;
    }
    file.close();
}
