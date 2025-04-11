
#include "passdata.h"

userdata getData(const string &username)
{
    userdata u;
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
            u.id = stoi(line.substr(3));
        } else if (line.rfind("Password:", 0) == 0)
        {
            u.password = line.substr(9);
        }
    }
    file.close();
    return u;
}