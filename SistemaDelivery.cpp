#include "SistemaDelivery.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

SistemaDelivery::SistemaDelivery() {
    contadorClientes = 0;
    contadorRepartidores = 0;
    contadorSectores = 0;
}

// --- CARGA Y GUARDADO DE ARCHIVOS ---
void SistemaDelivery::cargarClientes() {
    ifstream archivo("clientes.txt");
    if (!archivo.is_open()) return;
    contadorClientes = 0;
    while (!archivo.eof() && contadorClientes < MAX_CLIENTES) {
        if (!listaClientes[contadorClientes].cargarDesdeArchivo(archivo)) break;
        contadorClientes++;
    }
    archivo.close();
}

void SistemaDelivery::cargarRepartidores() {
    ifstream archivo("repartidores.txt");
    if (!archivo.is_open()) return;
    contadorRepartidores = 0;
    while (!archivo.eof() && contadorRepartidores < MAX_REPARTIDORES) {
        if (!listaRepartidores[contadorRepartidores].cargarDesdeArchivo(archivo)) break;
        contadorRepartidores++;
    }
    archivo.close();
}

void SistemaDelivery::cargarSectores() {
    ifstream archivo("sectores.txt");
    if (!archivo.is_open()) return;
    contadorSectores = 0;
    while (!archivo.eof() && contadorSectores < MAX_SECTORES) {
        if (!listaSectores[contadorSectores].cargarDesdeArchivo(archivo)) break;
        contadorSectores++;
    }
    archivo.close();
}

void SistemaDelivery::cargarTodo() {
    cargarClientes();
    cargarRepartidores();
    cargarSectores();
}

void SistemaDelivery::guardarClientes() {
    ofstream archivo("clientes.txt");
    if (!archivo.is_open()) return;
    for (int i = 0; i < contadorClientes; i++) {
        listaClientes[i].guardarEnArchivo(archivo);
    }
    archivo.close();
}

void SistemaDelivery::guardarRepartidores() {
    ofstream archivo("repartidores.txt");
    if (!archivo.is_open()) return;
    for (int i = 0; i < contadorRepartidores; i++) {
        listaRepartidores[i].guardarEnArchivo(archivo);
    }
    archivo.close();
}

void SistemaDelivery::guardarSectores() {
    ofstream archivo("sectores.txt");
    if (!archivo.is_open()) return;
    for (int i = 0; i < contadorSectores; i++) {
        listaSectores[i].guardarEnArchivo(archivo);
    }
    archivo.close();
}

void SistemaDelivery::guardarTodo() {
    guardarClientes();
    guardarRepartidores();
    guardarSectores();
}

// --- MÉTODOS DE REGISTRO (AUTÓNOMOS Y CORREGIDOS) ---
void SistemaDelivery::agregarCliente() {
    if (contadorClientes >= MAX_CLIENTES) {
        cout << "[ERROR] Limite de clientes alcanzado.\n";
        return;
    }
    
    char cedula[10];
    char telefono[15];
    char nombre[30];
    
    cout << "\n--- REGISTRAR CLIENTE ---\n";
    cout << "Cedula: "; cin >> cedula;
    cin.ignore(); // Limpiar el buffer de entrada
    cout << "Telefono: "; cin.getline(telefono, 15);
    cout << "Nombre: "; cin.getline(nombre, 30);

    listaClientes[contadorClientes] = Cliente(cedula, telefono, nombre);
    contadorClientes++;
    cout << "[OK] Cliente registrado exitosamente.\n";
}

void SistemaDelivery::agregarRepartidor() {
    if (contadorRepartidores >= MAX_REPARTIDORES) {
        cout << "[ERROR] Limite de repartidores alcanzado.\n";
        return;
    }

    char cedula[10], nombre[50], vehiculo[20], placa[10];
    
    cout << "\n--- REGISTRAR REPARTIDOR ---\n";
    cout << "Cedula: "; cin >> cedula;
    cin.ignore();
    cout << "Nombre: "; cin.getline(nombre, 50);
    cout << "Vehiculo: "; cin.getline(vehiculo, 20);
    cout << "Placa: "; cin.getline(placa, 10);

    listaRepartidores[contadorRepartidores] = Repartidor(cedula, nombre, vehiculo, placa, 0);
    contadorRepartidores++;
    cout << "[OK] Repartidor registrado exitosamente.\n";
}

