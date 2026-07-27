#ifndef SECTOR_H
#define SECTOR_H

#include <iostream>
#include <fstream>
#include <cstring>

class Sector {
private:
    int id;
    char direccion[20];

public:
    Sector();
    Sector(int id, const char* direccion);

    // Getters y Setters
    int getId() const;
    const char* getDireccion() const;
    void setId(int id);
    void setDireccion(const char* direccion);

    // Métodos de Persistencia (Lectura/Escritura)
    bool cargarDesdeArchivo(std::ifstream& archivo);
    void guardarEnArchivo(std::ofstream& archivo) const;
    void mostrarInformacion() const;
};

#endif