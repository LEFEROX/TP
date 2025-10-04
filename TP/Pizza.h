#pragma once
#ifndef PIZZA_H
#define PIZZA_H

#include "Producto.h"
#include "Ingrediente.h"
#include <vector>

using namespace std;

class Pizza : public Producto {
private:
    string tamano;
    string tipoMasa;
    vector<Ingrediente> ingredientesAdicionales;

public:
    Pizza(string nombre, double precio, string tamano, string masa)
        : Producto(nombre, precio), tamano(tamano), tipoMasa(masa) {
    }

    void agregarIngrediente(const Ingrediente& ingrediente) {
        ingredientesAdicionales.push_back(ingrediente);
    }

    void mostrarDetalles() const override {
        cout << "Pizza: " << nombre << " (" << tamano << ", Masa " << tipoMasa << ")" << endl;
        cout << "  Precio Base: S/ " << precioBase << endl;
    }
};

#endif 