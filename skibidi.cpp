#include <iostream>
#include "UserList.h"

using namespace std;

void showMainMenu() {
    cout << "\n--- Main Menu ---\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Save to file\n";
    cout << "4. Load from file\n";
    cout << "0. Exit\n";
    cout << "Choose: ";
}

void session(User* user, UserList& userList) {
    int choice;
    do {
        cout << "\n[Logged in as: " << user->username << " | ID: " << user->studentID << " | Role: "
             << (user->role == STUDENT ? "Student" : "Staff") << "]\n";
        cout << "1. Add money\n";
        cout << "2. Withdraw money\n";
        cout << "3. Transfer money\n";
        cout << "4. Show balance\n";
        cout << "5. Shop\n";
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
            cout << "Enter receiver ID: ";
            cin >> toID;
            cout << "Enter amount: ";
            cin >> amount;
            userList.transfer(user->studentID, toID, amount);
        } else if (choice == 4) {
            cout << "Your balance: " << user->balance << "\n";
        } else if (choice == 5) {
            user->shop();
        }

    } while (choice != 0);
}

int main() {
    UserList userList;
    string filename = "users.txt";
    int choice;

    do {
        showMainMenu();
        cin >> choice;

        if (choice == 1) {
            string uname, pwd;
            int roleInput;
            cout << "Enter username: ";
            cin >> uname;

            if (userList.exists(uname)) {
                cout << "Username already exists.\n";
                continue;
            }

            cout << "Enter password: ";
            cin >> pwd;
            cout << "Role (0 = Student, 1 = Staff): ";
            cin >> roleInput;
            Role role = static_cast<Role>(roleInput);

            userList.insertUser(uname, pwd, role);
            cout << "Registration successful!\n";

        } else if (choice == 2) {
            string uname, pwd;
            cout << "Enter username: ";
            cin >> uname;
            cout << "Enter password: ";
            cin >> pwd;

            if (userList.verifyUser(uname, pwd)) {
                User* user = userList.getUser(uname);
                session(user, userList);
            } else {
                cout << "Invalid login.\n";
            }

        } else if (choice == 3) {
            userList.saveToFile(filename);
            cout << "Data saved.\n";

        } else if (choice == 4) {
            userList.loadFromFile(filename);
            cout << "Data loaded.\n";
        }

    } while (choice != 0);

    cout << "Goodbye!\n";
    return 0;
}
