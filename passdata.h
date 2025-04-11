#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
struct userdata
{
    string  username;
    string  password;
    int id;
};

struct userdata getData(const string &username);