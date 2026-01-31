# Sistem Management Bibliotecă

Aplicație de linie de comandă pentru gestionarea unei biblioteci mici (cărți, utilizatori, împrumuturi), cu funcționalități de împrumut, returnare, căutare avansată, rapoarte și export CSV.

## Autor

- **Nume:** Teban Sergiu-Alexandru
- **Grupă:** 3.2
- **Email:** sergiu-alexandru.teban@student.upt.ro
- **An academic:** 2025-2026

## Descriere

Aplicația gestionează o bibliotecă personală sau o bibliotecă mică, permițând administrarea cărților, a utilizatorilor și a împrumuturilor. Sistemul oferă funcții de căutare avansată, verificare disponibilitate, rapoarte și statistici despre utilizarea colecției. Scopul este să ofere un mod simplu de urmărire a împrumuturilor și de analiză a celor mai populare cărți și utilizatori.

Funcționalități principale:
- Gestionare cărți (adăugare, listare, căutare, disponibilitate)
- Gestionare utilizatori (înregistrare, istoric împrumuturi)
- Împrumut și returnare cărți, cu dată limită
- Raportare (cărți împrumutate, întârziate, utilizatori activi)
- Statistici (cărți populare, categorii, utilizatori activi)
- Export/import date în/din CSV (catalog, împrumuturi, istoric utilizatori)

## Tehnologii folosite

- **Limbaj:** C++17
- **Biblioteci:**
  - `<vector>`, `<map>`, `<string>` – stocare și manipulare date
  - `<fstream>` – citire/scriere fișiere CSV
  - `<chrono>` / `<ctime>` – lucru cu date calendaristice
- **Tools:** Git, Docker, GitHub Actions

## Cerințe sistem

- Compilator C++ cu suport pentru C++17 (g++ sau clang++)
- Sistem de operare: Linux (testat pe Ubuntu-latest prin GitHub Actions)
- Dependențe externe:
  - `g++` / `build-essential` pentru build
  - Docker (opțional, pentru rulare în container)

## Instalare

