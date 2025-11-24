#pragma once
#ifndef GENERADOR_DATASET_H
#define GENERADOR_DATASET_H

#include <string>
#include <vector>
#include "HashTable.h"
#include "Cliente.h"

class Producto;

class GeneradorDataSet {
public:

    static void generarClientesDemo(HashTable<std::string, Cliente*>& tablaClientes,
                                    int cantidad);


    static void generarPedidosDemo(HashTable<std::string, Cliente*>& tablaClientes,
                                   const std::vector<Producto*>& catalogo,
                                   int pedidosMinPorCliente,
                                   int pedidosMaxPorCliente);
};

#endif
