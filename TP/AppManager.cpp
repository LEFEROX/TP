#include "AppManager.h" 
#include "MenuUI.h"
#include "GestorArchivos.h"
#include <iostream>
#include "Pizza.h"
#include "Bebida.h"
#include "Acompanamiento.h"
#include "Combo.h"
using namespace std;

AppManager::AppManager() : enEjecucion(false), clienteActual(nullptr) {
    inicializarCatalogo();
}

AppManager::~AppManager() {
    delete clienteActual;
    clienteActual = nullptr;

    for (Producto* p : catalogoProductos) {
        delete p;
    }
    catalogoProductos.clear();

}

void AppManager::iniciar() {
    enEjecucion = true;
    while (enEjecucion) {
        if (clienteActual == nullptr) {
            int opcion = MenuUI::mostrarMenuPrincipal();
            procesarOpcionMenuPrincipal(opcion);
        }
        else {
            MenuUI::mostrarMensaje("Sesion cerrada para volver al menu principal.");
            delete clienteActual;
            clienteActual = nullptr;
        }
    }
}

void AppManager::procesarOpcionMenuPrincipal(int opcion) {
    switch (opcion) {
    case 1:
        procesarInicioSesion();
        break;
    case 2:
        procesarRegistro();
        break;
    case 3:
        procesarVerMenuConsulta();
        break;
    case 4:
        procesarSalida();
        break;
    default:
        MenuUI::mostrarMensaje("Opcion no valida. Por favor, intente de nuevo.");
        break;
    }
}

void AppManager::procesarInicioSesion() {
    string dni = MenuUI::solicitarDNI();
    clienteActual = GestorArchivos::buscarClientePorDNI(dni);

    if (clienteActual) {
        MenuUI::mostrarMensaje("Bienvenido de nuevo, " + clienteActual->getNombreCompleto());
    }
    else {
        MenuUI::mostrarMensaje("Error: Cliente no encontrado.");
    }
}

void AppManager::procesarRegistro() {
    Cliente nuevoCliente = MenuUI::solicitarDatosNuevoCliente();
    if (GestorArchivos::guardarNuevoCliente(nuevoCliente)) {
        MenuUI::mostrarMensaje("¡Registro exitoso! Ahora puede iniciar sesion.");
    }
    else {
        MenuUI::mostrarMensaje("Error: No se pudo completar el registro.");
    }
}

void AppManager::procesarVerMenuConsulta() {
    MenuUI::mostrarCatalogo(catalogoProductos);
    MenuUI::mostrarMensaje("Este es nuestro catalogo actual.");
}

void AppManager::procesarSalida() {
    enEjecucion = false;
    MenuUI::mostrarMensaje("Gracias por visitar Pizza Hut. ¡Vuelva pronto!");
}

void AppManager::inicializarCatalogo() {
    catalogoProductos.push_back(new Pizza("Pepperoni Lovers", 45.90, "Familiar", "Artesanal"));
    catalogoProductos.push_back(new Pizza("Hawaiana", 42.90, "Familiar", "Delgada"));
    catalogoProductos.push_back(new Pizza("Suprema", 55.90, "Familiar", "Artesanal"));
    catalogoProductos.push_back(new Bebida("Inca Kola", 7.50, 1500));
    catalogoProductos.push_back(new Bebida("Coca-Cola", 7.50, 1500));
    catalogoProductos.push_back(new Bebida("Agua San Mateo", 3.00, 600));
    catalogoProductos.push_back(new Acompanamiento("Pan al Ajo", 12.90, "Clasico"));
    catalogoProductos.push_back(new Acompanamiento("Alitas BBQ", 18.90, "8 unidades"));
    catalogoProductos.push_back(new Combo("Combo Personal", 25.90));
}