#pragma once
#ifndef MENUI_H
#define MENUI_H

#include "Cliente.h"
#include <string>
#include <vector>

using namespace std;

class Producto;
void limpiarPantalla();
class MenuUI {
public:
    static string leerEntrada();
    static int mostrarMenuPrincipal();
    static int mostrarMenuCliente(const string& nombreCliente);
    static void mostrarCatalogo(const vector<Producto*>& catalogo);
    static string solicitarDNI();
    static Cliente solicitarDatosNuevoCliente();
    static void pausar(const string& mensaje);
};

#endif