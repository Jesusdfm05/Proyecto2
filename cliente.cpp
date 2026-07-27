#include "Cliente.h"
#include <cstdlib>

using namespace std;

Cliente::Cliente() {
    strcpy(this->cedula, "");
    strcpy(this->telefono, "");
    strcpy(this->nombre, "");
    this->servicios = 0;
}

Cliente::Cliente(const char* cedula, const char* telefono, const char* nombre, int servicios) {
    strncpy(this->cedula, cedula, 9); this->cedula[9] = '\0';
    strncpy(this->telefono, telefono, 14); this->telefono[14] = '\0';
    strncpy(this->nombre, nombre, 29); this->nombre[29] = '\0';
    this->servicios = servicios;
}

const char* Cliente::getCedula() const { return cedula; }
const char* Cliente::getTelefono() const { return telefono; }
const char* Cliente::getNombre() const { return nombre; }
int Cliente::getServicios() const { return servicios; }

void Cliente::setTelefono(const char* telefono) {
    strncpy(this->telefono, telefono, 14); this->telefono[14] = '\0';
}

void Cliente::setNombre(const char* nombre) {
    strncpy(this->nombre, nombre, 29); this->nombre[29] = '\0';
}

void Cliente::incrementarServicios() { this->servicios++; }

bool Cliente::cargarDesdeArchivo(ifstream& archivo) {
    if (!archivo.getline(this->cedula, 10, '|')) return false;
    if (strlen(this->cedula) == 0) return false;

    archivo.getline(this->telefono, 15, '|');
    archivo.getline(this->nombre, 30, '|');

    char servStr[10];
    archivo.getline(servStr, 10);
    this->servicios = atoi(servStr);
    return true;
}

void Cliente::guardarEnArchivo(ofstream& archivo) const {
    archivo << cedula << "|" << telefono << "|" << nombre << "|" << servicios << endl;
}

void Cliente::mostrarInformacion() const {
    cout << "Cedula: " << cedula 
         << " | Nombre: " << nombre 
         << " | Telefono: " << telefono 
         << " | Envios solicitados: " << servicios << endl;
}