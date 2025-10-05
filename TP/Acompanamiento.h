#pragma once
#ifndef ACOMPANAMIENTO_H
#define ACOMPANAMIENTO_H

#include "Producto.h"
#include <iostream>
using namespace std;

class Acompanamiento : public Producto {
private:
    string descripcion;

public:
    Acompanamiento(const string& nombre, double precio, const string& desc)
        : Producto(nombre, precio), descripcion(desc) {
    }

    void mostrarDetalles() const override {
        cout << "Acompanamiento: " << nombre << " (" << descripcion << ")" << endl;
        cout << "  Precio: S/ " << precioBase << endl;
    }

    Producto* clonar() const override {
        return new Acompanamiento(*this);
    }
};

#endif
