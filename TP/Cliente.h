#pragma once
#include <string>
#include <vector>
#ifndef CLIENTE_H
#define CLIENTE_H
using namespace std;

class Pedido;

class Cliente {
private:
    string dni;
    string nombreCompleto;
    string direccion;
    string telefono;

public:
    Cliente(string dni, string nombre, string dir, string tel)
        : dni(dni), nombreCompleto(nombre), direccion(dir), telefono(tel) {
    }

    string getDNI() const { return dni; }
    string getNombreCompleto() const { return nombreCompleto; }
    string getDireccion() const { return direccion; }
    string getTelefono() const { return telefono; }

};

#endif 