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
        : clienteController(_clienteController) {
    }

    void mostrarMenu() {
        bool salir = false;

        while (!salir) {
            Menu menu("GESTION DE CLIENTES");
            menu.agregarOpcion("Listar todos los clientes");
            menu.agregarOpcion("Buscar cliente");
            menu.agregarOpcion("Agregar nuevo cliente");
            menu.agregarOpcion("Editar cliente");
            menu.agregarOpcion("Eliminar cliente");
            menu.agregarOpcion("Ver clientes frecuentes");
            menu.agregarOpcion("Ordenar por apellido");
            menu.agregarOpcion("Volver al menu principal");

            int opcion = menu.mostrar();

            switch (opcion) {
            case 1:
                listarClientes();
                break;
            case 2:
                buscarCliente();
                break;
            case 3:
                agregarCliente();
                break;
            case 4:
                editarCliente();
                break;
            case 5:
                eliminarCliente();
                break;
            case 6:
                verClientesFrecuentes();
                break;
            case 7:
                ordenarPorApellido();
                break;
            case 8:
                salir = true;
                break;
            }
        }
    }

    void listarClientes() {
        Utilidades::limpiarPantalla();
        std::cout << "===== LISTADO DE CLIENTES =====" << std::endl;

        mostrarTablaClientes();

        Utilidades::pausar();
    }

    void buscarCliente() {
        Utilidades::limpiarPantalla();
        std::cout << "===== BUSCAR CLIENTE =====" << std::endl;

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

    void agregarCliente() {
        Utilidades::limpiarPantalla();
        std::cout << "===== AGREGAR CLIENTE =====" << std::endl;

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

        // Verificar si ya existe un cliente con ese email
        if (clienteController.obtenerPorEmail(email)) {
            Menu::mostrarError("Ya existe un cliente con ese email");
            return;
        }

        std::cout << "Telefono: ";
        std::getline(std::cin, telefono);

        std::cout << "Direccion: ";
        std::getline(std::cin, direccion);

        std::string id = "CL" + Utilidades::generarId().substr(0, 8);
        Cliente nuevoCliente(id, nombre, apellido, email, telefono, direccion);

        if (clienteController.crear(nuevoCliente)) {
            Menu::mostrarExito("Cliente agregado correctamente");
        }
        else {
            Menu::mostrarError("No se pudo agregar el cliente");
        }
    }

    void editarCliente() {
        Utilidades::limpiarPantalla();
        std::cout << "===== EDITAR CLIENTE =====" << std::endl;

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

        if (!Menu::confirmar("\n¿Desea editar este cliente?")) {
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
        else {
            // Verificar si ya existe otro cliente con ese email
            Cliente* existente = clienteController.obtenerPorEmail(email);
            if (existente && existente->getId() != cliente->getId()) {
                Menu::mostrarError("Ya existe un cliente con ese email");
                return;
            }
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
        std::cout << "¿Activo? (S/N) (" << (cliente->isActivo() ? "S" : "N") << "): ";
        std::getline(std::cin, activoStr);

        if (activoStr.empty()) {
            activo = cliente->isActivo();
        }
        else {
            activo = (Utilidades::aMinusculas(activoStr) == "s" ||
                Utilidades::aMinusculas(activoStr) == "si" ||
                Utilidades::aMinusculas(activoStr) == "y" ||
                Utilidades::aMinusculas(activoStr) == "yes");
        }

        Cliente clienteActualizado(cliente->getId(), nombre, apellido, email,
            telefono, direccion, cliente->getTotalCompras(),
            cliente->getPuntosAcumulados(), activo);

        if (clienteController.actualizar(clienteActualizado)) {
            Menu::mostrarExito("Cliente actualizado correctamente");
        }
        else {
            Menu::mostrarError("No se pudo actualizar el cliente");
        }
    }

    void eliminarCliente() {
        Utilidades::limpiarPantalla();
        std::cout << "===== ELIMINAR CLIENTE =====" << std::endl;

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

        if (!Menu::confirmar("\n¿Esta seguro de que desea eliminar este cliente?")) {
            return;
        }

        if (clienteController.eliminar(id)) {
            Menu::mostrarExito("Cliente eliminado correctamente");
        }
        else {
            Menu::mostrarError("No se pudo eliminar el cliente");
        }
    }

    void verClientesFrecuentes() {
        Utilidades::limpiarPantalla();
        std::cout << "===== CLIENTES FRECUENTES =====" << std::endl;

        std::cout << "Ingrese cantidad de clientes a mostrar: ";
        std::string cantidadStr;
        std::getline(std::cin, cantidadStr);

        int cantidad;
        try {
            cantidad = std::stoi(cantidadStr);
            if (cantidad <= 0) {
                throw std::invalid_argument("La cantidad debe ser mayor que cero");
            }
        }
        catch (const std::exception& e) {
            Menu::mostrarError("Cantidad invalida");
            return;
        }

        std::vector<Cliente> clientes = clienteController.obtenerClientesFrecuentes(cantidad);

        if (clientes.empty()) {
            Menu::mostrarInfo("No hay clientes registrados");
            return;
        }

        std::cout << "\nTop " << cantidad << " clientes por volumen de compras:" << std::endl;
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;
        std::cout << std::left << std::setw(5) << "ID"
            << std::left << std::setw(25) << "Nombre"
            << std::left << std::setw(25) << "Email"
            << std::left << std::setw(15) << "Telefono"
            << std::right << std::setw(10) << "Total"
            << std::right << std::setw(8) << "Puntos" << std::endl;
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;

        for (const auto& cliente : clientes) {
            std::cout << cliente.obtenerFilaTabla() << std::endl;
        }

        Utilidades::pausar();
    }

    void ordenarPorApellido() {
        Utilidades::limpiarPantalla();
        std::cout << "===== CLIENTES ORDENADOS POR APELLIDO =====" << std::endl;

        std::vector<Cliente> clientes = clienteController.ordenarPorApellidoAsc();

        if (clientes.empty()) {
            Menu::mostrarInfo("No hay clientes registrados");
            return;
        }

        std::cout << "\nClientes ordenados por apellido:" << std::endl;
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;
        std::cout << std::left << std::setw(5) << "ID"
            << std::left << std::setw(25) << "Nombre"
            << std::left << std::setw(25) << "Email"
            << std::left << std::setw(15) << "Telefono"
            << std::right << std::setw(10) << "Total"
            << std::right << std::setw(8) << "Puntos" << std::endl;
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;

        for (const auto& cliente : clientes) {
            std::cout << cliente.obtenerFilaTabla() << std::endl;
        }

        Utilidades::pausar();
    }

    void mostrarTablaClientes() {
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;
        std::cout << std::left << std::setw(5) << "ID"
            << std::left << std::setw(25) << "Nombre"
            << std::left << std::setw(25) << "Email"
            << std::left << std::setw(15) << "Telefono"
            << std::right << std::setw(10) << "Total"
            << std::right << std::setw(8) << "Puntos" << std::endl;
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;

        auto mostrarCliente = [](const Cliente& c) {
            if (c.isActivo()) {
                std::cout << c.obtenerFilaTabla() << std::endl;
            }
            };

        clienteController.obtenerTodos().forEach(mostrarCliente);
    }

    void mostrarTablaClientes(Lista<Cliente>& clientes) {
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;
        std::cout << std::left << std::setw(5) << "ID"
            << std::left << std::setw(25) << "Nombre"
            << std::left << std::setw(25) << "Email"
            << std::left << std::setw(15) << "Telefono"
            << std::right << std::setw(10) << "Total"
            << std::right << std::setw(8) << "Puntos" << std::endl;
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;

        auto mostrarCliente = [](const Cliente& c) {
            if (c.isActivo()) {
                std::cout << c.obtenerFilaTabla() << std::endl;
            }
            };

        clientes.forEach(mostrarCliente);
    }

    void mostrarPerfil(const std::string& clienteId) {
        Utilidades::limpiarPantalla();
        std::cout << "===== MI PERFIL =====" << std::endl;

        Cliente* cliente = clienteController.obtenerPorId(clienteId);
        if (!cliente) {
            Menu::mostrarError("No se pudo cargar la informacion del perfil");
            return;
        }

        std::cout << "\nInformacion Personal:" << std::endl;
        std::cout << "Nombre: " << cliente->getNombreCompleto() << std::endl;
        std::cout << "Email: " << cliente->getEmail() << std::endl;
        std::cout << "Telefono: " << cliente->getTelefono() << std::endl;
        std::cout << "Direccion: " << cliente->getDireccion() << std::endl;
        std::cout << "\nEstadisticas de Compra:" << std::endl;
        std::cout << "Total de compras: $" << std::fixed << std::setprecision(2) << cliente->getTotalCompras() << std::endl;
        std::cout << "Puntos acumulados: " << cliente->getPuntosAcumulados() << std::endl;

        Utilidades::pausar();
    }
};

#endif
