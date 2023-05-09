#include "Inventory.h"
#include <fstream>
#include <sstream>
#include <algorithm>

Inventory::Inventory() {
    // užkrauname prekes iš CSV failo
    ifstream file("Inventorius.csv");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;
            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }
            Product product = { stoi(tokens[0]), tokens[1], stof(tokens[2]), stoi(tokens[3]) };
            products.push_back(product);
        }
        file.close();
    }
}

void Inventory::addProduct(int id, string name, float price, int quantity) {
    // patikriname, ar produktas su nurodytu ID jau yra
    auto iter = find_if(products.begin(), products.end(), [&](const Product& p) { return p.id == id;});

    if (iter != products.end()) {
        cout << "Produktas su nurodytu ID jau egzistuoja!" << endl;
        return;
    }
    // pridedame naują produktą
    Product product = { id, name, price, quantity };
    products.push_back(product);
    // įrašome pakeitimus į CSV failą
    ofstream file("inventory.csv", ios::app);
    if (file.is_open()) {
        file << id << "," << name << "," << price << "," << quantity << endl;
        file.close();
    }
}

void Inventory::updateProduct(int id) {
    // ieškome produkto su nurodytu ID
    auto iter = find_if(products.begin(), products.end(), [&](const Product& p) {
        return p.id == id;
        });
    if (iter == products.end()) {
        cout << "Produktas su nurodytu ID neegzistuoja!" << endl;
        return;
    }
    // paklausime vartotojo, ką nori pakeisti
    cout << "Ką norite pakeisti?" << endl;
    cout << "1. Kainą" << endl;
    cout << "2. Pavadinimą" << endl;
    cout << "3. Kiekį" << endl;
    int choice;
    cin >> choice;
    // atnaujiname produktą pagal pasirinkimą
    switch (choice) {
    case 1: {
        cout << "Nauja kaina: ";
        float price;
        cin >> price;
        iter->price = price;
        break;
    }
    case 2: {
        cout << "Naujas pavadinimas: ";
        string name;
        cin.ignore();
        getline(cin, name);
        iter->name = name;
        break;
    }
    case 3: {
        cout << "Naujas kiekis: ";
        int quantity;
        cin >> quantity;
        iter->quantity = quantity;
        break;
    }
    default:
        cout << "Neteisingas pasirinkimas!" << endl;
        break;
    }