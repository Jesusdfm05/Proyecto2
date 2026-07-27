#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <fstream>
#include <cstring>

class Cliente {
private:
    char cedula[10];
    char telefono[15];
    char nombre[30];
    int servicios;

public:
    Cliente();
    Cliente(const char* cedula, const char* telefono, const char* nombre, int servicios = 0);

    // Getters y Setters
    const char* getCedula() const;
    const char* getTelefono() const;
    const char* getNombre() const;
    int getServicios() const;

    void setTelefono(const char* telefono);
    void setNombre(const char* nombre);
    void incrementarServicios();

    // Métodos de Persistencia (Lectura/Escritura)
    bool cargarDesdeArchivo(std::ifstream& archivo);
    void guardarEnArchivo(std::ofstream& archivo) const;
    void mostrarInformacion() const;
};

#endif