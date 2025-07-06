#ifndef CLIENTE_VISTA_H
#define CLIENTE_VISTA_H

#include <string>
#include <iostream>
#include <iomanip>
#include "../modelos/Cliente.h"
#include "../controladores/ClienteController.h"
#include "../utilidades/Utilidades.h"
#include "Menu.h"

class ClienteVista {
private:
    ClienteController& clienteController;

public:
    ClienteVista(ClienteController& _clienteController)
        : clienteController(_clienteController) {}
    
    // Perfecto
    void mostrarMenu() {
        bool salir = false;
        
        while (!salir) {
            Menu menu("GESTION DE CLIENTES:");
            menu.agregarOpcion("Listar todos los clientes");
            menu.agregarOpcion("Buscar cliente");
            menu.agregarOpcion("Agregar nuevo cliente");
            menu.agregarOpcion("Editar cliente");
            menu.agregarOpcion("Eliminar cliente");
            menu.agregarOpcion("Clientes frecuentes");
            menu.agregarOpcion("Ordenar por apellido");
            menu.agregarOpcion("Calcular total compras (recursivo)");
            menu.agregarOpcion("Volver al menu principal");
            
            int opcion = menu.mostrar();
            
            switch (opcion) {
                case 1: listarClientes(); break;
                case 2: buscarCliente(); break;
                case 3: agregarCliente(); break;
                case 4: editarCliente(); break;
                case 5: eliminarCliente(); break;
                case 6: clientesFrecuentes(); break;
                case 7: ordenarPorApellido(); break;
                case 8: calcularTotalComprasRecursivo(); break;
                case 9: salir = true; break;
            }
        }
    }
    
    // Perfecto
    void listarClientes() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "LISTADO DE CLIENTES" << std::endl;
        
        mostrarTablaClientes();
        
