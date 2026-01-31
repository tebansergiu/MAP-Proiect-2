#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

// --- STRUCTURI DE DATE ---
struct Book {
    int id;
    string title;
    string author;
    string isbn;
    bool isAvailable;
};

struct User {
    int id;
    string name;
};

struct Loan {
    int bookId;
    int userId;
    string returnDate; // Data scadenta (deadline)
};

// --- VARIABILE GLOBALE (Baza de date in memorie) ---
vector<Book> books;
vector<User> users;
vector<Loan> loans;

// --- FUNCTII AJUTATOARE ---

// Obtine data curenta ca string (YYYY-MM-DD)
string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-"
        << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
        << setfill('0') << setw(2) << ltm->tm_mday;
    return ss.str();
}

// Calculeaza data viitoare (Data curenta + zile)
string getFutureDate(int days) {
    time_t now = time(0) + (days * 24 * 60 * 60);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-"
        << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
        << setfill('0') << setw(2) << ltm->tm_mday;
    return ss.str();
}

// Sparge un string dupa virgula (pentru CSV)
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// --- GESTIONARE FISIERE (CSV) ---

void loadData() {
    ifstream fBooks("data/books.csv");
    string line;
    while (getline(fBooks, line)) {
        vector<string> d = split(line, ',');
        if (d.size() >= 5)
            books.push_back({ stoi(d[0]), d[1], d[2], d[3], d[4] == "1" });
    }

    ifstream fUsers("data/users.csv");
    while (getline(fUsers, line)) {
        vector<string> d = split(line, ',');
        if (d.size() >= 2)
            users.push_back({ stoi(d[0]), d[1] });
    }
    // Nota: Simplificam si nu salvam istoricul imprumuturilor vechi la restart in versiunea simpla
    // doar incarcam cartile si userii pentru a putea face operatiuni noi.
}

void saveBooks() {
    ofstream f("data/books.csv");
    for (auto& b : books) {
        f << b.id << "," << b.title << "," << b.author << "," << b.isbn << "," << (b.isAvailable ? "1" : "0") << "\n";
    }
}

void saveUsers() {
    ofstream f("data/users.csv");
    for (auto& u : users) {
        f << u.id << "," << u.name << "\n";
    }
}

// --- LOGICA APLICATIEI ---

void addBook(string title, string author, string isbn) {
    int id = books.size() + 1;
    books.push_back({ id, title, author, isbn, true });
    saveBooks();
    cout << "[OK] Carte adaugata: " << title << " (ID: " << id << ")\n";
}

void addUser(string name, int id) {
    users.push_back({ id, name });
    saveUsers();
    cout << "[OK] Utilizator adaugat: " << name << "\n";
}

void borrowBook(string bookTitle, int userId, int days) {
    // 1. Cautam userul
    bool userExists = false;
    for (auto& u : users) if (u.id == userId) userExists = true;
    if (!userExists) { cout << "[Eroare] User invalid!\n"; return; }

    // 2. Cautam cartea
    for (auto& b : books) {
        if (b.title == bookTitle) {
            if (b.isAvailable) {
                b.isAvailable = false;
                string dueDate = getFutureDate(days);
                loans.push_back({ b.id, userId, dueDate });
                saveBooks();
                cout << "[OK] Ai imprumutat '" << b.title << "' pana la " << dueDate << ".\n";
                return;
            }
            else {
                cout << "[Eroare] Cartea este deja imprumutata.\n";
                return;
            }
        }
    }
    cout << "[Eroare] Cartea nu a fost gasita.\n";
}

void returnBook(string bookTitle) {
    for (auto& b : books) {
        if (b.title == bookTitle) {
            b.isAvailable = true;
            saveBooks();
            cout << "[OK] Cartea '" << b.title << "' a fost returnata.\n";
            return;
        }
    }
    cout << "[Eroare] Cartea nu exista.\n";
}

void listBooks() {
    cout << "\n--- LISTA CARTI ---\n";
    for (auto& b : books) {
        cout << b.id << ". " << b.title << " - " << b.author
            << " [" << (b.isAvailable ? "DISPONIBIL" : "IMPRUMUTAT") << "]\n";
    }
    cout << "-------------------\n";
}

// Functie simpla pentru a extrage argumente optionale (ex: --days 14)
string getOption(char** begin, char** end, const string& option) {
    char** itr = find(begin, end, option);
    if (itr != end && ++itr != end) return string(*itr);
    return "";
}

// --- MAIN ---
int main(int argc, char* argv[]) {
    loadData(); // Incarca datele la pornire

    if (argc < 2) {
        cout << "Comenzi disponibile:\n";
        cout << "  ./app add_book \"Titlu\" \"Autor\" --isbn 1234\n";
        cout << "  ./app add_user \"Nume\" --id 101\n";
        cout << "  ./app borrow \"Titlu\" --user_id 101 --days 7\n";
        cout << "  ./app return \"Titlu\"\n";
        cout << "  ./app list\n";
        return 1;
    }

    string command = argv[1];

    if (command == "add_book") {
        if (argc < 4) { cout << "Lipsesc argumente!\n"; return 1; }
        string isbn = getOption(argv, argv + argc, "--isbn");
        addBook(argv[2], argv[3], isbn.empty() ? "N/A" : isbn);
    }
    else if (command == "add_user") {
        string idStr = getOption(argv, argv + argc, "--id");
        if (idStr.empty()) { cout << "Lipseste --id!\n"; return 1; }
        addUser(argv[2], stoi(idStr));
    }
    else if (command == "borrow") {
        string uidStr = getOption(argv, argv + argc, "--user_id");
        string daysStr = getOption(argv, argv + argc, "--days");
        if (uidStr.empty()) { cout << "Lipseste --user_id!\n"; return 1; }
        borrowBook(argv[2], stoi(uidStr), daysStr.empty() ? 14 : stoi(daysStr));
    }
    else if (command == "return") {
        returnBook(argv[2]);
    }
    else if (command == "list") {
        listBooks();
    }
    else {
        cout << "Comanda necunoscuta!\n";
    }

    return 0;
}
