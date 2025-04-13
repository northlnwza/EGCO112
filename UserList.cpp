#include <sys/stat.h>
#include <sys/types.h>
#include "UserList.h"
#include <fstream>
#include <sstream>

using namespace std;

User::User(std::string uname, std::string pwd, int id)
    : username(uname), password(pwd), id(id), next(nullptr) {}

UserList::UserList() : head(nullptr), currentID(1000) {}

UserList::~UserList() {
    User* curr = head;
    while (curr) {
        User* tmp = curr;
        curr = curr->next;
        delete tmp; //call destructor of User automatically even if we didn't define it
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

int UserList::getID(const std::string& username) {
    User* curr = head;
    while (curr) {
        if (curr->username == username)
            return curr->id;
        curr = curr->next;
    }
    return -1;
}

User* UserList::findByID(int id)
{
    User* curr = head;
    while (curr) {
        if (curr->id == id) return curr;
        curr = curr->next;
    }
    return nullptr;
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
// load from file users.txt format
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
/* method to read data from data.txt.
User getData(const string &username)
{
    User u;
    string path = "userdata/" + username + "/data.txt";
    ifstream file(path);
    string line;


    if (!file) {
        std::cerr << "Data file not found for user: " << username << std::endl;
        return u;
    }
    while (getline(file, line)) 
    {
        if (line.rfind("Username:", 0) == 0) {
            u.username = line.substr(9);// from index 9 onward
        } else if (line.rfind("ID:", 0) == 0) 
        {
            u.studentID = stoi(line.substr(3));
        } else if (line.rfind("Password:", 0) == 0)
        {
            u.password = line.substr(9);
        }
    }
    file.close();
    return u;
}
*/

void UserList::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    User* curr = head;
    while (curr) {
        file << curr->username << " " << curr->password << " " << curr->id << std::endl;
        makedir(curr->username, curr->password, curr->id);
        curr = curr->next;
    }
    file.close();
}



void makedir(const string & username, string & password, int id)
{
	string folder = "userdata/" + username;
	string file = folder + "/data.txt";
    
    mkdir("userdata", 0777);
	mkdir(folder.c_str(), 0777);
    ofstream userFile(file);
    userFile << "Username: " << username << endl;
    userFile << "Password: " << password << endl;
    userFile << "ID: " << id << endl;
    userFile.close();
}
