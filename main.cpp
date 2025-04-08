#include <iostream>
#include "Auth.h"
#include "UserList.h"
using namespace std;

void authMenu() {
    int choice;
    string uname, pass, newPass, sid;
    UserList userList;

    do {
        cout << "\n1. Register\n2. Login\n3. Reset Password\n4. View Sorted Users\n5. Exit\nChoose: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Username: ";
            cin >> uname;
            cout << "Password: ";
            cin >> pass;
            cout << "Student ID: ";
            cin >> sid;
            {
                Auth newUser(uname, pass, sid);
                if (newUser.registerUser()) {
                    cout << "Registered successfully.\n";
                    userList.addUser(newUser);
                } else {
                    cout << "Username already exists.\n";
                }
            }
            break;
        case 2:
            cout << "Username: ";
            cin >> uname;
            cout << "Password: ";
            cin >> pass;
            {
                Auth loginUser;
                if (loginUser.login(uname, pass)) {
                    cout << "Login successful.\n";
                } else {
                    cout << "Invalid credentials.\n";
                }
            }
            break;
        case 3:
            cout << "Username: ";
            cin >> uname;
            cout << "New Password: ";
            cin >> newPass;
            {
                Auth resetUser;
                if (resetUser.resetPassword(uname, newPass)) {
                    cout << "Password reset.\n";
                } else {
                    cout << "Username not found.\n";
                }
            }
            break;
        case 4:
            cout << "\nSorted Users:\n";
            userList.displayUsers();
            break;
        }
    } while (choice != 5);
}

int main() {
    authMenu();
    return 0;
}
