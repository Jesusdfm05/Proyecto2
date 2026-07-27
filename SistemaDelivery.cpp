//g++ *.cpp -o main; .\main
#include "SistemaDelivery.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Funcion auxiliar para pausar y limpiar la salida en consola
static void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

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

// --- BUSQUEDAS ---
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

// --- METODOS DE REGISTRO CON VALIDACION DE DUPLICADOS ---
void SistemaDelivery::agregarCliente() {
    if (contadorClientes >= MAX_CLIENTES) {
        cout << "[ERROR] Limite maximo de clientes alcanzado.\n";
        pausar();
        return;
    }
    
    char cedula[10];
    char telefono[15];
    char nombre[30];
    
    cout << "\n--- REGISTRAR CLIENTE ---\n";
    cout << "Cedula: "; cin >> cedula;

    if (buscarCliente(cedula) != -1) {
        cout << "[ERROR] Ya existe un cliente registrado con esa cedula.\n";
        pausar();
        return;
    }

    cin.ignore();
    cout << "Telefono: "; cin.getline(telefono, 15);
    cout << "Nombre: "; cin.getline(nombre, 30);

    listaClientes[contadorClientes] = Cliente(cedula, telefono, nombre);
    contadorClientes++;
    cout << "[OK] Cliente registrado exitosamente.\n";
    pausar();
}

void SistemaDelivery::agregarRepartidor() {
    if (contadorRepartidores >= MAX_REPARTIDORES) {
        cout << "[ERROR] Limite maximo de repartidores alcanzado.\n";
        pausar();
        return;
    }

    char cedula[10], nombre[50], vehiculo[20], placa[10];
    
    cout << "\n--- REGISTRAR REPARTIDOR ---\n";
    cout << "Cedula: "; cin >> cedula;

    if (buscarRepartidor(cedula) != -1) {
        cout << "[ERROR] Ya existe un repartidor registrado con esa cedula.\n";
        pausar();
        return;
    }

    cin.ignore();
    cout << "Nombre: "; cin.getline(nombre, 50);
    cout << "Vehiculo: "; cin.getline(vehiculo, 20);
    cout << "Placa: "; cin.getline(placa, 10);

    listaRepartidores[contadorRepartidores] = Repartidor(cedula, nombre, vehiculo, placa, 0);
    contadorRepartidores++;
    cout << "[OK] Repartidor registrado exitosamente.\n";
    pausar();
}

void SistemaDelivery::agregarSector() {
    if (contadorSectores >= MAX_SECTORES) {
        cout << "[ERROR] Limite maximo de sectores alcanzado.\n";
        pausar();
        return;
    }

    int id;
    char nombre[50];

    cout << "\n--- REGISTRAR SECTOR ---\n";
    cout << "ID del Sector: "; cin >> id;

    for (int i = 0; i < contadorSectores; i++) {
        if (listaSectores[i].getId() == id) {
            cout << "[ERROR] Ya existe un sector con ese ID.\n";
            pausar();
            return;
        }
    }

    cin.ignore();
    cout << "Nombre del Sector: "; cin.getline(nombre, 50);

    listaSectores[contadorSectores] = Sector(id, nombre);
    contadorSectores++;
    cout << "[OK] Sector registrado exitosamente.\n";
    pausar();
}

// --- METODOS DE ELIMINACION ---
void SistemaDelivery::eliminarCliente() {
    if (contadorClientes == 0) {
        cout << "[!] No hay clientes registrados para eliminar.\n";
        pausar();
        return;
    }

    char cedula[10];
    cout << "\n--- ELIMINAR CLIENTE ---\n";
    cout << "Ingrese la cedula del cliente a eliminar: ";
    cin >> cedula;

    int pos = buscarCliente(cedula);
    if (pos == -1) {
        cout << "[ERROR] Cliente no encontrado.\n";
        pausar();
        return;
    }

    for (int i = pos; i < contadorClientes - 1; i++) {
        listaClientes[i] = listaClientes[i + 1];
    }
    contadorClientes--;
    cout << "[OK] Cliente eliminado del sistema.\n";
    pausar();
}

