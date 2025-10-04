#pragma once
#include <vector>
#include "Producto.h"
using namespace std;

class Pedido {
private:
    vector<Producto> productos;

public:
    void agregarProducto(const Producto& p);
    void mostrarPedido() const;
};