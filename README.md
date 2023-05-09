# [StrongPoint intern] Inventoriaus valdymo sistema

Ši programa yra paprasta inventoriaus valdymo sistema, sukurta naudojant C++ kalbą. Ši sistema leidžia pridėti naujus produktus į inventorių, redaguoti jau esamus produktus, šalinti produktus, atvaizduoti visą inventorių lentelės formatu, ieškoti produktų pagal pavadinimą arba ID, bei saugoti inventoriaus duomenis faile.
Kaip paleisti programą?

Prisirengimas

    Įdiekite Microsoft Visual Studio 2022.

    Atidarykite projektą naudodami Microsoft Visual Studio 2022.

Kompiliavimas

    Atidarykite "Solution Explorer" langą.

    Pasirinkite projektą ir paspauskite dešinį pelės klavišą.

    Pasirinkite "Build" ir spustelėkite "Build Solution".

    Jei kompiliavimas buvo sėkmingas, turėtų būti sukuriamas vykdomasis failas.
    
    Taip pat programą galima paleisti Debug režimu.

Paleidimas

    Atidarykite "Command Prompt" langą.

    Naviguokite į katalogą, kuriame yra sukurtas vykdomasis failas.

    Parašykite pavadinimą ir spustelėkite "Enter".

    Programa turėtų būti paleista.

Kaip naudotis programa?

Paleidus programą, vartotojas bus prašomas pasirinkti, ką jis nori daryti. Pagrindinis meniu apima šias funkcijas:

    Pridėti naują produktą į inventorių
    Redaguoti esamą produktą
    Ištrinti produktą iš inventoriaus
    Atvaizduoti visą inventorių lentelės formatu
    Ieškoti produkto pagal pavadinimą arba ID
    Rūšiuoti produktus pagal pavadinimą arba ID
    Rodyti visų produktų bendrą vertę
    Baigti programos darbą

Pasirinkus atitinkamą funkciją, vartotojas bus prašomas įvesti produktą, kuriuo jis nori atlikti veiksmą. Jei produktas nėra rastas, vartotojas bus informuojamas ir bus paprašytas įvesti naują produktą. Kai produktas yra rastas, vartotojas bus prašomas įvesti atitinkamus duomenis, pavyzdžiui, pavadinimą, kainą ar kiekį. Taip pat bus vykdomos patikros, kad vartotojas įveda tik teisingus duomenis. Po to, kai duomenys yra įvesti, jie bus išsaugoti į vektorių ir atvaizduojami vartotojui.

Programos naudojimas:

    Pasirinkite norimą funkciją iš meniu.
    Jei norite pridėti naują produktą, įveskite produkto pavadinimą, kainą ir kiekį. Patikrinkite, ar įvesti duomenys teisingi.
    Jei norite keisti esamo produkto informaciją, įveskite produkto ID ir įveskite naują reikšmę. Jei nenorite keisti reikšmės - įveskite 0.
    Jei norite pašalinti produktą, įveskite produkto ID.
    Jei norite rasti produktą, įveskite pavadinimą arba ID.
    Jei norite rūšiuoti produktus, pasirinkite pagal ką norite rūšiuoti (pavadinimą arba ID).
    Jei norite pamatyti bendrą inventoriaus vertę, pasirinkite atitinkamą meniu punktą.

Duomenų tikrinimas:

    Produkto pavadinimas negali būti tuščias
    Produkto kaina ir kiekis turi būti teigiamos sveikosios arba realiosios skaičių reikšmės.
    Produkto ID turi būti teigiamas sveikasis skaičius.
    
    Duomenų saugojimas:

    Duomenys saugomi products.txt faile, kuris yra programos kataloge.
    Prieš paleidžiant programą, galite atidaryti products.txt failą ir papildyti jame produktų informaciją.
    Paleidus programą, informacija iš failo products.txt bus nuskaityta ir patalpinta į programos vektorių.

Funkcijų aprašymas:

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
bool compareByName(const Product& p1, const Product& p2);   // Funkcija, kuri palygina produktus pagal varda (naudojama sortinimui)
void sortInventoryByName(vector<Product>& inventory);   // Funkcija, kuri sortina pagal varda
bool compareById(const Product& p1, const Product& p2);   // Funkcija, kuri palygina produktus pagal id (naudojama sortinimui)
void sortInventoryById(vector<Product>& inventory);   // Funkcija, kuri rusiuoja pagal id
void printMenu(vector<Product>& inventory, bool& running); // Funkcija, kuri atspausdina meniu
  
Kodo kokybė:

    Kode naudojami aiškūs kintamųjų pavadinimai.
    Funkcijos yra gerai struktūrizuotos ir komentuotos.
    Duomenų tikrinimas užtikrina, kad vartotojas negali įvesti neteisingų duomenų.

Naudotojo patirtis:

    Programos meniu yra aiškus ir lengvai suprantamas.
    Visos funkcijos yra lengvai pasiekiamos iš meniu.
    Duomenų tikrinimas užtikrina, kad vartotojas negali įvesti neteisingų duomenų.