void SistemaDelivery::eliminarRepartidor() {
    if (contadorRepartidores == 0) {
        cout << "[!] No hay repartidores registrados para eliminar.\n";
        pausar();
        return;
    }

    char cedula[10];
    cout << "\n--- ELIMINAR REPARTIDOR (RENUNCIA/RETIRO) ---\n";
    cout << "Ingrese la cedula del repartidor a eliminar: ";
    cin >> cedula;

    int pos = buscarRepartidor(cedula);
    if (pos == -1) {
        cout << "[ERROR] Repartidor no encontrado.\n";
        pausar();
        return;
    }

    if (!listaRepartidores[pos].isDisponible()) {
        cout << "[ERROR] No se puede eliminar un repartidor que esta actualmente EN RUTA.\n";
        pausar();
        return;
    }

    for (int i = pos; i < contadorRepartidores - 1; i++) {
        listaRepartidores[i] = listaRepartidores[i + 1];
    }
    contadorRepartidores--;
    cout << "[OK] Repartidor eliminado del sistema.\n";
    pausar();
}

// --- LOGICA DE NEGOCIO Y SERVICIOS ---
void SistemaDelivery::iniciarJornada() {
    if (contadorSectores == 0 || contadorRepartidores == 0) {
        cout << "[!] Faltan sectores o repartidores cargados para iniciar jornada.\n";
        pausar();
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
    pausar();
}

void SistemaDelivery::solicitarEnvio() {
    if (contadorClientes == 0 || contadorRepartidores == 0) {
        cout << "[!] Se requieren clientes y repartidores registrados para procesar envios.\n";
        pausar();
        return;
    }

    char cedula[10];
    int sectorDestino;

    cout << "\n--- SOLICITAR ENVIO ---\n";
    cout << "Cedula del Cliente: "; cin >> cedula;
    int posCliente = buscarCliente(cedula);
    if (posCliente == -1) {
        cout << "[ERROR] Cliente no registrado.\n";
        pausar();
        return;
    }

    cout << "ID Sector Destino: "; cin >> sectorDestino;
    int posRepartidor = buscarRepartidorDisponibleEnSector(sectorDestino);

    if (posRepartidor == -1) {
        cout << "[!] No hay repartidores disponibles en este momento.\n";
        pausar();
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
    cout << "========================================\n";
    pausar();
}

void SistemaDelivery::finalizarEntrega() {
    if (contadorRepartidores == 0) {
        cout << "[!] No hay repartidores registrados.\n";
        pausar();
        return;
    }

    char cedula[10];
    int sectorDestino;

    cout << "\n--- FINALIZAR ENTREGA ---\n";
    cout << "Cedula del Repartidor que finaliza: "; cin >> cedula;
    int posRepartidor = buscarRepartidor(cedula);

    if (posRepartidor == -1) {
        cout << "[ERROR] Repartidor no encontrado.\n";
        pausar();
        return;
    }

    if (listaRepartidores[posRepartidor].isDisponible()) {
        cout << "[!] El repartidor ya se encuentra disponible (no esta en ruta).\n";
        pausar();
        return;
    }

    cout << "ID del Sector donde completo la entrega: "; cin >> sectorDestino;
    listaRepartidores[posRepartidor].finalizarEntrega(sectorDestino);

    cout << "[OK] Entrega finalizada. El repartidor " 
         << listaRepartidores[posRepartidor].getNombre() 
         << " ahora esta DISPONIBLE en el sector " << sectorDestino << ".\n";
    pausar();
}

void SistemaDelivery::generarReporteEstadisticas() {
    ofstream archivo("reporte_estadisticas.txt");
    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo crear el archivo de reporte.\n";
        pausar();
        return;
    }

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
    pausar();
}

// --- MENUS ---
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
             << "7. Eliminar Cliente\n"
             << "8. Eliminar Repartidor\n"
             << "0. Volver\n"
             << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: agregarCliente(); break;
            case 2: agregarRepartidor(); break;
            case 3: agregarSector(); break;
            case 4:
                cout << "\n--- LISTA DE CLIENTES ---\n";
                if (contadorClientes == 0) cout << "[!] No hay clientes registrados.\n";
                else for (int i = 0; i < contadorClientes; i++) listaClientes[i].mostrarInformacion();
                pausar();
                break;
            case 5:
                cout << "\n--- LISTA DE REPARTIDORES ---\n";
                if (contadorRepartidores == 0) cout << "[!] No hay repartidores registrados.\n";
                else for (int i = 0; i < contadorRepartidores; i++) listaRepartidores[i].mostrarInformacion();
                pausar();
                break;
            case 6:
                cout << "\n--- LISTA DE SECTORES ---\n";
                if (contadorSectores == 0) cout << "[!] No hay sectores registrados.\n";
                else for (int i = 0; i < contadorSectores; i++) listaSectores[i].mostrarInformacion();
                pausar();
                break;
            case 7: eliminarCliente(); break;
            case 8: eliminarRepartidor(); break;
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
    cout << "[OK] Datos guardados. Hasta luego!\n";
}