#include "Sector.h"
#include <cstdlib>

using namespace std;

Sector::Sector() {
    this->id = 0;
    strcpy(this->direccion, "");
}

Sector::Sector(int id, const char* direccion) {
    this->id = id;
    strncpy(this->direccion, direccion, 19);
    this->direccion[19] = '\0';
}

int Sector::getId() const { return id; }
const char* Sector::getDireccion() const { return direccion; }

void Sector::setId(int id) { this->id = id; }
void Sector::setDireccion(const char* direccion) {
    strncpy(this->direccion, direccion, 19);
    this->direccion[19] = '\0';
}

bool Sector::cargarDesdeArchivo(ifstream& archivo) {
    char idStr[10];
    if (!archivo.getline(idStr, 10, '|')) return false;
    if (strlen(idStr) == 0) return false;

    this->id = atoi(idStr);
    archivo.getline(this->direccion, 20);
    return true;
}

void Sector::guardarEnArchivo(ofstream& archivo) const {
    archivo << id << "|" << direccion << endl;
}

void Sector::mostrarInformacion() const {
    cout << "ID Sector: " << id << " | Direccion: " << direccion << endl;
}