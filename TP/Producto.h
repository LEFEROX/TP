#pragma once
#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>
#include <iostream>
using namespace std;

class Producto {
protected:
    string nombre;
    double precioBase;

public:
    Producto(string nombre, double precio) : nombre(nombre), precioBase(precio) {}

    virtual ~Producto() {}

    string getNombre() const { return nombre; }
    double getPrecio() const { return precioBase; }

    virtual void mostrarDetalles() const = 0;
};

#endif 