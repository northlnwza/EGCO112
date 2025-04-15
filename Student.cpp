#include "Student.h"
#include "Shop.h"
#include "Score.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;

Student::Student(string uname, string pwd, int id)
    : User(uname, pwd, id, STUDENT) {
    subjects["Physics"] = Score();
    subjects["Calculus"] = Score();
    subjects["Chemistry"] = Score();
    subjects["Computer"] = Score();
}

void Student::showMenu(UserList& userList) {
    int choice;
    do {
        cout << "\n=== Student Menu ===\n";
        cout << "1. Enter Scores\n";
        cout << "2. Show Scores & Grades\n";
        cout << "3. Delete Scores\n";
        cout << "4. Shopping\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: enterScore(); break;
            case 2: showScores(); break;
            case 3: deleteScores(); break;
            case 4: openShopMenu(userList); break;
            case 0: return;
            default: cout << "Invalid choice.\n";
        }
    } while (true);
}

void Student::openShopMenu(UserList& userList) {
    int choice;
    do {
        cout << "\n[Logged in as: " << username << " | ID: " << studentID << " | Role: Student]\n";
        cout << "1. Add money\n";
        cout << "2. Withdraw money\n";
        cout << "3. Transfer money\n";
        cout << "4. Show balance\n";
        cout << "5. Shop\n";
        cout << "0. Back\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                float amt; cout << "Enter amount: "; cin >> amt;
                userList.deposit(studentID, amt);
                break;
            }
            case 2: {
                float amt; cout << "Enter amount: "; cin >> amt;
                userList.withdraw(studentID, amt);
                break;
            }
            case 3: {
                int toID; float amt;
                cout << "Enter receiver ID: "; cin >> toID;
                cout << "Enter amount: "; cin >> amt;
                userList.transfer(studentID, toID, amt);
                break;
            }
            case 4:
                cout << "Balance: " << balance << "\n";
                break;
            case 5:
                shop();
                break;
            case 0:
                return;
            default:
                cout << "Invalid choice.\n";
        }
    } while (true);
}

void Student::shop() {
    Shop shop;
    shop.loadItems("shop.txt");
    shop.showItems();

    std::string item;
    std::cout << "Enter item to buy: ";
    std::cin >> item;

    if (shop.buyItem(item, balance)) {
        std::cout << "Purchased " << item << "! Remaining balance: " << balance << "\n";
    } else {
        std::cout << "Could not purchase item.\n";
    }
}

//score

void Student::enterScore() {
    cout << "Subjects:\n1. Physics\n2. Calculus\n3. Chemistry\n4. Computer\nChoose subject (1-4): ";
    int sub; cin >> sub;
    string subName;
    switch (sub) {
        case 1: subName = "Physics"; break;
        case 2: subName = "Calculus"; break;
        case 3: subName = "Chemistry"; break;
        case 4: subName = "Computer"; break;
        default: cout << "Invalid subject."; return;
    }

    cout << "1. Midterm\n2. Final\nChoose score type: ";
    int type; cin >> type;
    cout << "Enter score (0-50): ";
    float score; cin >> score;
    if (score < 0 || score > 50) {
        cout << "Invalid score."; return;
    }

    if (type == 1)
        subjects[subName].midterm = score;
    else if (type == 2)
        subjects[subName].final = score;
    else {
        cout << "Invalid type."; return;
    }

    cout << subName << (type == 1 ? " Midterm" : " Final") << " score updated to " << score << endl;
    saveToFile();
}

void Student::showScores() {
    cout << fixed << setprecision(1);
    for (auto& [sub, score] : subjects) {
        float total = score.midterm + score.final;
        char grade;
        if (total >= 80) grade = 'A';
        else if (total >= 70) grade = 'B';
        else if (total >= 60) grade = 'C';
        else if (total >= 50) grade = 'D';
        else grade = 'F';

        cout << sub << ":\n  Midterm: " << score.midterm << "/50\n  Final: " << score.final << "/50\n  Total: " << total << "/100\n  Grade: " << grade << "\n\n";
    }
}

void Student::deleteScores() {
    for (auto& [sub, score] : subjects) {
        score.midterm = 0.0;
        score.final = 0.0;
    }
    cout << "All scores have been reset to 0.\n";
    saveToFile();
}

void Student::saveToFile() {
    ifstream in("user.txt");
    if (!in) {
        cerr << "Error reading user.txt\n";
        return;
    }

    vector<string> lines;
    string line;
    while (getline(in, line)) {
        lines.push_back(line);
    }
    in.close();

    bool updated = false;

    for (size_t i = 0; i < lines.size(); ++i) {
        istringstream iss(lines[i]);
        string uname, pwd;
        int id, role;
        float balance;

        iss >> uname >> pwd >> id >> role >> balance;

        if (uname == username && role == STUDENT) {
            if (i + 1 < lines.size() && lines[i + 1].rfind("scores:", 0) == 0) {
                lines.erase(lines.begin() + i + 1);
            }

            ostringstream scoreLine;
            scoreLine << "scores:";
            for (const auto& [sub, score] : subjects) {
                scoreLine << " " << sub << "=" << score.midterm << "," << score.final;
            }

            lines.insert(lines.begin() + i + 1, scoreLine.str());
            updated = true;
            break;
        }
    }

    if (!updated) {
        ostringstream newEntry;
        newEntry << username << " " << password << " " << studentID << " " << STUDENT << " " << balance;
        lines.push_back(newEntry.str());

        ostringstream scoreLine;
        scoreLine << "scores:";
        for (const auto& [sub, score] : subjects) {
            scoreLine << " " << sub << "=" << score.midterm << "," << score.final;
        }
        lines.push_back(scoreLine.str());
    }

    ofstream out("user.txt");
    for (const string& l : lines) {
        out << l << "\n";
    }
    out.close();

    cout << "Data Saved\n";
}
