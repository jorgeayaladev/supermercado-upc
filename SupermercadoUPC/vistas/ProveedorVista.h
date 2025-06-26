#ifndef PROVEEDOR_VISTA_H
#define PROVEEDOR_VISTA_H

#include <string>
#include <iostream>
#include <iomanip>
#include "../modelos/Proveedor.h"
#include "../controladores/ProveedorController.h"
#include "../utilidades/Utilidades.h"
#include "Menu.h"

class ProveedorVista {
private:
    ProveedorController& proveedorController;

public:
    ProveedorVista(ProveedorController& _proveedorController)
        : proveedorController(_proveedorController) {}
    
    void mostrarMenu() {
        bool salir = false;
        
        while (!salir) {
            Menu menu("GESTION DE PROVEEDORES");
            menu.agregarOpcion("Listar todos los proveedores");
            menu.agregarOpcion("Buscar proveedor");
            menu.agregarOpcion("Agregar nuevo proveedor");
            menu.agregarOpcion("Editar proveedor");
            menu.agregarOpcion("Eliminar proveedor");
            menu.agregarOpcion("Listar por categoria");
            menu.agregarOpcion("Ordenar por nombre");
            menu.agregarOpcion("Volver al menu principal");
            
            int opcion = menu.mostrar();
            
            switch (opcion) {
                case 1:
                    listarProveedores();
                    break;
                case 2:
                    buscarProveedor();
                    break;
                case 3:
                    agregarProveedor();
                    break;
                case 4:
                    editarProveedor();
                    break;
                case 5:
                    eliminarProveedor();
                    break;
                case 6:
                    listarPorCategoria();
                    break;
                case 7:
                    ordenarPorNombre();
                    break;
                case 8:
                    salir = true;
                    break;
            }
        }
    }
    
    void listarProveedores() {
        Utilidades::limpiarPantalla();
        std::cout << "===== LISTADO DE PROVEEDORES =====" << std::endl;
        
        mostrarTablaProveedores();
        
        Utilidades::pausar();
    }
    
    void buscarProveedor() {
        Utilidades::limpiarPantalla();
        std::cout << "===== BUSCAR PROVEEDOR =====" << std::endl;
        
        std::cout << "Ingrese nombre a buscar: ";
        std::string busqueda;
        std::getline(std::cin, busqueda);
        
        if (busqueda.empty()) {
            Menu::mostrarError("La busqueda no puede estar vacia");
            return;
        }
        
        Lista<Proveedor> resultados = proveedorController.buscarPorNombre(busqueda);
        
        if (resultados.estaVacia()) {
            Menu::mostrarInfo("No se encontraron proveedores");
            return;
        }
        
        std::cout << "\nProveedores encontrados:" << std::endl;
        mostrarTablaProveedores(resultados);
        
        Utilidades::pausar();
    }
    
