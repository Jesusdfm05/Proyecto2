#ifndef REPARTIDOR_H
#define REPARTIDOR_H

#include <iostream>
#include <fstream>
#include <cstring>

class Repartidor {
private:
    char cedula[10];
    char nombre[30];
    char vehiculo[20];
    char placa[10];
    int sector;
    int servicios;
    bool disponible;

public:
    Repartidor();
    Repartidor(const char* cedula, const char* nombre, const char* vehiculo, const char* placa, int sector);

    // Getters
    const char* getCedula() const;
    const char* getNombre() const;
    const char* getVehiculo() const;
    const char* getPlaca() const;
    int getSector() const;
    int getServicios() const;
    bool isDisponible() const;

    // Lógica del Paso 0.2
    bool despacharServicio();
    bool finalizarEntrega(int sectorDestino);

    // Métodos de Persistencia (Lectura/Escritura)
    bool cargarDesdeArchivo(std::ifstream& archivo);
    void guardarEnArchivo(std::ofstream& archivo) const;
    void mostrarInformacion() const;
};

#endif