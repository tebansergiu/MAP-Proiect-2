# Library Manager

Aplicație de linie de comandă pentru gestionarea unei biblioteci mici: cărți, utilizatori și împrumuturi, cu salvare în fișiere CSV.

## Autor
- **Nume:** Teban Sergiu-Alexandru
- **Grupă:** 3.2
- **Email:** sergiu-alexandru.teban@student.upt.ro
- **An academic:** 2025-2026

## Descriere

Aplicația permite:
- adăugarea de cărți cu titlu, autor și ISBN;
- adăugarea de utilizatori cu nume și ID;
- împrumutul și returnarea cărților;
- listarea cărților și verificarea disponibilității.

Este utilă pentru o bibliotecă personală sau o bibliotecă mică, unde vrei să ții evidența împrumuturilor într-un mod simplu.

## Tehnologii folosite

- **Limbaj:** C++
- **Biblioteci:**
  - STL (vector, string, fstream) – gestionare liste în memorie și fișiere CSV.
- **Tools:** Git, Docker, GitHub Actions.

## Cerințe sistem

- Compilator: g++ (versiune minimă recomandată 9.0).
- Sistem de operare: Windows / Linux / macOS.
- Dependențe externe:
  - Docker (opțional, pentru rulare în container).
  - Git (pentru clonarea repository-ului).

## Instalare

```bash
# Clone repository
git clone https://github.com/tebansergiu/Map-proiect.git
cd Map-proiect

# Build
g++ src/main.cpp -o library_manager