    void agregarProveedor() {
        Utilidades::limpiarPantalla();
        std::cout << "===== AGREGAR PROVEEDOR =====" << std::endl;
        
        std::string nombre, contacto, email, telefono, direccion;
        std::vector<std::string> categorias;
        
        std::cout << "Nombre: ";
        std::getline(std::cin, nombre);
        
        if (nombre.empty()) {
            Menu::mostrarError("El nombre no puede estar vacio");
            return;
        }
        
        std::cout << "Contacto: ";
        std::getline(std::cin, contacto);
        
        if (contacto.empty()) {
            Menu::mostrarError("El contacto no puede estar vacio");
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
        
        std::cout << "Categorias (separadas por coma): ";
        std::string categoriasStr;
        std::getline(std::cin, categoriasStr);
        
        if (!categoriasStr.empty()) {
            std::stringstream ss(categoriasStr);
            std::string categoria;
            while (std::getline(ss, categoria, ',')) {
                // Eliminar espacios en blanco
                categoria.erase(0, categoria.find_first_not_of(" "));
                categoria.erase(categoria.find_last_not_of(" ") + 1);
                if (!categoria.empty()) {
                    categorias.push_back(categoria);
                }
            }
        }
        
        if (categorias.empty()) {
            Menu::mostrarError("Debe especificar al menos una categoria");
            return;
        }
        
        std::string id = "PR" + Utilidades::generarId().substr(0, 8);
        Proveedor nuevoProveedor(id, nombre, contacto, email, telefono, direccion, categorias);
        
        if (proveedorController.crear(nuevoProveedor)) {
            Menu::mostrarExito("Proveedor agregado correctamente");
        } else {
            Menu::mostrarError("No se pudo agregar el proveedor");
        }
    }
    
    void editarProveedor() {
        Utilidades::limpiarPantalla();
        std::cout << "===== EDITAR PROVEEDOR =====" << std::endl;
        
        std::cout << "Ingrese ID del proveedor a editar: ";
        std::string id;
        std::getline(std::cin, id);
        
        Proveedor* proveedor = proveedorController.obtenerPorId(id);
        
        if (!proveedor) {
            Menu::mostrarError("No se encontro el proveedor");
            return;
        }
        
        std::cout << "\nProveedor encontrado:" << std::endl;
        proveedor->mostrar();
        
        if (!Menu::confirmar("\n¿Desea editar este proveedor?")) {
            return;
        }
        
        std::string nombre, contacto, email, telefono, direccion;
        std::vector<std::string> categorias;
        bool activo;
        
        std::cout << "\nNuevo nombre (" << proveedor->getNombre() << "): ";
        std::getline(std::cin, nombre);
        if (nombre.empty()) {
            nombre = proveedor->getNombre();
        }
        
        std::cout << "Nuevo contacto (" << proveedor->getContacto() << "): ";
        std::getline(std::cin, contacto);
        if (contacto.empty()) {
            contacto = proveedor->getContacto();
        }
        
        std::cout << "Nuevo email (" << proveedor->getEmail() << "): ";
        std::getline(std::cin, email);
        if (email.empty()) {
            email = proveedor->getEmail();
        }
        
        std::cout << "Nuevo telefono (" << proveedor->getTelefono() << "): ";
        std::getline(std::cin, telefono);
        if (telefono.empty()) {
            telefono = proveedor->getTelefono();
        }
        
        std::cout << "Nueva direccion (" << proveedor->getDireccion() << "): ";
        std::getline(std::cin, direccion);
        if (direccion.empty()) {
            direccion = proveedor->getDireccion();
        }
        
        std::cout << "Nuevas categorias (separadas por coma) (" << proveedor->getCategoriasString() << "): ";
        std::string categoriasStr;
        std::getline(std::cin, categoriasStr);
        
        if (categoriasStr.empty()) {
            categorias = proveedor->getCategorias();
        } else {
            std::stringstream ss(categoriasStr);
            std::string categoria;
            while (std::getline(ss, categoria, ',')) {
                // Eliminar espacios en blanco
                categoria.erase(0, categoria.find_first_not_of(" "));
                categoria.erase(categoria.find_last_not_of(" ") + 1);
                if (!categoria.empty()) {
                    categorias.push_back(categoria);
                }
            }
        }
        
        std::string activoStr;
        std::cout << "¿Activo? (S/N) (" << (proveedor->isActivo() ? "S" : "N") << "): ";
        std::getline(std::cin, activoStr);
        
        if (activoStr.empty()) {
            activo = proveedor->isActivo();
        } else {
            activo = (Utilidades::aMinusculas(activoStr) == "s" || 
                     Utilidades::aMinusculas(activoStr) == "si" ||
                     Utilidades::aMinusculas(activoStr) == "y" ||
                     Utilidades::aMinusculas(activoStr) == "yes");
        }
        
        Proveedor proveedorActualizado(proveedor->getId(), nombre, contacto, email, 
                                     telefono, direccion, categorias, activo);
        
        if (proveedorController.actualizar(proveedorActualizado)) {
            Menu::mostrarExito("Proveedor actualizado correctamente");
        } else {
            Menu::mostrarError("No se pudo actualizar el proveedor");
        }
    }
    
    void eliminarProveedor() {
        Utilidades::limpiarPantalla();
        std::cout << "===== ELIMINAR PROVEEDOR =====" << std::endl;
        
        std::cout << "Ingrese ID del proveedor a eliminar: ";
        std::string id;
        std::getline(std::cin, id);
        
        Proveedor* proveedor = proveedorController.obtenerPorId(id);
        
        if (!proveedor) {
            Menu::mostrarError("No se encontro el proveedor");
            return;
        }
        
        std::cout << "\nProveedor encontrado:" << std::endl;
        proveedor->mostrar();
        
        if (!Menu::confirmar("\n¿Esta seguro de que desea eliminar este proveedor?")) {
            return;
        }
        
        if (proveedorController.eliminar(id)) {
            Menu::mostrarExito("Proveedor eliminado correctamente");
        } else {
            Menu::mostrarError("No se pudo eliminar el proveedor");
        }
    }
    
    void listarPorCategoria() {
        Utilidades::limpiarPantalla();
        std::cout << "===== PROVEEDORES POR CATEGORIA =====" << std::endl;
        
        std::cout << "Ingrese categoria a buscar: ";
        std::string categoria;
        std::getline(std::cin, categoria);
        
        if (categoria.empty()) {
            Menu::mostrarError("La categoria no puede estar vacia");
            return;
        }
        
        Lista<Proveedor> proveedores = proveedorController.obtenerPorCategoria(categoria);
        
        if (proveedores.estaVacia()) {
            Menu::mostrarInfo("No hay proveedores en la categoria especificada");
            return;
        }
        
        std::cout << "\nProveedores en la categoria '" << categoria << "':" << std::endl;
        mostrarTablaProveedores(proveedores);
        
        Utilidades::pausar();
    }
    
    void ordenarPorNombre() {
        Utilidades::limpiarPantalla();
        std::cout << "===== PROVEEDORES ORDENADOS POR NOMBRE =====" << std::endl;
        
        std::vector<Proveedor> proveedores = proveedorController.ordenarPorNombreAsc();
        
        if (proveedores.empty()) {
            Menu::mostrarInfo("No hay proveedores registrados");
            return;
        }
        
        std::cout << "\nProveedores ordenados por nombre:" << std::endl;
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;
        std::cout << std::left << std::setw(5) << "ID"
                  << std::left << std::setw(25) << "Nombre"
                  << std::left << std::setw(20) << "Contacto"
                  << std::left << std::setw(20) << "Email"
                  << std::left << std::setw(15) << "Telefono" << std::endl;
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;
        
        for (const auto& proveedor : proveedores) {
            std::cout << proveedor.obtenerFilaTabla() << std::endl;
        }
        
        Utilidades::pausar();
    }
    
    void mostrarTablaProveedores() {
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;
        std::cout << std::left << std::setw(5) << "ID"
                  << std::left << std::setw(25) << "Nombre"
                  << std::left << std::setw(20) << "Contacto"
                  << std::left << std::setw(20) << "Email"
                  << std::left << std::setw(15) << "Telefono" << std::endl;
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;
        
        auto mostrarProveedor = [](const Proveedor& p) {
            if (p.isActivo()) {
                std::cout << p.obtenerFilaTabla() << std::endl;
            }
        };
        
        proveedorController.obtenerTodos().forEach(mostrarProveedor);
    }
    
    void mostrarTablaProveedores(Lista<Proveedor>& proveedores) {
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;
        std::cout << std::left << std::setw(5) << "ID"
                  << std::left << std::setw(25) << "Nombre"
                  << std::left << std::setw(20) << "Contacto"
                  << std::left << std::setw(20) << "Email"
                  << std::left << std::setw(15) << "Telefono" << std::endl;
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;
        
        auto mostrarProveedor = [](const Proveedor& p) {
            if (p.isActivo()) {
                std::cout << p.obtenerFilaTabla() << std::endl;
            }
        };
        
        proveedores.forEach(mostrarProveedor);
    }
};

#endif