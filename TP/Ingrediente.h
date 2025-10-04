#pragma once
#ifndef INGREDIENTE_H
#define INGREDIENTE_H
#include <string>
using namespace std;

class Ingrediente {
private:
    string nombre;
    double costoAdicional;

public:
    Ingrediente(string nombre, double costo) : nombre(nombre), costoAdicional(costo) {}

    string getNombre() const { return nombre; }
    double getCostoAdicional() const { return costoAdicional; }
};

#endif 