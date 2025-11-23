#include "AppManager.h"
#include "MenuUI.h"
#include "GestorArchivos.h"
#include "Pedido.h"
#include "Pizza.h"
#include "Bebida.h"
#include "Acompanamiento.h"
#include "Combo.h"
#include "Factura.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// ====================================================
// =============== QUICK SORT INTEGRADO ===============
// ====================================================

void quickSort(vector<Producto*>& arr, int left, int right) {
    if (left >= right) return;

    double pivot = arr[(left + right) / 2]->getPrecio();
    int i = left;
    int j = right;

    while (i <= j) {
        while (arr[i]->getPrecio() < pivot) i++;
        while (arr[j]->getPrecio() > pivot) j--;

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (left < j) quickSort(arr, left, j);
    if (i < right) quickSort(arr, i, right);
}

void ordenarCatalogoPorPrecio_QuickSort(vector<Producto*>& arr) {
    if (!arr.empty()) {
        quickSort(arr, 0, arr.size() - 1);
    }
}

// ====================================================
// ================= FIN QUICK SORT ===================
// ====================================================


AppManager::AppManager() : enEjecucion(false), clienteActual(nullptr) {
    tablaClientes = new HashTable<string, Cliente*>(101);

    inicializarCatalogo();
    cargarDatosIniciales(); 
}

AppManager::~AppManager() {
    clienteActual = nullptr;

    for (Producto* p : catalogoProductos) {
        delete p;
    }
    catalogoProductos.clear();

    if (tablaClientes) {
        tablaClientes->recorrer([](Cliente* c) {
            delete c;
        });
        delete tablaClientes; 
    }
}

void AppManager::iniciar() {
    enEjecucion = true;
    while (enEjecucion) {
        if (clienteActual == nullptr) {
            int opcion = MenuUI::mostrarMenuPrincipal();
            procesarOpcionMenuPrincipal(opcion);
        }
        else {
            bucleClienteLogueado();
        }
    }
}

void AppManager::cargarDatosIniciales() {
    GestorArchivos::cargarClientesEnHash(*tablaClientes);
    cout << "Sistema inicializado: Clientes cargados en memoria (Hash Table).\n";
}

void AppManager::bucleClienteLogueado() {
    int opcion = MenuUI::mostrarMenuCliente(clienteActual->getNombreCompleto());
    procesarOpcionMenuCliente(opcion);
}

void AppManager::procesarOpcionMenuPrincipal(int opcion) {
    switch (opcion) {
    case 1: procesarInicioSesion(); break;
    case 2: procesarRegistro(); break;
    case 3: procesarVerMenuConsulta(); break;
    case 4: procesarSalida(); break;
    default: MenuUI::pausar("Opcion no valida. Por favor, intente de nuevo."); break;
    }
}

void AppManager::procesarOpcionMenuCliente(int opcion) {
    switch (opcion) {
    case 1: procesarNuevoPedido(); break;
    case 2: clienteActual->mostrarHistorialPedidos(); MenuUI::pausar(""); break;
    case 3: procesarGestionarPerfil(); break;
    case 4: procesarCerrarSesion(); break;
    default: MenuUI::pausar("Opcion no valida."); break;
    }
}

void AppManager::procesarInicioSesion() {
    string dni = MenuUI::solicitarDNI();

    clienteActual = tablaClientes->buscar(dni);

    if (!clienteActual) {
        MenuUI::pausar("Error: Cliente no encontrado o DNI incorrecto.");
    }
    else {
        auto pedidosPrevios = GestorArchivos::cargarPedidosPorCliente(dni);

        for (auto p : pedidosPrevios) {
            clienteActual->agregarPedido(p);
        }
        MenuUI::pausar("Bienvenido de nuevo, " + clienteActual->getNombreCompleto());
    }
}

void AppManager::procesarRegistro() {
    Cliente nuevoCliente = MenuUI::solicitarDatosNuevoCliente();

    if (GestorArchivos::guardarNuevoCliente(nuevoCliente)) {

        Cliente* clienteMemoria = new Cliente(
            nuevoCliente.getDNI(),
            nuevoCliente.getNombreCompleto(),
            nuevoCliente.getDireccion(),
            nuevoCliente.getTelefono()
        );

        tablaClientes->insertar(clienteMemoria->getDNI(), clienteMemoria);

        MenuUI::pausar("¡Registro exitoso! Ahora puede iniciar sesion.");
    }
    else {
        MenuUI::pausar("Error: No se pudo completar el registro en el archivo.");
    }
}

void AppManager::procesarVerMenuConsulta() {
    ordenarCatalogoPorPrecio();
    MenuUI::mostrarCatalogo(catalogoProductos);
    MenuUI::pausar("");
}

void AppManager::procesarCerrarSesion() {
    MenuUI::pausar("Sesion cerrada. ¡Vuelva pronto, " + clienteActual->getNombreCompleto() + "!");
    clienteActual = nullptr; 
}

void AppManager::procesarSalida() {
    enEjecucion = false;
    MenuUI::pausar("Gracias por visitar Pizza Hut. ¡Vuelva pronto!");
}

void AppManager::procesarNuevoPedido() {
    Pedido* pedidoActual = new Pedido(clienteActual);
    bool finalizado = false;

    while (!finalizado) {
        MenuUI::mostrarCatalogo(catalogoProductos);
        cout << "\n--- SU CARRITO ACTUAL ---" << endl;
        pedidoActual->mostrarPedido();

        cout << "\n--- OPCIONES DE PEDIDO ---" << endl;
        cout << "Ingrese el # del producto para anadirlo." << endl;
        cout << "[F] Finalizar pedido." << endl;
        cout << "[X] Cancelar pedido." << endl;
        cout << "Su eleccion: ";

        string seleccion = MenuUI::leerEntrada();

        if (seleccion.empty()) {
            continue;
        }

        if (seleccion == "F" || seleccion == "f") {
            if (pedidoActual->getTotal() > 0) {
                finalizado = true;

                clienteActual->agregarPedido(pedidoActual);

                GestorArchivos::guardarPedido(*pedidoActual);

                Factura::generarBoleta(*pedidoActual);
                MenuUI::pausar("Pedido finalizado y enviado a la cocina. ¡Gracias!");
            }
            else {
                MenuUI::pausar("El carrito esta vacio. No se puede finalizar el pedido.");
            }
        }
        else if (seleccion == "X" || seleccion == "x") {
            MenuUI::pausar("Pedido cancelado.");
            delete pedidoActual;
            finalizado = true;
        }
        else {
            try {
                int indice = stoi(seleccion) - 1;
                if (indice >= 0 && indice < catalogoProductos.size()) {
                    pedidoActual->agregarProducto(catalogoProductos[indice]->clonar());
                }
                else {
                    MenuUI::pausar("Numero de producto fuera de rango.");
                }
            }
            catch (const exception&) {
                MenuUI::pausar("Entrada no valida. Por favor, ingrese un numero o una letra de opcion.");
            }
        }
    }
}

void AppManager::procesarGestionarPerfil() {
    bool salir = false;
    while (!salir) {
        limpiarPantalla();
        cout << "=======================================" << endl;
        cout << "      GESTIONAR PERFIL DE CLIENTE      " << endl;
        cout << "=======================================" << endl;
        cout << "Nombre: " << clienteActual->getNombreCompleto() << endl;
        cout << "DNI:    " << clienteActual->getDNI() << endl;
        cout << "Dir.:   " << clienteActual->getDireccion() << endl;
        cout << "Tel.:   " << clienteActual->getTelefono() << endl;
        cout << "---------------------------------------" << endl;
        cout << "1. Cambiar direccion" << endl;
        cout << "2. Cambiar telefono" << endl;
        cout << "3. Volver al menu cliente" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Seleccione una opcion: ";

        string opcion = MenuUI::leerEntrada();

        if (opcion == "1") {
            cout << "Nueva direccion: ";
            string nuevaDir = MenuUI::leerEntrada();
            clienteActual->setDireccion(nuevaDir);

            GestorArchivos::actualizarCliente(*clienteActual);

            MenuUI::pausar("Direccion actualizada correctamente.");
        }
        else if (opcion == "2") {
            cout << "Nuevo telefono: ";
            string nuevoTel = MenuUI::leerEntrada();
            clienteActual->setTelefono(nuevoTel);
            GestorArchivos::actualizarCliente(*clienteActual);
            MenuUI::pausar("Telefono actualizado correctamente.");
        }
        else if (opcion == "3") {
            salir = true;
        }
        else {
            MenuUI::pausar("Opcion no valida.");
        }
    }
}

void AppManager::inicializarCatalogo() {
    catalogoProductos.push_back(new Pizza("Pepperoni Lovers", 45.90, "Familiar", "Artesanal"));
    catalogoProductos.push_back(new Pizza("Hawaiana", 42.90, "Familiar", "Delgada"));
    catalogoProductos.push_back(new Pizza("Suprema", 55.90, "Familiar", "Artesanal"));
    catalogoProductos.push_back(new Bebida("Inca Kola", 7.50, 1500));
    catalogoProductos.push_back(new Bebida("Coca-Cola", 7.50, 1500));
    catalogoProductos.push_back(new Bebida("Agua San Mateo", 3.00, 600));
    catalogoProductos.push_back(new Acompanamiento("Pan al Ajo", 12.90, "Clasico"));
    catalogoProductos.push_back(new Acompanamiento("Alitas BBQ", 18.90, "8 unidades"));
    catalogoProductos.push_back(new Combo("Combo Personal", 25.90));

    int totalProductos = count_if(catalogoProductos.begin(), catalogoProductos.end(),
        [](Producto* p) { return p != nullptr; });

    cout << "Catalogo cargado con " << totalProductos << " productos.\n";
}

void AppManager::ordenarCatalogoPorPrecio() {
    ordenarCatalogoPorPrecio_QuickSort(catalogoProductos);
    cout << "Catalogo ordenado por precio (QuickSort recursivo).\n";
}
