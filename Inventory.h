#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Product {
    int id;
    string name;
    float price;
    int quantity;
};

class Inventory {
private:
    vector<Product> products;
public:
    Inventory();
    void addProduct(int id, string name, float price, int quantity);
    void updateProduct(int id);
    void removeProduct(int id);
    void showInventory();
    void searchProduct(string keyword);
    float getTotalValue();
    void sortByName();
    void sortByPrice();
};

#endif
