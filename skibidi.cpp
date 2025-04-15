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
    if (user->role == STUDENT) {
        Student* student = dynamic_cast<Student*>(user);
        if (student) {
            student->showMenu(userList);  // Student-specific menu
            return;
        }
    } else if (user->role == STAFF) {
        int choice;
        do {
            cout << "\n=== Staff Menu ===\n";
            cout << "[Logged in as: " << user->username << " | ID: " << user->studentID << " | Role: Staff]\n";
            cout << "1. Add money\n";
            cout << "2. Withdraw money\n";
            cout << "3. Transfer money\n";
            cout << "4. Show balance\n";
            cout << "5. Shop\n";
            cout << "0. Logout\n";
            cout << "Choose: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    float amount;
                    cout << "Enter amount: ";
                    cin >> amount;
                    userList.deposit(user->studentID, amount);
                    break;
                }
                case 2: {
                    float amount;
                    cout << "Enter amount: ";
                    cin >> amount;
                    userList.withdraw(user->studentID, amount);
                    break;
                }
                case 3: {
                    int toID;
                    float amount;
                    cout << "Enter receiver ID: ";
                    cin >> toID;
                    cout << "Enter amount: ";
                    cin >> amount;
                    userList.transfer(user->studentID, toID, amount);
                    break;
                }
                case 4:
                    cout << "Your balance: " << user->balance << "\n";
                    break;
                case 5:
                    user->shop();
                    break;
                case 0:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }
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