void SistemaDelivery::agregarSector() {
    if (contadorSectores >= MAX_SECTORES) {
        cout << "[ERROR] Limite de sectores alcanzado.\n";
        return;
    }

    int id;
    char nombre[50];

    cout << "\n--- REGISTRAR SECTOR ---\n";
    cout << "ID del Sector: "; cin >> id;
    cin.ignore();
    cout << "Nombre del Sector: "; cin.getline(nombre, 50);

    listaSectores[contadorSectores] = Sector(id, nombre);
    contadorSectores++;
    cout << "[OK] Sector registrado exitosamente.\n";
}

// --- BÚSQUEDAS ---
int SistemaDelivery::buscarCliente(const char* cedula) {
    for (int i = 0; i < contadorClientes; i++) {
        if (strcmp(listaClientes[i].getCedula(), cedula) == 0) return i;
    }
    return -1;
}

int SistemaDelivery::buscarRepartidor(const char* cedula) {
    for (int i = 0; i < contadorRepartidores; i++) {
        if (strcmp(listaRepartidores[i].getCedula(), cedula) == 0) return i;
    }
    return -1;
}

int SistemaDelivery::buscarRepartidorDisponibleEnSector(int sectorId) {
    for (int i = 0; i < contadorRepartidores; i++) {
        if (listaRepartidores[i].getSector() == sectorId && listaRepartidores[i].isDisponible()) {
            return i;
        }
    }
    for (int i = 0; i < contadorRepartidores; i++) {
        if (listaRepartidores[i].isDisponible()) return i;
    }
    return -1;
}

// --- LÓGICA DE NEGOCIO Y SERVICIOS ---
void SistemaDelivery::iniciarJornada() {
    if (contadorSectores == 0 || contadorRepartidores == 0) {
        cout << "[!] Faltan sectores o repartidores cargados.\n";
        return;
    }
    srand(time(NULL));
    for (int i = 0; i < contadorRepartidores; i++) {
        int sectorAzar = listaSectores[rand() % contadorSectores].getId();
        listaRepartidores[i] = Repartidor(
            listaRepartidores[i].getCedula(),
            listaRepartidores[i].getNombre(),
            listaRepartidores[i].getVehiculo(),
            listaRepartidores[i].getPlaca(),
            sectorAzar
        );
    }
    cout << "[OK] Jornada iniciada. Repartidores distribuidos aleatoriamente.\n";
}

void SistemaDelivery::solicitarEnvio() {
    char cedula[10];
    int sectorDestino;

    cout << "Cedula del Cliente: "; cin >> cedula;
    int posCliente = buscarCliente(cedula);
    if (posCliente == -1) {
        cout << "[ERROR] Cliente no registrado.\n";
        return;
    }

    cout << "ID Sector Destino: "; cin >> sectorDestino;
    int posRepartidor = buscarRepartidorDisponibleEnSector(sectorDestino);

    if (posRepartidor == -1) {
        cout << "[!] No hay repartidores disponibles en este momento.\n";
        return;
    }

    listaRepartidores[posRepartidor].despacharServicio();
    listaClientes[posCliente].incrementarServicios();

    cout << "\n========================================\n";
    cout << "        ENVIO ASIGNADO CON EXITO        \n";
    cout << "========================================\n";
    cout << "Cliente: " << listaClientes[posCliente].getNombre() << "\n";
    cout << "Repartidor Asignado: " << listaRepartidores[posRepartidor].getNombre() << "\n";
    cout << "Estado: EN RUTA\n";
    cout << "========================================\n\n";
}

