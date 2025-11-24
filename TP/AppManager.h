#pragma once
#ifndef APPMANAGER_H
#define APPMANAGER_H

#include "Cliente.h"
#include <vector>
#include <string>
#include "HashTable.h"

using namespace std;

class Producto; 

class AppManager {
private:
    bool enEjecucion;
    Cliente* clienteActual;
    vector<Producto*> catalogoProductos;
    HashTable<string, Cliente*>* tablaClientes; 
    void ordenarCatalogoPorPrecio();
    void ordenarCatalogoPorNombre();
    void procesarGestionarPerfil();
    void procesarOpcionMenuPrincipal(int opcion);
    void bucleClienteLogueado();
    void procesarOpcionMenuCliente(int opcion);
    void procesarInicioSesion();
    void procesarRegistro();
    void procesarVerMenuConsulta();
    void procesarNuevoPedido();
    void procesarCerrarSesion();
    void procesarSalida();
    void inicializarCatalogo();
    void cargarDatosIniciales();
    void procesarVerClientesRegistrados();

public:
    AppManager();
    ~AppManager();
    void iniciar();
};

#endif
