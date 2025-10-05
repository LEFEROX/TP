#ifndef LISTAENLAZADA_HPP
#define LISTAENLAZADA_HPP
#include <iostream>
#include <vector>
#include "Producto.h"

using namespace std;

template<typename T>
class ListaEnlazada {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(T val) : dato(val), siguiente(nullptr) {}
    };

    Nodo* cabeza;

public:
    ListaEnlazada() : cabeza(nullptr) {}

    ~ListaEnlazada() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* aBorrar = actual;
            actual = actual->siguiente;
            delete aBorrar;
        }
    }

    void insertarAlFinal(T dato) {
        Nodo* nuevoNodo = new Nodo(dato);
        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
        }
        else {
            Nodo* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
    }

    bool estaVacia() const {
        return cabeza == nullptr;
    }

    void recorrerYMostrar() const;

    vector<T> obtenerTodos() const {
        vector<T> resultado;
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            resultado.push_back(actual->dato);
            actual = actual->siguiente;
        }
        return resultado;
    }
};

template<typename T>
void ListaEnlazada<T>::recorrerYMostrar() const {
    Nodo* actual = cabeza;
    int i = 1;
    while (actual != nullptr) {
        cout << i++ << ". " << actual->dato << endl;
        actual = actual->siguiente;
    }
}

template<>
inline void ListaEnlazada<Producto*>::recorrerYMostrar() const {
    Nodo* actual = cabeza;
    int i = 1;
    while (actual != nullptr) {
        cout << i++ << ". ";
        if (actual->dato) {
            actual->dato->mostrarDetalles();
        }
        actual = actual->siguiente;
    }
}

#endif
