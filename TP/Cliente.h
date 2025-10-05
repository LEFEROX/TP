#pragma once
#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include "ListaEnlazada.h"

using namespace std;

class Pedido;

class Cliente {
private:
    string dni;
    string nombreCompleto;
    string direccion;
    string telefono;
    ListaEnlazada<Pedido*> historialPedidos;

public:
    Cliente(string dni, string nombre, string dir, string tel);
    ~Cliente();
    string getDNI() const;
    string getNombreCompleto() const;
    string getDireccion() const;
    string getTelefono() const;
    void setDireccion(const string& dir);
    void setTelefono(const string& tel);
    void agregarPedido(Pedido* pedido);
    void mostrarHistorialPedidos() const;
};

#endif
