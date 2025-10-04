#pragma once
#include "Cliente.h"
#include <string>
#include <vector>
#ifndef MENUI_H
#define MENUI_H
using namespace std;

class Producto;

class MenuUI {
public:
    static int mostrarMenuPrincipal();

    static void mostrarCatalogo(const vector<Producto*>& catalogo);

    static string solicitarDNI();
    static Cliente solicitarDatosNuevoCliente();

    static void mostrarMensaje(const string& mensaje);
};

#endif 