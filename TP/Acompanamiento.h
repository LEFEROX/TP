#pragma once
#ifndef ACOMPANAMIENTO_H
#define ACOMPANAMIENTO_H
#include "Producto.h"
using namespace std;

class Acompanamiento : public Producto {
private:
    string descripcion;

public:
    Acompanamiento(string nombre, double precio, string desc)
        : Producto(nombre, precio), descripcion(desc) {
    }

    void mostrarDetalles() const override {
        cout << "Acompanamiento: " << nombre << " (" << descripcion << ")" << endl;
        cout << "  Precio: S/ " << precioBase << endl;
    }
};

#endif 