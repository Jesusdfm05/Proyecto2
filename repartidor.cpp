#include "Repartidor.h"
#include <cstdlib>

using namespace std;

Repartidor::Repartidor() {
    strcpy(this->cedula, "");
    strcpy(this->nombre, "");
    strcpy(this->vehiculo, "");
    strcpy(this->placa, "");
    this->sector = 0;
    this->servicios = 0;
    this->disponible = true;
}

Repartidor::Repartidor(const char* cedula, const char* nombre, const char* vehiculo, const char* placa, int sector) {
    strncpy(this->cedula, cedula, 9); this->cedula[9] = '\0';
    strncpy(this->nombre, nombre, 29); this->nombre[29] = '\0';
    strncpy(this->vehiculo, vehiculo, 19); this->vehiculo[19] = '\0';
    strncpy(this->placa, placa, 9); this->placa[9] = '\0';
    this->sector = sector;
    this->servicios = 0;
    this->disponible = true;
}

const char* Repartidor::getCedula() const { return cedula; }
const char* Repartidor::getNombre() const { return nombre; }
const char* Repartidor::getVehiculo() const { return vehiculo; }
const char* Repartidor::getPlaca() const { return placa; }
int Repartidor::getSector() const { return sector; }
int Repartidor::getServicios() const { return servicios; }
bool Repartidor::isDisponible() const { return disponible; }

// --- LÓGICA DE NEGOCIO PASO 0.2 ---
bool Repartidor::despacharServicio() {
    if (!disponible) return false;
    disponible = false;
    return true;
}

bool Repartidor::finalizarEntrega(int sectorDestino) {
    if (disponible) return false; // Incoherencia: no se puede finalizar si no estaba en ruta
    disponible = true;
    sector = sectorDestino; // Se traslada al nuevo sector
    servicios++;            // Suma el envío completado
    return true;
}

// --- PERSISTENCIA EXPRESA DE TUS .TXT ---
bool Repartidor::cargarDesdeArchivo(ifstream& archivo) {
    if (!archivo.getline(this->cedula, 10, '|')) return false;
    if (strlen(this->cedula) == 0) return false;

    archivo.getline(this->nombre, 30, '|');
    archivo.getline(this->vehiculo, 20, '|');
    archivo.getline(this->placa, 10, '|');

    char secStr[10], servStr[10], dispStr[10];
    archivo.getline(secStr, 10, '|');
    archivo.getline(servStr, 10, '|');
    archivo.getline(dispStr, 10);

    this->sector = atoi(secStr);
    this->servicios = atoi(servStr);
    this->disponible = (atoi(dispStr) == 1);
    return true;
}

void Repartidor::guardarEnArchivo(ofstream& archivo) const {
    archivo << cedula << "|"
            << nombre << "|"
            << vehiculo << "|"
            << placa << "|"
            << sector << "|"
            << servicios << "|"
            << (disponible ? 1 : 0) << endl;
}

void Repartidor::mostrarInformacion() const {
    cout << "Cedula: " << cedula 
         << " | Nombre: " << nombre 
         << " | Vehiculo: " << vehiculo << " (" << placa << ")"
         << " | Sector: " << sector 
         << " | Estado: " << (disponible ? "DISPONIBLE" : "EN RUTA") 
         << " | Envios: " << servicios << endl;
}