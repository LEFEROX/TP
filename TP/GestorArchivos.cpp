#include "GestorArchivos.h"
#include "Pedido.h"
#include "Producto.h"
#include "Acompanamiento.h" 
#include <fstream>
#include <sstream>

using namespace std;

const string NOMBRE_ARCHIVO_CLIENTES = "clientes.txt";
const string NOMBRE_ARCHIVO_PEDIDOS = "pedidos.txt";

Cliente* GestorArchivos::buscarClientePorDNI(const string& dniBuscado) {
    ifstream archivo(NOMBRE_ARCHIVO_CLIENTES);
    string linea;

    if (!archivo.is_open()) {
        return nullptr;
    }

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dni, nombre, direccion, telefono;

        getline(ss, dni, ',');
        getline(ss, nombre, ',');
        getline(ss, direccion, ',');
        getline(ss, telefono, ',');

        if (dni == dniBuscado) {
            archivo.close();
            return new Cliente(dni, nombre, direccion, telefono);
        }
    }

    archivo.close();
    return nullptr;
}

bool GestorArchivos::guardarNuevoCliente(const Cliente& nuevoCliente) {
    ofstream archivo(NOMBRE_ARCHIVO_CLIENTES, ios::app);
    if (!archivo.is_open()) {
        return false;
    }

    archivo << nuevoCliente.getDNI() << ","
        << nuevoCliente.getNombreCompleto() << ","
        << nuevoCliente.getDireccion() << ","
        << nuevoCliente.getTelefono() << endl;

    archivo.close();
    return true;
}

bool GestorArchivos::actualizarCliente(const Cliente& cliente) {
    ifstream archivoIn(NOMBRE_ARCHIVO_CLIENTES);
    if (!archivoIn.is_open()) return false;

    vector<string> lineas;
    string linea;

    while (getline(archivoIn, linea)) {
        stringstream ss(linea);
        string dni, nombre, direccion, telefono;
        getline(ss, dni, ',');
        getline(ss, nombre, ',');
        getline(ss, direccion, ',');
        getline(ss, telefono, ',');

        if (dni == cliente.getDNI()) {
            lineas.push_back(cliente.getDNI() + "," +
                cliente.getNombreCompleto() + "," +
                cliente.getDireccion() + "," +
                cliente.getTelefono());
        }
        else {
            lineas.push_back(linea);
        }
    }
    archivoIn.close();

    ofstream archivoOut(NOMBRE_ARCHIVO_CLIENTES, ios::trunc);
    if (!archivoOut.is_open()) return false;

    for (auto& l : lineas) {
        archivoOut << l << endl;
    }

    archivoOut.close();
    return true;
}

bool GestorArchivos::guardarPedido(const Pedido& pedido) {
    ofstream archivo(NOMBRE_ARCHIVO_PEDIDOS, ios::app);
    if (!archivo.is_open()) return false;

    archivo << pedido.getCliente()->getDNI() << ",";

    auto productos = pedido.getProductos().obtenerTodos();
    for (size_t i = 0; i < productos.size(); i++) {
        archivo << productos[i]->getNombre();
        if (i < productos.size() - 1) archivo << ";";
    }
    archivo << "," << pedido.getTotal() << endl;

    archivo.close();
    return true;
}

vector<Pedido*> GestorArchivos::cargarPedidosPorCliente(const string& dni) {
    ifstream archivo(NOMBRE_ARCHIVO_PEDIDOS);
    vector<Pedido*> pedidos;

    if (!archivo.is_open()) return pedidos;

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dniArchivo, productosStr, totalStr;

        getline(ss, dniArchivo, ',');
        getline(ss, productosStr, ',');
        getline(ss, totalStr, ',');

        if (dniArchivo == dni) {
            Pedido* nuevoPedido = new Pedido(nullptr);
            stringstream prodStream(productosStr);
            string prod;

            while (getline(prodStream, prod, ';')) {
                nuevoPedido->agregarProducto(new Acompanamiento(prod, 0.0, ""));
            }

            pedidos.push_back(nuevoPedido);
        }
    }
    archivo.close();
    return pedidos;
}
