#ifndef PEDIDO_H
#define PEDIDO_H
#include "Cliente.h"
#include "Producto.h"
#include "ListaEnlazada.h" 
#include <string>
#include <iostream>

using namespace std;

class Pedido {
private:
    Cliente* clienteAsociado;
    ListaEnlazada<Producto*> productos;
    double montoTotal;
    string estado;

public:
    Pedido(Cliente* cliente);
    void agregarProducto(Producto* producto);
    void mostrarPedido() const;
    void mostrarPedidoResumen() const;

    const ListaEnlazada<Producto*>& getProductos() const;
    double getTotal() const;
    Cliente* getCliente() const;
};

#endif 
