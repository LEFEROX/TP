#pragma once
#ifndef GESTORARCHIVOS_H
#define GESTORARCHIVOS_H
#include "Cliente.h"
#include "Pedido.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class GestorArchivos {
public:
    static Cliente* buscarClientePorDNI(const string& dni);
    static bool guardarNuevoCliente(const Cliente& nuevoCliente);
    static bool actualizarCliente(const Cliente& cliente);
    static bool guardarPedido(const Pedido& pedido);
    static vector<Pedido*> cargarPedidosPorCliente(const string& dni);

    static map<string, Cliente*> cargarClientesEnMapa();
};

#endif
