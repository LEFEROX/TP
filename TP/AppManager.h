#pragma once 
#ifndef APPMANAGER_H
#define APPMANAGER_H
#include "Cliente.h"   
#include "Producto.h"   
#include <vector>                   
using namespace std;

class AppManager {
private:
    bool enEjecucion;
    Cliente* clienteActual;

    vector<Producto*> catalogoProductos;

    class Pedido;
    template<typename T> class Cola;

    void procesarOpcionMenuPrincipal(int opcion);
    void procesarInicioSesion();
    void procesarRegistro();
    void procesarVerMenuConsulta();
    void procesarSalida();
    void inicializarCatalogo();

public:
    AppManager();
    ~AppManager();

    void iniciar();
};

#endif