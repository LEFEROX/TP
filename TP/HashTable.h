#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <vector>
#include <functional> 
#include "ListaEnlazada.h" 

using namespace std;

template<typename K, typename V>
class HashEntry {
public:
    K key;
    V value;
    HashEntry(K k, V v) : key(k), value(v) {}
};

template<typename K, typename V>
class HashTable {
private:
    int TAM;
    int cantidadElementos;
    vector<ListaEnlazada<HashEntry<K, V>*>*> tabla;

    int funcionHash(string clave) {
        unsigned long hash = 5381;
        for (char c : clave) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash % TAM;
    }

    int funcionHash(int clave) {
        return clave % TAM;
    }

public:
    HashTable(int tam = 101) : TAM(tam), cantidadElementos(0) {
        for (int i = 0; i < TAM; i++) {
            tabla.push_back(new ListaEnlazada<HashEntry<K, V>*>());
        }
    }

    ~HashTable() {
        for (auto lista : tabla) {
            delete lista;
        }
    }

    void insertar(K key, V value) {
        int pos = funcionHash(key);

        HashEntry<K, V>* nuevaEntrada = new HashEntry<K, V>(key, value);
        tabla[pos]->insertarAlFinal(nuevaEntrada);
        cantidadElementos++;
    }

    V buscar(K key) {
        int pos = funcionHash(key);
        ListaEnlazada<HashEntry<K, V>*>* lista = tabla[pos];

        vector<HashEntry<K, V>*> elementos = lista->obtenerTodos();

        for (auto entrada : elementos) {
            if (entrada->key == key) {
                return entrada->value;
            }
        }
        return nullptr;
    }

    void recorrer(function<void(V)> accion) {
        for (int i = 0; i < TAM; i++) {
            vector<HashEntry<K, V>*> elementos = tabla[i]->obtenerTodos();
            for (auto entrada : elementos) {
                accion(entrada->value);
            }
        }
    }

    int getCantidad() const { return cantidadElementos; }
};

#endif