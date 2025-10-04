#include "GestorArchivos.h"
#include <fstream> 
#include <sstream>  

using namespace std;

const string NOMBRE_ARCHIVO_CLIENTES = "clientes.txt";

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