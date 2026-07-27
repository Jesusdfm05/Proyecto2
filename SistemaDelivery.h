#ifndef SISTEMADELIVERY_H
#define SISTEMADELIVERY_H

#include "cliente.h"
#include "repartidor.h"
#include "sector.h"

const int MAX_CLIENTES = 100;
const int MAX_REPARTIDORES = 50;
const int MAX_SECTORES = 20;

class SistemaDelivery {
private:
    Cliente listaClientes[MAX_CLIENTES];
    int contadorClientes;

    Repartidor listaRepartidores[MAX_REPARTIDORES];
    int contadorRepartidores;

    Sector listaSectores[MAX_SECTORES];
    int contadorSectores;

    // Métodos privados de carga y guardado
    void cargarClientes();
    void cargarRepartidores();
    void cargarSectores();

    void guardarClientes();
    void guardarRepartidores();
    void guardarSectores();

    void agregarCliente();
    void agregarRepartidor();
    void agregarSector();

    // Métodos auxiliares de búsqueda
    int buscarCliente(const char* cedula);
    int buscarRepartidor(const char* cedula);
    int buscarRepartidorDisponibleEnSector(int sectorId);

public:
    SistemaDelivery();

    // Carga inicial y guardado
    void cargarTodo();
    void guardarTodo();
    void eliminarCliente();
    void eliminarRepartidor();

    // Flujo de menú y servicios
    void iniciarJornada();
    void solicitarEnvio();
    void finalizarEntrega(); // Corrección clave del Paso 0.2
    void generarReporteEstadisticas();

    // Menús
    void menuGestionInterna();
    void menuServicioDiario();
    void iniciar();
};

#endif