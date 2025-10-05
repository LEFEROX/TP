#pragma once
#ifndef BEBIDA_H
#define BEBIDA_H

#include "Producto.h"
#include <iostream>
using namespace std;

class Bebida : public Producto {
private:
    int volumenML;

public:
    Bebida(const string& nombre, double precio, int volumen)
        : Producto(nombre, precio), volumenML(volumen) {
    }

    void mostrarDetalles() const override {
        cout << "Bebida: " << nombre << " (" << volumenML << "ml)" << endl;
        cout << "  Precio: S/ " << precioBase << endl;
    }

    Producto* clonar() const override {
        return new Bebida(*this);
    }
};

#endif
