#include "Shop.h"
#include <fstream>
#include <iostream>

void Shop::loadItems(const std::string& filename) {
    items.clear();
    std::ifstream file(filename);
    std::string name;
    float price;
    while (file >> name >> price) {
        items.push_back({name, price});
    }
    file.close();
}

void Shop::saveItems(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& item : items) {
        file << item.name << " " << item.price << "\n";
    }
    file.close();
}

void Shop::showItems() {
    std::cout << "\nAvailable items:\n";
    for (const auto& item : items) {
        std::cout << "- " << item.name << " : " << item.price << "\n";
    }
}

void Shop::addItem(const std::string& name, float price) {
    items.push_back({name, price});
}

bool Shop::buyItem(const std::string& itemName, float& userBalance) {
    for (const auto& item : items) {
        if (item.name == itemName && userBalance >= item.price) {
            userBalance -= item.price;
            return true;
        }
    }
    return false;
}
