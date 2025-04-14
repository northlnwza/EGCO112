#include "Student.h"
#include "Shop.h"
#include <iostream>

Student::Student(std::string uname, std::string pwd, int id)
    : User(uname, pwd, id, STUDENT) {}

void Student::showMenu() {
    std::cout << "[Student Menu] Use 'shop()' to buy items.\n";
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
