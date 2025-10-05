#pragma once
#ifndef PIZZA_H
#define PIZZA_H

#include "Producto.h"
#include "Ingrediente.h"
#include <vector>
#include <iostream>
using namespace std;

class Pizza : public Producto {
private:
    string tamano;
    string tipoMasa;
    vector<Ingrediente> ingredientesAdicionales;

public:
    Pizza(const string& nombre, double precio, const string& tamano, const string& masa)
        : Producto(nombre, precio), tamano(tamano), tipoMasa(masa) {
    }

    void agregarIngrediente(const Ingrediente& ingrediente) {
        ingredientesAdicionales.push_back(ingrediente);
    }

    void mostrarDetalles() const override {
        cout << "Pizza: " << nombre << " (" << tamano << ", Masa " << tipoMasa << ")" << endl;
        cout << "  Precio Base: S/ " << precioBase << endl;
    }

    Producto* clonar() const override {
        return new Pizza(*this);
    }
};

#endif
