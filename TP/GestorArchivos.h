#pragma once
#ifndef GESTORARCHIVOS_H
#define GESTORARCHIVOS_H
#include "Cliente.h"
#include <string>
#include <vector>

using namespace std;

class GestorArchivos {
public:
    static Cliente* buscarClientePorDNI(const string& dni);

    static bool guardarNuevoCliente(const Cliente& nuevoCliente);
};

#endif 