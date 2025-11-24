#include "MenuUI.h"
#include "Producto.h"
#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <algorithm> 

using namespace std;

string MenuUI::leerEntrada() {
    string entrada;
    getline(cin, entrada);
    return entrada;
}

void limpiarPantalla() {
    system("cls");
}

int MenuUI::mostrarMenuPrincipal() {
    limpiarPantalla();
    cout << "=======================================" << endl;
    cout << "      BIENVENIDO A PIZZA HUT VIRTUAL   " << endl;
    cout << "=======================================" << endl;
    cout << "1. Iniciar Sesion" << endl;
    cout << "2. Registrar Nuevo Cliente" << endl;
    cout << "3. Ver Menu (Solo consulta)" << endl;
    cout << "4. Ver Clientes Registrados (Data set)" << endl;
    cout << "5. Salir" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Por favor, elija una opcion: ";

    try {
        return stoi(leerEntrada());
    }
    catch (const exception&) {
        return -1;
    }
}

int MenuUI::mostrarMenuCliente(const string& nombreCliente) {
    limpiarPantalla();
    cout << "=======================================" << endl;
    cout << "      Bienvenido, " << nombreCliente << "!" << endl;
    cout << "=======================================" << endl;
    cout << "1. Realizar Nuevo Pedido" << endl;
    cout << "2. Ver Historial de Pedidos" << endl;
    cout << "3. Gestionar Mi Perfil" << endl;
    cout << "4. Cerrar Sesion" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Por favor, elija una opcion: ";

    try {
        return stoi(leerEntrada());
    }
    catch (const exception&) {
        return -1;
    }
}

void MenuUI::pausar(const string& mensaje) {
    cout << endl << ">> " << mensaje << endl;
    cout << "Presione Enter para continuar...";
    leerEntrada();
}

string MenuUI::solicitarDNI() {
    limpiarPantalla();
    cout << "--- INICIO DE SESION ---" << endl;
    cout << "Ingrese su DNI: ";
    return leerEntrada();
}

Cliente MenuUI::solicitarDatosNuevoCliente() {
    limpiarPantalla();
    cout << "--- REGISTRO DE NUEVO CLIENTE ---" << endl;
    string dni, nombre, direccion, telefono;
    cout << "Ingrese DNI: ";
    dni = leerEntrada();
    cout << "Ingrese Nombre Completo: ";
    nombre = leerEntrada();
    cout << "Ingrese Direccion de Entrega: ";
    direccion = leerEntrada();
    cout << "Ingrese Telefono: ";
    telefono = leerEntrada();
    return Cliente(dni, nombre, direccion, telefono);
}

void MenuUI::mostrarCatalogo(const vector<Producto*>& catalogo) {
    int i = 1;
    limpiarPantalla();
    cout << "=======================================" << endl;
    cout << "        NUESTRO CATALOGO DE PRODUCTOS  " << endl;
    cout << "=======================================" << endl;

    if (catalogo.empty()) {
        cout << "El catalogo esta vacio por el momento." << endl;
    }
    else {
        vector<Producto*> copia = catalogo;
        sort(copia.begin(), copia.end(), [](Producto* a, Producto* b) {
            return a->getPrecio() < b->getPrecio();
            });

        sort(copia.begin(), copia.end(), [](Producto* a, Producto* b) {
            if (a->getPrecio() == b->getPrecio())
                return a->getNombre() < b->getNombre();
            return false;
            });

        for_each(copia.begin(), copia.end(), [&](Producto* p) {
            cout << "--- Producto #" << i++ << " ---" << endl;
            p->mostrarDetalles();
            });
    }
    cout << "=======================================" << endl;
}
