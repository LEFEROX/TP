#include "Pedido.h" 
Pedido::Pedido(Cliente* cliente)
    : clienteAsociado(cliente), montoTotal(0.0), estado("En curso") {
}

void Pedido::agregarProducto(Producto* producto) {
    productos.insertarAlFinal(producto);
    montoTotal += producto->getPrecio();
}

void Pedido::mostrarPedido() const {
    if (productos.estaVacia()) {
        cout << "El carrito esta vacio." << endl;
    }
    else {
        productos.recorrerYMostrar();
    }
    cout << "---------------------------------------" << endl;
    cout << "TOTAL A PAGAR: S/ " << montoTotal << endl;
}

void Pedido::mostrarPedidoResumen() const {
    cout << "Pedido - Total: S/ " << montoTotal << endl;
}

const ListaEnlazada<Producto*>& Pedido::getProductos() const {
    return productos;
}

double Pedido::getTotal() const {
    return montoTotal;
}

Cliente* Pedido::getCliente() const {
    return clienteAsociado;
}
