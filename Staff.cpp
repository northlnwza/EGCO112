#include "Staff.h"
#include "Shop.h"
#include <iostream>

Staff::Staff(std::string uname, std::string pwd, int id)
    : User(uname, pwd, id, STAFF) {}

void Staff::showMenu() {
    std::cout << "[Staff Menu] Use 'shop()' to manage store.\n";
}

void Staff::shop() {
    Shop shop;
    shop.loadItems("shop.txt");

    std::string name;
    float price;
    std::cout << "Enter item name to add: ";
    std::cin >> name;
    std::cout << "Enter item price: ";
    std::cin >> price;

    shop.addItem(name, price);
    shop.saveItems("shop.txt");
    std::cout << "Item added successfully.\n";
}