void SistemaDelivery::finalizarEntrega() {
    char cedula[10];
    int sectorDestino;

    cout << "Cedula del Repartidor que finaliza: "; cin >> cedula;
    int posRepartidor = buscarRepartidor(cedula);

    if (posRepartidor == -1) {
        cout << "[ERROR] Repartidor no encontrado.\n";
        return;
    }

    if (listaRepartidores[posRepartidor].isDisponible()) {
        cout << "[!] El repartidor ya se encuentra disponible (no estaba en ruta).\n";
        return;
    }

    cout << "ID del Sector donde completo la entrega: "; cin >> sectorDestino;
    listaRepartidores[posRepartidor].finalizarEntrega(sectorDestino);

    cout << "[OK] Entrega finalizada. El repartidor " 
         << listaRepartidores[posRepartidor].getNombre() 
         << " ahora esta DISPONIBLE en el sector " << sectorDestino << ".\n";
}

void SistemaDelivery::generarReporteEstadisticas() {
    ofstream archivo("reporte_estadisticas.txt");
    if (!archivo.is_open()) return;

    archivo << "=== REPORTE DE ESTADISTICAS DEL SISTEMA ===\n\n";
    archivo << "-- REPARTIDORES --\n";
    for (int i = 0; i < contadorRepartidores; i++) {
        archivo << "Nombre: " << listaRepartidores[i].getNombre()
                << " | Envios: " << listaRepartidores[i].getServicios() << "\n";
    }

    archivo << "\n-- CLIENTES --\n";
    for (int i = 0; i < contadorClientes; i++) {
        archivo << "Nombre: " << listaClientes[i].getNombre()
                << " | Envios solicitados: " << listaClientes[i].getServicios() << "\n";
    }

    archivo.close();
    cout << "[OK] Reporte 'reporte_estadisticas.txt' generado exitosamente.\n";
}

// --- MENÚS ---
void SistemaDelivery::menuGestionInterna() {
    int opcion;
    do {
        cout << "\n--- GESTION INTERNA ---\n"
             << "1. Registrar Cliente\n"
             << "2. Registrar Repartidor\n"
             << "3. Registrar Sector\n"
             << "4. Listar Clientes\n"
             << "5. Listar Repartidores\n"
             << "6. Listar Sectores\n"
             << "0. Volver\n"
             << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: agregarCliente(); break;
            case 2: agregarRepartidor(); break;
            case 3: agregarSector(); break;
            case 4:
                for (int i = 0; i < contadorClientes; i++) listaClientes[i].mostrarInformacion();
                break;
            case 5:
                for (int i = 0; i < contadorRepartidores; i++) listaRepartidores[i].mostrarInformacion();
                break;
            case 6:
                for (int i = 0; i < contadorSectores; i++) listaSectores[i].mostrarInformacion();
                break;
        }
    } while (opcion != 0);
}

void SistemaDelivery::menuServicioDiario() {
    int opcion;
    do {
        cout << "\n--- SERVICIO DIARIO ---\n"
             << "1. Iniciar Jornada (Asignacion Aleatoria)\n"
             << "2. Solicitar Envios\n"
             << "3. Finalizar Entrega\n"
             << "4. Generar Reporte de Estadisticas\n"
             << "0. Volver\n"
             << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: iniciarJornada(); break;
            case 2: solicitarEnvio(); break;
            case 3: finalizarEntrega(); break;
            case 4: generarReporteEstadisticas(); break;
        }
    } while (opcion != 0);
}

void SistemaDelivery::iniciar() {
    cargarTodo();
    int opcion;
    do {
        cout << "\n=== SISTEMA DELIVERY ===\n"
             << "1. Gestion Interna\n"
             << "2. Servicio Diario\n"
             << "0. Salir y Guardar\n"
             << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) menuGestionInterna();
        else if (opcion == 2) menuServicioDiario();

    } while (opcion != 0);

    guardarTodo();
    cout << "[OK] Datos guardados. ¡Hasta luego!\n";
}