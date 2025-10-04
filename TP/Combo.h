#pragma once
#ifndef COMBO_H
#define COMBO_H
#include "Producto.h"
#include <vector>
using namespace std;

class Combo : public Producto {
private:
    vector<Producto*> productosIncluidos;

public:
    Combo(string nombre, double precio) : Producto(nombre, precio) {}

    ~Combo() {
    }

    void agregarProductoAlCombo(Producto* producto) {
        productosIncluidos.push_back(producto);
    }

    void mostrarDetalles() const override {
        cout << "Combo: " << nombre << " - Precio Total: S/ " << precioBase << endl;
        cout << "  Incluye:" << endl;
        for (const auto& producto : productosIncluidos) {
            cout << "  - " << producto->getNombre() << endl;
        }
    }
};

#endif 