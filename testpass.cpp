#include <iostream>
#include <string>
#include "passdata.h"

using namespace std;

void    test(struct userdata & u)
{
    cout << u.username << endl;
    cout << u.password << endl;
    cout << u.id << endl;
}