```bash
# Clone repository
git clone https://github.com/tebansergiu/MAP-Proiect-2.git
cd MAP-Proiect-2

# Build local (folosind g++)
g++ -std=c++17 -O2 src/main.cpp -o library_manager

# Comandă de bază (help)
./library_manager --help

# Adăugare carte
./library_manager add_book "1984" "George Orwell" --isbn 9780451524935 --category "Fiction"

# Adăugare utilizator
./library_manager add_user "Popescu Ion" --id 1001 --email "ion@example.com"

# Listare cărți
./library_manager list

# Exemple

$ ./library_manager add_book "1984" "George Orwell" --isbn 9780451524935 --category "Fiction"

Sistem Management Bibliotecă
Carte adăugată cu succes!
Titlu: 1984
Autor: George Orwell
ISBN: 9780451524935
Categorie: Fiction
Status: DISPONIBIL
Data adăugare: 2025-10-13
Catalog actualizat în library.csv

$ ./library_manager add_user "Popescu Ion" --id 1001 --email "ion@example.com"

Utilizator adăugat:
Nume: Popescu Ion
ID: 1001
Email: ion@example.com
Data înregistrare: 2025-10-13
Cărți împrumutate: 0
Status: ACTIV

$ ./library_manager borrow "1984" --user_id 1001 --days 14

Verificare disponibilitate... ✓
Carte disponibilă! ✓
Utilizator valid! ✓

Împrumut înregistrat:
Carte: 1984 (George Orwell)
Utilizator: Popescu Ion (ID: 1001)
Data împrumut: 2025-10-13
Data returnare: 2025-10-27 (14 zile)

Reminder: Returnează cartea până la 2025-10-27 pentru a evita penalități!

$ ./library_manager list --status borrowed

Cărți Împrumutate (3 total)
┌────┬──────────────────┬──────────────┬───────────┬────────────┐
│ ID │ Titlu            │ Împrumutat de│ Împrumut  │ Return     │
├────┼──────────────────┼──────────────┼───────────┼────────────┤
│ 1  │ 1984             │ Popescu Ion  │ 2025-10-13│ 2025-10-27 │
│ 2  │ Animal Farm      │ Ionescu Ana  │ 2025-10-10│ 2025-10-24 │
│ 3  │ Brave New World  │ Georgescu M. │ 2025-10-05│ 2025-10-19 │
└────┴──────────────────┴──────────────┴───────────┴────────────┘

$ ./library_manager return "1984" --user_id 1001

Procesare returnare...
Carte returnată cu succes!

Carte: 1984
Utilizator: Popescu Ion
Data împrumut: 2025-10-13
Data returnare efectivă: 2025-10-13 (ASTĂZI)
Zile împrumut: 0 zile

✓ Returnat la timp!
✓ Fără penalități

Cartea este acum DISPONIBILĂ pentru împrumut.

$ ./library_manager report --overdue

Raport Cărți Întârziate
Generat: 2025-10-13 14:30

2 cărți sunt returnate cu întârziere:

1. Animal Farm (George Orwell)
   Utilizator: Ionescu Ana (ID: 1002)
   Deadline: 2025-10-24
   Întârziere: 0 zile (scadent ASTĂZI!)
   Penalitate: 0 RON

2. Brave New World (Aldous Huxley)
   Utilizator: Georgescu Maria (ID: 1003)
   Deadline: 2025-10-19
   Întârziere: 5 zile
   Penalitate: 5 RON (1 RON/zi)

Total penalități de colectat: 5 RON

$ ./library_manager search --author "Orwell"

Rezultate căutare autor "Orwell":
1. 1984
   Autor: George Orwell
   ISBN: 9780451524935
   Status: ✓ DISPONIBIL
   Categoria: Fiction
   Împrumuturi totale: 12 (Popular!)

2. Animal Farm
   Autor: George Orwell
   ISBN: 9780451526342
   Status: ÎMPRUMUTAT (returnare: 2025-10-24)
   Categoria: Fiction
   Împrumuturi totale: 8

Total găsite: 2 cărți

$ ./library_manager stats --summary

Statistici Bibliotecă - Octombrie 2025

COLECȚIE:
  Total cărți: 156
  Categorii: 12
  Autori unici: 89

STATUS CĂRȚI:
  Disponibile: 143 (91.7%)
  Împrumutate: 13 (8.3%)

UTILIZATORI:
  Total înregistrați: 45
  Activi (luna curentă): 23 (51.1%)
  Cu împrumuturi active: 13

ÎMPRUMUTURI:
  Total luna aceasta: 67
  Medie/zi: 2.2
  Rată returnare la timp: 92%
  Cărți întârziate: 2 (3%)

TOP 5 CĂRȚI POPULARE:
  1. "To Kill a Mockingbird" - 18 împrumuturi
  2. "1984" - 12 împrumuturi
  3. "Pride and Prejudice" - 11 împrumuturi
  4. "The Great Gatsby" - 10 împrumuturi
  5. "Brave New World" - 9 împrumuturi

$ ./library_manager export --format csv --output data/library_catalog.csv

Export în desfășurare...
✓ Exportat 156 cărți
✓ Exportat 45 utilizatori
✓ Exportat 67 împrumuturi (luna curentă)

Fișiere generate:
-  data/library_catalog.csv (catalog complet)
-  data/active_loans.csv (împrumuturi active)
-  data/user_history.csv (istoric utilizatori)

Export complet în 0.3 secunde.

Funcționalități implementate
 Adăugare cărți cu detalii (titlu, autor, ISBN, categorie, an)

 Gestionare utilizatori (nume, ID, email, istoric)

 Împrumut cărți cu dată limită (ex: 14 zile)

 Returnare cărți și calculare întârzieri

 Căutare după titlu, autor, ISBN, categorie

 Verificare disponibilitate

 Rapoarte: cărți împrumutate, cărți întârziate, utilizatori activi

 Statistici: rate împrumut, cărți populare, autori preferați

 Export catalog și date în CSV

 Sistem de rezervări (opțional / în lucru)

 Sistem avansat de amenzi/taxe (extensii viitoare)

MAP-Proiect-2/
├── README.md
├── .gitignore
├── .github/
│   └── workflows/
│       └── build.yml       # CI (build C++)
│       └── docker-image.yml # Build & push Docker
├── src/
│   ├── main.cpp            # punct de intrare, parsare argumente
│   └── ...                  # servicii, repository, utilitare
├── data/
│   ├── books.csv         #  cărți
│   ├── users.csv           # utilizatori
│   
└── Dockerfile

Decizii de design
Am separat logica aplicației pe entități (Book, User, Loan) pentru a reflecta clar domeniul (cărți, utilizatori, împrumuturi) și pentru a face codul mai ușor de extins.

Am folosit containere STL (std::vector, std::map) pentru gestionarea colecțiilor de obiecte, deoarece oferă iterație ușoară, căutare rapidă și integrare bună cu algoritmii standard.

Persistența datelor se face în fișiere CSV pentru a fi ușor de importat/exportat și inspectat manual, fără baze de date externe.

Logica de business (validări, calcule de întârzieri, penalități) este separată de partea de I/O (citire fișiere, afișare în consolă) pentru o mai bună testare și întreținere.

Probleme întâlnite și soluții
Problema: gestionarea corectă a datelor calendaristice (calcul zile, întârzieri).

Soluție: utilizarea bibliotecilor standard C++ pentru timp și conversii (de ex. std::chrono) și definirea unor funcții de utilitate pentru calculul numărului de zile dintre două date.

Problema: menținerea sincronizării între fișierele CSV (cărți, utilizatori, împrumuturi).

Soluție: definirea unei clase/service central (de exemplu LibraryManager) care coordonează toate operațiile și se ocupă de salvare/încărcare într-un mod unitar.

# Docker
docker build -t tebansergiu/map-proiect2 .
docker run --rm tebansergiu/map-proiect2 ./library_manager --help
docker run --rm tebansergiu/map-proiect2 ./library_manager list

Resurse folosite
Documentația oficială C++ (cppreference)

Tutoriale STL (vector, map, string)

Documentația Docker și GitHub Actions pentru CI/CD
