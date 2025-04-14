#ifndef SHOP_H
#define SHOP_H

#include <vector>
#include <string>

struct Item {
    std::string name;
    float price;
};

class Shop {
private:
    std::vector<Item> items;

public:
    void loadItems(const std::string& filename);
    void saveItems(const std::string& filename);
    void showItems();
    void addItem(const std::string& name, float price);
    bool buyItem(const std::string& itemName, float& userBalance);
};

#endif
