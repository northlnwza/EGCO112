#include <iostream>
#include "UserList.h"

using namespace std;

void showMenu() {
    cout << "\n===== Student Account Menu =====\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Save to file\n";
    cout << "4. Load from file\n";
    cout << "0. Exit\n";
    cout << "Choose: ";
}

void userSession(UserList& userList, const string& username) {
    User* user = userList.findByID(userList.getID(username));
    if (!user) {
        cout << "User not found.\n";
        return;
    }

    int choice;
    do {
        cout << "\n-- Welcome, " << username << " (ID: " << user->studentID << ") --\n";
        cout << "1. Add money\n";
        cout << "2. Take out money\n";
        cout << "3. Send money to other ID\n";
        cout << "4. Show my money\n";
        cout << "0. Logout\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1) {
            float amount;
            cout << "Enter amount: ";
            cin >> amount;
            userList.deposit(user->studentID, amount);

        } else if (choice == 2) {
            float amount;
            cout << "Enter amount: ";
            cin >> amount;
            userList.withdraw(user->studentID, amount);

        } else if (choice == 3) {
            int toID;
            float amount;
            cout << "Enter ID to send to: ";
            cin >> toID;
            cout << "Enter amount: ";
            cin >> amount;
            userList.transfer(user->studentID, toID, amount);

        } else if (choice == 4) {
            cout << "Your balance: " << user->balance << "\n";
        }

    } while (choice != 0);
}

int main() {
    UserList userList;
    string filename = "users.txt";
    int choice;

    do {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            string uname, pwd;
            cout << "Enter username: ";
            cin >> uname;
            if (userList.exists(uname)) {
                cout << "Username already exists!\n";
            } else {
                cout << "Enter password: ";
                cin >> pwd;
                userList.insertUser(uname, pwd);
                cout << "Register success!\n";
            }

        } else if (choice == 2) {
            string uname, pwd;
            cout << "Enter username: ";
            cin >> uname;
            cout << "Enter password: ";
            cin >> pwd;
            if (userList.verifyUser(uname, pwd)) {
                userSession(userList, uname);
            } else {
                cout << "Wrong username or password.\n";
            }

        } else if (choice == 3) {
            userList.saveToFile(filename);
            cout << "Saved to file.\n";

        } else if (choice == 4) {
            userList.loadFromFile(filename);
            cout << "Loaded from file.\n";
        }

    } while (choice != 0);

    cout << "Goodbye!\n";
    return 0;
}