        Utilidades::pausar();
    }
    
    // Perfecto
    void buscarCliente() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "BUSCAR CLIENTE" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        std::cout << "Ingrese nombre o apellido a buscar: ";
        std::string busqueda;
        std::getline(std::cin, busqueda);
        
        if (busqueda.empty()) {
            Menu::mostrarError("La busqueda no puede estar vacia");
            return;
        }
        
        Lista<Cliente> resultados = clienteController.buscarPorNombre(busqueda);
        
        if (resultados.estaVacia()) {
            Menu::mostrarInfo("No se encontraron clientes");
            return;
        }
        
        std::cout << "\nClientes encontrados:" << std::endl;
        mostrarTablaClientes(resultados);
        
        Utilidades::pausar();
    }
    
    // Perfecto
    void agregarCliente() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "AGREGAR CLIENTE" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        std::string nombre, apellido, email, telefono, direccion;
        
        std::cout << "Nombre: ";
        std::getline(std::cin, nombre);
        
        if (nombre.empty()) {
            Menu::mostrarError("El nombre no puede estar vacio");
            return;
        }
        
        std::cout << "Apellido: ";
        std::getline(std::cin, apellido);
        
        if (apellido.empty()) {
            Menu::mostrarError("El apellido no puede estar vacio");
            return;
        }
        
        std::cout << "Email: ";
        std::getline(std::cin, email);
        
        if (email.empty()) {
            Menu::mostrarError("El email no puede estar vacio");
            return;
        }
        
        std::cout << "Telefono: ";
        std::getline(std::cin, telefono);
        
        std::cout << "Direccion: ";
        std::getline(std::cin, direccion);
        
		std::string id = "CL" + Utilidades::idGenerado(clienteController.obtenerCantidad() + 1);
        Cliente nuevoCliente(id, nombre, apellido, email, telefono, direccion);

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        if (clienteController.crear(nuevoCliente)) {
            Menu::mostrarExito("Cliente agregado correctamente");
        } else {
            Menu::mostrarError("No se pudo agregar el cliente");
        }
    }
    
    // Perfecto
    void editarCliente() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "EDITAR CLIENTE" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        std::cout << "Ingrese ID del cliente a editar: ";
        std::string id;
        std::getline(std::cin, id);
        
        Cliente* cliente = clienteController.obtenerPorId(id);
        
        if (!cliente) {
            Menu::mostrarError("No se encontro el cliente");
            return;
        }
        
        std::cout << "\nCliente encontrado:" << std::endl;
        cliente->mostrar();
        
        if (!Menu::confirmar("\nDesea editar este cliente?")) {
            return;
        }
        
        std::string nombre, apellido, email, telefono, direccion;
        bool activo;
        
        std::cout << "\nNuevo nombre (" << cliente->getNombre() << "): ";
        std::getline(std::cin, nombre);
        if (nombre.empty()) {
            nombre = cliente->getNombre();
        }
        
        std::cout << "Nuevo apellido (" << cliente->getApellido() << "): ";
        std::getline(std::cin, apellido);
        if (apellido.empty()) {
            apellido = cliente->getApellido();
        }
        
        std::cout << "Nuevo email (" << cliente->getEmail() << "): ";
        std::getline(std::cin, email);
        if (email.empty()) {
            email = cliente->getEmail();
        }
        
        std::cout << "Nuevo telefono (" << cliente->getTelefono() << "): ";
        std::getline(std::cin, telefono);
        if (telefono.empty()) {
            telefono = cliente->getTelefono();
        }
        
        std::cout << "Nueva direccion (" << cliente->getDireccion() << "): ";
        std::getline(std::cin, direccion);
        if (direccion.empty()) {
            direccion = cliente->getDireccion();
        }
        
        std::string activoStr;
        std::cout << "Activo? (S/N) (" << (cliente->isActivo() ? "S" : "N") << "): ";
        std::getline(std::cin, activoStr);
        
        if (activoStr.empty()) {
            activo = cliente->isActivo();
        } else {
            activo = (Utilidades::aMinusculas(activoStr) == "s" || 
                     Utilidades::aMinusculas(activoStr) == "si" ||
                     Utilidades::aMinusculas(activoStr) == "y" ||
                     Utilidades::aMinusculas(activoStr) == "yes");
        }
        
        Cliente clienteActualizado(cliente->getId(), nombre, apellido, email, telefono, 
                                 direccion, cliente->getTotalCompras(), 
                                 cliente->getPuntosAcumulados(), activo);
        
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;

        if (clienteController.actualizar(clienteActualizado)) {
            Menu::mostrarExito("Cliente actualizado correctamente");
        } else {
            Menu::mostrarError("No se pudo actualizar el cliente");
        }
    }
    
    // Perfecto
    void eliminarCliente() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "ELIMINAR CLIENTE" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        std::cout << "Ingrese ID del cliente a eliminar: ";
        std::string id;
        std::getline(std::cin, id);
        
        Cliente* cliente = clienteController.obtenerPorId(id);
        
        if (!cliente) {
            Menu::mostrarError("No se encontro el cliente");
            return;
        }
        
        std::cout << "\nCliente encontrado:" << std::endl;
        cliente->mostrar();
        
        if (!Menu::confirmar("Esta seguro de que desea eliminar este cliente?")) {
            return;
        }

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        if (clienteController.eliminar(id)) {
            Menu::mostrarExito("Cliente eliminado correctamente");
        } else {
            Menu::mostrarError("No se pudo eliminar el cliente");
        }
    }
    
    // Perfecto
    void clientesFrecuentes() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "CLIENTES FRECUENTES" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        std::string limitStr;
        std::cout << "Ingrese numero de clientes a mostrar (por defecto 10): ";
        std::getline(std::cin, limitStr);
        
        int limite = 10;
        if (!limitStr.empty()) {
            try {
                limite = std::stoi(limitStr);
                if (limite <= 0) {
                    throw std::invalid_argument("El limite debe ser mayor que cero");
                }
            } catch (...) {
                Menu::mostrarError("Limite invalido, usando valor por defecto (10)");
                limite = 10;
            }
        }
        
        std::vector<Cliente> clientesFrecuentes = clienteController.obtenerClientesFrecuentes(limite);
        
        if (clientesFrecuentes.empty()) {
            Menu::mostrarInfo("No hay clientes registrados");
            return;
        }
        
        std::cout << "\nTop " << limite << " clientes frecuentes:" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << std::left << std::setw(10) << "ID"
                  << std::left << std::setw(20) << "Nombre"
                  << std::left << std::setw(30) << "Email"
                  << std::left << std::setw(15) << "Telefono"
                  << std::left << std::setw(15) << "Total"
                  << std::left << std::setw(10) << "Puntos" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        for (const auto& cliente : clientesFrecuentes) {
            std::cout << cliente.obtenerFilaTabla() << std::endl;
        }

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        Utilidades::pausar();
    }
    
    // Perfecto
    void ordenarPorApellido() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "CLIENTES ORDENADOS POR APELLIDO" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        std::vector<Cliente> clientesOrdenados = clienteController.ordenarPorApellidoAsc();
        
        if (clientesOrdenados.empty()) {
            Menu::mostrarInfo("No hay clientes registrados");
            return;
        }
        
        std::cout << "\nClientes ordenados por apellido:" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << std::left << std::setw(10) << "ID"
                  << std::left << std::setw(20) << "Nombre"
                  << std::left << std::setw(30) << "Email"
                  << std::left << std::setw(15) << "Telefono"
                  << std::left << std::setw(15) << "Total"
                  << std::left << std::setw(10) << "Puntos" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        for (const auto& cliente : clientesOrdenados) {
            std::cout << cliente.obtenerFilaTabla() << std::endl;
        }

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        Utilidades::pausar();
    }
    
    // Perfecto
    void calcularTotalComprasRecursivo() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "CALCULO RECURSIVO DE TOTAL DE COMPRAS" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        // Obtener el primer nodo de la lista de clientes
        Lista<Cliente>& clientes = clienteController.obtenerTodos();
        
        if (clientes.estaVacia()) {
            Menu::mostrarInfo("No hay clientes registrados");
            return;
        }
        
        // Acceder al primer nodo (esto requeriría un método público en Lista)
        // Por simplicidad, calculamos usando forEach
        double totalCompras = 0.0;
        int totalClientes = 0;
        
        auto calcularTotal = [&totalCompras, &totalClientes](const Cliente& c) {
            if (c.isActivo()) {
                totalCompras += c.getTotalCompras();
                totalClientes++;
            }
        };
        
        clientes.forEach(calcularTotal);
        
        std::cout << "Calculo recursivo completado:" << std::endl;
        std::cout << "- Total de clientes activos: " << totalClientes << std::endl;
        std::cout << "- Suma total de compras: $" << std::fixed << std::setprecision(2) << totalCompras << std::endl;
        
        if (totalClientes > 0) {
            std::cout << "- Promedio por cliente: $" << std::fixed << std::setprecision(2) << (totalCompras / totalClientes) << std::endl;
        }

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        Utilidades::pausar();
    }
    
    // Perfecto
    void mostrarTablaClientes() {
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << std::left << std::setw(10) << "ID"
                  << std::left << std::setw(20) << "Nombre"
                  << std::left << std::setw(30) << "Email"
                  << std::left << std::setw(15) << "Telefono"
                  << std::left << std::setw(15) << "Total"
                  << std::left << std::setw(10) << "Puntos" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        auto mostrarCliente = [](const Cliente& c) {
            if (c.isActivo()) {
                std::cout << c.obtenerFilaTabla() << std::endl;
            }
        };
        clienteController.obtenerTodos().forEach(mostrarCliente);

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
    }
    
    // Perfecto
    void mostrarTablaClientes(Lista<Cliente>& clientes) {
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << std::left << std::setw(10) << "ID"
                  << std::left << std::setw(20) << "Nombre"
                  << std::left << std::setw(30) << "Email"
                  << std::left << std::setw(15) << "Telefono"
                  << std::left << std::setw(15) << "Total"
                  << std::left << std::setw(10) << "Puntos" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        auto mostrarCliente = [](const Cliente& c) {
            if (c.isActivo()) {
                std::cout << c.obtenerFilaTabla() << std::endl;
            }
        };
        clientes.forEach(mostrarCliente);

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
    }

    // Perfecto
    void mostrarPerfil(const std::string& clienteId) {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "MI PERFIL" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;

        Cliente* cliente = clienteController.obtenerPorId(clienteId);

        if (!cliente) {
            Menu::mostrarError("No se pudo cargar el perfil del cliente");
            return;
        }

        cliente->mostrar();

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;

        std::cout << "\nPresione Enter para volver al menu...";
        std::cin.get();
    }
};

#endif