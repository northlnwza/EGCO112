#include "UserList.h"
#include <fstream>
#include <sstream>

User::User(std::string uname, std::string pwd, int id)
    : username(uname), password(pwd), studentID(id), balance(0.0), next(nullptr) {} 


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
        float balance;
        ss >> uname >> pwd >> id >> balance;
        User* newUser = new User(uname, pwd, id);
        newUser->balance = balance;

        head = newUser;
        if (id >= currentID) currentID = id + 1;
    }
    file.close();
}

void UserList::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    User* curr = head;
    while (curr) {
        file << curr->username << " " << curr->password << " " << curr->studentID << " " << curr->balance << std::endl;
        curr = curr->next;
    }
    file.close();
}



User* UserList::findByID(int id) {
    User* curr = head;
    while (curr) {
        if (curr->studentID == id) return curr;
        curr = curr->next;
    }
    return nullptr;
}

void UserList::deposit(int id, float amount) {
    User* user = findByID(id);
    if (user) {
        user->balance += amount;
        std::cout << "Deposit successful! Your balance: " << user->balance << "\n";
    } else {
        std::cout << "User not found.\n";
    }
}

bool UserList::withdraw(int id, float amount) {
    User* user = findByID(id);
    if (user && user->balance >= amount) {
        user->balance -= amount;
        std::cout << "Withdraw successful! Your balance: " << user->balance << "\n";
        return true;
    } else {
        std::cout << "Not enough money or user not found.\n";
        return false;
    }
}

bool UserList::transfer(int fromID, int toID, float amount) {
    User* fromUser = findByID(fromID);
    User* toUser = findByID(toID);

    if (!fromUser || !toUser) {
        std::cout << "Sender or receiver not found.\n";
        return false;
    }

    if (fromUser->balance < amount) {
        std::cout << "Not enough money to transfer.\n";
        return false;
    }

    fromUser->balance -= amount;
    toUser->balance += amount;

    std::cout << "Transfer successful from ID " << fromID << " to ID " << toID << "\n";
    return true;
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
