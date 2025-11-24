cmake_minimum_required(VERSION 4.0)
project(TP)

set(CMAKE_CXX_STANDARD 14)

include_directories(TP)

add_executable(TP
        TP/Acompanamiento.h
        TP/AppManager.cpp
        TP/AppManager.h
        TP/Bebida.h
        TP/Cliente.cpp
        TP/Cliente.h
        TP/Combo.h
        TP/Factura.h
        TP/GestorArchivos.cpp
        TP/GestorArchivos.h
        TP/HashTable.h
        TP/Ingrediente.h
        TP/ListaEnlazada.h
        TP/MenuUI.cpp
        TP/MenuUI.h
        TP/Pedido.cpp
        TP/Pedido.h
        TP/Pizza.h
        TP/Producto.h
        TP/Source.cpp
        TP/GeneradorDataSet.h
        TP/GeneradorDataSet.cpp)
