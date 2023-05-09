#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

struct Product { //Produkto saugojimo struktura
    int id;
    string name;
    double price;
    int quantity;
};



//Funkciju deklaravimas
void readFile(vector <Product>& inventory); // Funkcija, kuri nuskaito faila i vektoriu
void addProduct(vector<Product>& inventory); // Funkcija, kuri prideda nauja produkta i inventoriu
void editProduct(vector<Product>& inventory);   // Funkcija, kuri keicia esamo produkto kaina, pavadinima arba kieki
void removeProduct(vector<Product>& inventory); // Funkcija, kuri pasalina produkta is inventoriaus
void displayInventory(vector<Product>& inventory);  // Funkcija, kuri rodo viso inventoriaus turini lenteles formatu
void searchProduct(vector<Product>& inventory); // Funkcija, kuri iesko produkto pagal pavadinima arba ID
void sortInventory(vector<Product>& inventory); // Funkcija, kuri rusiuoja inventoriu pagal pavadinima arba ID didejimo tvarka
void displayInventoryValue(vector<Product>& inventory); // Funkcija, kuri rodo visu inventoriuje esanciu produktu bendra verte
double calculateInventoryValue(vector<Product>& inventory); // Funkcija, kuri apskaiciuoja viso inventoriaus verte
void writeFile(vector <Product>& inventory); // Funkcija, kuri atnaujina Inventorius.txt faila
bool isIdValid(int id, vector<Product>& inventory); // Funkcija, kuri tikrina, ar vartotojo ivestas ID jau egzistuoja inventoriuje
bool isNameUnique(string name, vector<Product>& inventory); // Funkcija, kuri tikrina, ar vartotojo ivestas pavadinimas yra unikalus ir ne tuscias
string removeSpaces(string str); // Funkcija, kuri pasalina tarpus is string
bool isPositiveDouble(double number);   // Funkcija, kuri tikrina, ar vartotojo ivesta kaina yra teigiama
bool isPositiveInt(int number);   // Funkcija, kuri tikrina, ar vartotojo ivestas kiekis yra teigiamas
bool compareByName(const Product& p1, const Product& p2);   // Palygina produktus pagal varda (naudojama sortinimui)
void sortInventoryByName(vector<Product>& inventory);   // Sortina pagal varda
bool compareById(const Product& p1, const Product& p2);   // Palygina produktus pagal id (naudojama sortinimui)
void sortInventoryById(vector<Product>& inventory);   // Sortina pagal id
void printMenu(vector<Product>& inventory, bool& running); // Atspausdina meniu





//MAIN funckija
int main()
{
    vector <Product> inventory; // Sukuriamas inventoriaus vektorius
    readFile(inventory);    // Skaitomas failas
    bool running=true;

    do {    // Pagrindinis programos loopas
        printMenu(inventory, running);    // Meniu spausdinimas ir veikimas
        
    } while (running); // do ciklo kondicija
}





//Funkcijos
void readFile(vector<Product>& inventory) {
    ifstream readFile;
    readFile.open("Inventorius.txt");

    if (readFile.is_open()) {
        string line;
        Product product;

        while (getline(readFile, line)) {
            stringstream ss(line); // eilute skaido iki tarpo simboliu
            ss >> product.id >> product.name  >> product.price >> product.quantity;
            inventory.push_back(product);
        }
        readFile.close();
    }
}

void addProduct(vector<Product>& inventory) {
    int id, quantity;
    string name;
    double price;
    Product product;

    // ID ivedimas
    do {
        cout << "Iveskite produkto ID: ";
        cin >> id; cout << endl;
    } while (!isIdValid(id, inventory));
    product.id = id;

    // Pavadinimo ivedimas
    do{
        cout << "Iveskite produkto pavadinima: ";
        cin >> name;
        name = removeSpaces(name); cout << endl;
    } while (!isNameUnique(name, inventory));
    product.name = name;

    // Kiekio ivedimas
    do {
        cout << "Iveskite produkto kieki: ";
        cin >> quantity; cout << endl;
    } while (!isPositiveInt(quantity));
    product.quantity = quantity;

    // Kainos ivedimas
    do {
        cout << "Iveskite produkto kaina: ";
        cin >> price; cout << endl;
        price = round(price * 100.0) / 100.0;   // Skaiciu suapvalina iki dvieju desimtuju
    } while (!isPositiveDouble(price));
    product.price = price;

    inventory.push_back(product);
}

