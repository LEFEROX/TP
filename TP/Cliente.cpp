#include "Cliente.h"
#include "Pedido.h"
#include <iostream>

using namespace std;

Cliente::Cliente(string dni_, string nombre, string dir, string tel)
    : dni(dni_), nombreCompleto(nombre), direccion(dir), telefono(tel) {
}

Cliente::~Cliente() {
    auto pedidos = historialPedidos.obtenerTodos();
    for (auto p : pedidos) delete p;
}

string Cliente::getDNI() const { return dni; }
string Cliente::getNombreCompleto() const { return nombreCompleto; }
string Cliente::getDireccion() const { return direccion; }
string Cliente::getTelefono() const { return telefono; }

void Cliente::setDireccion(const string& dir) { direccion = dir; }
void Cliente::setTelefono(const string& tel) { telefono = tel; }

void Cliente::agregarPedido(Pedido* pedido) {
    historialPedidos.insertarAlFinal(pedido);
}

void Cliente::mostrarHistorialPedidos() const {
    auto pedidos = historialPedidos.obtenerTodos();  // ListaEnlazada -> vector

    if (pedidos.empty()) {
        cout << "No tiene pedidos registrados.\n";
        return;
    }

    cout << "\n--- HISTORIAL DE PEDIDOS ---\n";
    // Llamada inicial a la función recursiva
    mostrarHistorialPedidosRecursivo(pedidos, 0);
}

void Cliente::mostrarHistorialPedidosRecursivo(const vector<Pedido*>& pedidos, int indice) const {

    if (indice >= static_cast<int>(pedidos.size())) {
        return;
    }

    cout << indice + 1 << ". ";
    if (pedidos[indice]) {
        pedidos[indice]->mostrarPedidoResumen();
    }


    mostrarHistorialPedidosRecursivo(pedidos, indice + 1);
}
