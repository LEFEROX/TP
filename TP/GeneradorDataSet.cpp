#include "GeneradorDataSet.h"
#include "GestorArchivos.h"
#include "Pedido.h"
#include "Producto.h"
#include <cstdlib>
#include <ctime>

using std::string;
using std::vector;

static bool yaSeed = false;
static void asegurarSeed() {
    if (!yaSeed) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        yaSeed = true;
    }
}

void GeneradorDataSet::generarClientesDemo(HashTable<string, Cliente*>& tablaClientes,
                                           int cantidad) {
    asegurarSeed();

    vector<string> nombres = { "Ana", "Bruno", "Carla", "Diego", "Elena",
                               "Fernando", "Gabriela", "Hugo", "Isabel" };
    vector<string> apellidos = { "Torres", "Lopez", "Diaz", "Gomez",
                                 "Rojas", "Perez", "Ramirez" };
    vector<string> calles = { "Av. Lima", "Calle Union", "Jr. Arequipa",
                              "Pasaje Los Olivos", "Av. Perú", "Av. Ejercito" };

    for (int i = 0; i < cantidad; ++i) {
        // DNI pseudo-aleatorio de 8 dígitos
        string dni = std::to_string(10000000 + std::rand() % 90000000);

        string nombre = nombres[std::rand() % nombres.size()] + " " +
                        apellidos[std::rand() % apellidos.size()];
        string direccion = calles[std::rand() % calles.size()] + " #" +
                           std::to_string(1 + std::rand() % 500);
        string telefono = "9" + std::to_string(10000000 + std::rand() % 90000000);


        Cliente* c = new Cliente(dni, nombre, direccion, telefono);


        tablaClientes.insertar(dni, c);


        GestorArchivos::guardarNuevoCliente(*c);
    }
}

void GeneradorDataSet::generarPedidosDemo(HashTable<string, Cliente*>& tablaClientes,
                                          const vector<Producto*>& catalogo,
                                          int pedidosMinPorCliente,
                                          int pedidosMaxPorCliente) {
    if (catalogo.empty()) return;
    asegurarSeed();

    tablaClientes.recorrer([&](Cliente* c) {
        int cantidadPedidos = pedidosMinPorCliente +
                              (std::rand() % (pedidosMaxPorCliente - pedidosMinPorCliente + 1));

        for (int k = 0; k < cantidadPedidos; ++k) {
            Pedido* p = new Pedido(c);

            int numProductos = 1 + std::rand() % 5; // 1 a 5 productos
            for (int n = 0; n < numProductos; ++n) {
                int idx = std::rand() % catalogo.size();
                p->agregarProducto(catalogo[idx]->clonar());
            }


            c->agregarPedido(p);


            GestorArchivos::guardarPedido(*p);
        }
    });
}