void editProduct(vector<Product>& inventory) {
    int id, newQuantity;
    string newName;
    double newPrice;

    cout << "Iveskite proodukto ID, kuri norite redaguoti: ";
    cin >> id; cout << endl;

    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i].id == id) {
            cout << "Redaguojama produkto " << inventory[i].name << " informacija." << endl; // Headeris
            
            do {    // Pavadinimo redagavimas
                cout << "Iveskite nauja pavadinima (arba 0, jei norite palikti sena): ";
                cin >> newName; cout << endl;
                newName = removeSpaces(newName);    // Pasalina tarpus is stringo
            } while (!isNameUnique(newName, inventory));
            if (newName != "0") {
                inventory[i].name = newName;
            }

            do {    // Kainos redagavimas
                cout << "Iveskite nauja kaina (arba 0, jei norite palikti sena kieki): ";
                cin >> newPrice; cout << endl;
                newPrice = round(newPrice * 100.0) / 100.0;   // Skaiciu suapvalina iki dvieju desimtuju
            } while (!isPositiveDouble(newPrice));
            if (newPrice > 0) {
                inventory[i].price = newPrice;  
            }

            do {    // Kiekio redagavimas
            cout << "Iveskite nauja kieki (arba 0, jei norite palikti sena kieki): ";
            cin >> newQuantity; cout << endl;
            } while (!isPositiveInt(newQuantity));
            if (newQuantity > 0) {
                inventory[i].quantity = newQuantity;
            }


            cout << "Produktas atnaujintas." << endl;
            return;
        }
    }
    cout << "Produktas nerastas." << endl;
}

void removeProduct(vector<Product>& inventory) {
    int id;
    do {
        cout << "Iveskite produkto ID, kuri norite istrinti: ";
        cin >> id; cout << endl;
    } while (!isIdValid);   // Tikrina ar egzistuoja toks ID.
    
    for (auto iter = inventory.begin(); iter != inventory.end(); iter++) {  // Ieskome produkto pagal jo ID
        if (iter->id == id) {
            inventory.erase(iter); // Jeigu produktas rastas, pasaliname ji is vektoriaus
            cout << "Produktas pasalintas." << endl;
            return;
        }
    }
}

void displayInventory(vector<Product>& inventory){
    int idWidth = 8, nameWidth = 25, priceWidth = 10, quantityWidth = 8;

    cout << left << setw(idWidth) << "ID"   // Atspausdina lenteles antraste
        << setw(nameWidth) << "Name"
        << setw(priceWidth) << "Price"
        << setw(quantityWidth) << "Quantity" << endl;

    for (int i = 0; i < inventory.size(); i++) {    // Atspausdina kiekvieno produkto informacija
        cout << left << setw(idWidth) << inventory[i].id
            << setw(nameWidth) << inventory[i].name
            << setw(priceWidth) << fixed << setprecision(2) << inventory[i].price
            << setw(quantityWidth) << inventory[i].quantity << endl;
    }
}

void searchProduct(vector<Product>& inventory) {
    int option;

    cout << "1. Paieska pagal varda" << endl;
    cout << "2. Paieska pagal ID" << endl;
    cout << "Pasirinkite veiksma: ";
    cin >> option;

    if (option == 1) {
        string name;
        cout << "Iveskite produkto pavadinima: ";
        cin >> name; cout <<endl;

        for (const auto& p : inventory) {   // Iterate vektoriu, kol randa tinkama itema
            if (p.name == name) {
                cout << "ID: " << p.id << ", Name: " << p.name << ", Price: " << p.price << ", Quantity: " << p.quantity << endl;
                return;
            }
        }
    }
    else if (option == 2) {
        int id;
        cout << "Iveskite produkto ID: ";
        cin >> id; cout << endl;

        for (const auto& p : inventory) {   // Iterate vektoriu, kol randa tinkama itema
            if (p.id == id) {
                cout << "ID: " << p.id << ", Name: " << p.name << ", Price: " << p.price << ", Quantity: " << p.quantity << endl;
                return;
            }
        }
    }
    else {
        cout << "Neteisingas pasirinkimas." << endl;
    }

    cout << "Produktas nerastas." << endl;
}

