#pragma once
#ifndef FACTURA_H
#define FACTURA_H
#include "Pedido.h"         
#include "MenuUI.h" 
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>          

using namespace std;

class Factura {
public:
    static void generarBoleta(const Pedido& pedido) {
        limpiarPantalla();

        Cliente* cliente = pedido.getCliente();

        const ListaEnlazada<Producto*>& listaProductos = pedido.getProductos();
        vector<Producto*> productos = listaProductos.obtenerTodos();

        cout << "+----------------------------------------------------+" << endl;
        cout << "|                 BOLETA DE VENTA                    |" << endl;
        cout << "+----------------------------------------------------+" << endl;
        if (cliente) {
            cout << "| Cliente: " << left << setw(40) << cliente->getNombreCompleto() << "|" << endl;
            cout << "| DNI:     " << left << setw(40) << cliente->getDNI() << "|" << endl;
        }
        cout << "+----------------------------------------------------+" << endl;
        cout << "| CANT | DESCRIPCION               | P. UNIT | TOTAL  |" << endl;
        cout << "+----------------------------------------------------+" << endl;

        cout << fixed << setprecision(2);

        for (Producto* prod : productos) {
            string nombre = prod->getNombre();
            if (nombre.length() > 25) nombre = nombre.substr(0, 22) + "...";

            cout << "|  1   | " << left << setw(25) << nombre
                << "| S/ " << right << setw(6) << prod->getPrecio()
                << "| S/ " << right << setw(6) << prod->getPrecio() << " |" << endl;
        }

        cout << "+----------------------------------------------------+" << endl;
        cout << "|                                  TOTAL: | S/ " << right << setw(6) << pedido.getTotal() << " |" << endl;
        cout << "+----------------------------------------------------+" << endl;
        cout << "|      ¡Gracias por su compra en Pizza Hut!          |" << endl;
        cout << "+----------------------------------------------------+" << endl;
    }
};

#endif