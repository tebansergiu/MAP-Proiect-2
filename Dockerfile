# Imagine de bază cu compilator C++
FROM gcc:latest

# Directorul de lucru din container
WORKDIR /usr/src/app

# Copiem tot proiectul în container (cod + data)
COPY . .

# Compilăm aplicația
# Dacă fișierul tău principal este src/main.cpp, asta e suficient
RUN g++ -std=c++17 -O2 src/main.cpp -o library_manager

# Comanda implicită la pornirea containerului
# Poți schimba argumentele când rulezi `docker run`
CMD ["./library_manager", "list"]