void sortInventory(vector<Product>& inventory) {
    int choice = 0;   // Vartotojo meniu pasirinkimas
    do {
        cout << "1. Rusiuoti pagal produkto pavadinima" << endl;
        cout << "2. Rusiuoti pagal id" << endl;
        cout << "Pasirinkite veiksma: ";
        cin >> choice; cout << endl;
    } while (choice < 1 || choice > 2);
        
        if (choice == 1) {
            sortInventoryByName(inventory);
        }
        else {
            sortInventoryById(inventory);
        }
}

void displayInventoryValue(vector<Product>& inventory) {
    double value = calculateInventoryValue(inventory); // Suskaiciuoja inventoriaus verte
    cout << "Inventoriaus verte: " << fixed << setprecision(2) << value << endl; // Atspausdinna inventoriaus verte
}

double calculateInventoryValue(vector<Product>& inventory) {
    double value = 0.0;
    for (int i = 0; i < inventory.size(); i++) {
        value += inventory[i].price * inventory[i].quantity; // Daugina kieki ir kaina;
    }
    return value;
}

void writeFile(vector <Product>& inventory) {
    ofstream file("Inventorius.txt"); // Atidaro faila, truncas pagal nutylejima, todel wipinami duomenys

    if (file.is_open()) {
        for (const auto& p : inventory) {
            file << p.id << " " << p.name << " " << p.price << " " << p.quantity << endl; // Isveda duomenis i faila
        }
        file.close();
        cout << "Failas atnaujintas." << endl;
    }
    else {
        cout << "Nepavyko atidaryti failo." << endl;
    }
}

bool isIdValid(int id, vector<Product>& inventory) {
    for (int i = 0; i < inventory.size(); i++) { // Iterate per vektoriu
        if (inventory[i].id == id) { // Tikrina ar nera vienodu id
            return false;
        }
    }
    return true;
}

bool isNameUnique(string name, vector<Product>& inventory) {
    if (name == "") { // Ar vardas nera tuscias
        return false;
    }
    for (int i = 0; i<inventory.size(); i++) { // Iterate per vektoriu
        if (inventory[i].name == name) { // Tikrina ar nera vienodu vardu
            return false;
        }
    }
    return true;
}

string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); // Trina tarpus
    return str;
}

bool isPositiveDouble(double number) {
    if (number >= 0.0) {
        return true;
    }
    else {
        return false;
    }
}bool isPositiveInt(int number) {

    if (number >= 0) {
        return true;
    }
    else {
        return false;
    }
}

bool compareByName(const Product& p1, const Product& p2) {
    return p1.name < p2.name;   // Lygina ASCII reiksmes
}

bool compareById(const Product& p1, const Product& p2) { 
    return p1.id < p2.id;   // Lygina int reiksmes
}

void sortInventoryByName(vector<Product>& inventory) {
    sort(inventory.begin(), inventory.end(), compareByName);
}

void sortInventoryById(vector<Product>& inventory) {
    sort(inventory.begin(), inventory.end(), compareById);
}

void printMenu(vector<Product>& inventory, bool& running)
{

    cout << endl;
    cout << "1. Prideti nauja produkta" << endl;
    cout << "2. Redaguoti esama produkta" << endl;
    cout << "3. Pasalinti produkta" << endl;
    cout << "4. Rodyti visa inventoriu" << endl;
    cout << "5. Ieskoti produkto" << endl;
    cout << "6. Rusiuoti inventoriu" << endl;
    cout << "7. Rodyti visu produktu bendra verte" << endl;
    cout << "8. Atnaujinti duomenis faile ir iseiti is programos." << endl;
    cout << "Pasirinkite veiksma: ";
    int choice = 0;   // Vartotojo meniu pasirinkimas
    while (choice < 1 || choice > 8) {  // Ciklas, neleidziantis ivesti netinkamu duomenu
        cin >> choice;
    }
    cout << endl;


    switch (choice) {
    case 1:
        addProduct(inventory);
        break;
    case 2:
        editProduct(inventory);
        break;
    case 3:
        removeProduct(inventory);
        break;
    case 4:
        displayInventory(inventory);
        break;
    case 5:
        searchProduct(inventory);
        break;
    case 6:
        sortInventory(inventory);
        break;
    case 7:
        displayInventoryValue(inventory);
        break;
    case 8:
        writeFile(inventory);
        running = false;    // Iraso i faila ir triggerina pagrindio loopo 
        break;
    }
}
