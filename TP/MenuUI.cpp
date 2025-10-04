#include "MenuUI.h"
#include "Producto.h" 
#include <iostream>
#include <limits>
#include <cstdlib>
using namespace std;

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
    cout << "4. Salir" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Por favor, elija una opcion: ";

    int opcion;
    cin >> opcion;

    while (cin.fail()) {
        cout << "Entrada invalida. Por favor, ingrese un numero." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Por favor, elija una opcion: ";
        cin >> opcion;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return opcion;
}

string MenuUI::solicitarDNI() {
    limpiarPantalla();
    cout << "--- INICIO DE SESION ---" << endl;
    cout << "Ingrese su DNI: ";
    string dni;
    getline(cin, dni);
    return dni;
}

Cliente MenuUI::solicitarDatosNuevoCliente() {
    limpiarPantalla();
    cout << "--- REGISTRO DE NUEVO CLIENTE ---" << endl;
    string dni, nombre, direccion, telefono;

    cout << "Ingrese DNI: ";
    getline(cin, dni);
    cout << "Ingrese Nombre Completo: ";
    getline(cin, nombre);
    cout << "Ingrese Direccion de Entrega: ";
    getline(cin, direccion);
    cout << "Ingrese Telefono: ";
    getline(cin, telefono);

    return Cliente(dni, nombre, direccion, telefono);
}

void MenuUI::mostrarMensaje(const string& mensaje) {
    cout << endl << ">> " << mensaje << endl;
    cout << "Presione Enter para continuar...";
    cin.get();
}

void MenuUI::mostrarCatalogo(const vector<Producto*>& catalogo) {
    limpiarPantalla();
    cout << "=======================================" << endl;
    cout << "        NUESTRO CATALOGO DE PRODUCTOS  " << endl;
    cout << "=======================================" << endl;

    if (catalogo.empty()) {
        cout << "El catalogo esta vacio por el momento." << endl;
    }
    else {
        for (const Producto* p : catalogo) {
            p->mostrarDetalles();
            cout << "---------------------------------------" << endl;
        }
    }
}