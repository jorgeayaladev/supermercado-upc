#ifndef CATEGORIA_VISTA_H
#define CATEGORIA_VISTA_H

#include <string>
#include <iostream>
#include <iomanip>
#include "../modelos/Categoria.h"
#include "../controladores/CategoriaController.h"
#include "../controladores/ProductoController.h"
#include "../utilidades/Utilidades.h"
#include "Menu.h"

class CategoriaVista {
private:
    CategoriaController& categoriaController;
    ProductoController& productoController;

public:
    CategoriaVista(CategoriaController& _categoriaController, ProductoController& _productoController)
        : categoriaController(_categoriaController), productoController(_productoController) {
    }

    void mostrarMenu() {
        bool salir = false;

        while (!salir) {
            Menu menu("GESTION DE CATEGORIAS");
            menu.agregarOpcion("Listar todas las categorias");
            menu.agregarOpcion("Buscar categoria");
            menu.agregarOpcion("Agregar nueva categoria");
            menu.agregarOpcion("Editar categoria");
            menu.agregarOpcion("Eliminar categoria");
            menu.agregarOpcion("Ordenar por nombre");
            menu.agregarOpcion("Volver al menu principal");

            int opcion = menu.mostrar();

            switch (opcion) {
            case 1:
                listarCategorias();
                break;
            case 2:
                buscarCategoria();
                break;
            case 3:
                agregarCategoria();
                break;
            case 4:
                editarCategoria();
                break;
            case 5:
                eliminarCategoria();
                break;
            case 6:
                ordenarPorNombre();
                break;
            case 7:
                salir = true;
                break;
            }
        }
    }

    void listarCategorias() {
        Utilidades::limpiarPantalla();
        std::cout << "===== LISTADO DE CATEGORIAS =====" << std::endl;

        mostrarTablaCategorias();

        Utilidades::pausar();
    }

    void buscarCategoria() {
        Utilidades::limpiarPantalla();
        std::cout << "===== BUSCAR CATEGORIA =====" << std::endl;

        std::cout << "Ingrese nombre de la categoria: ";
        std::string nombre;
        std::getline(std::cin, nombre);

        if (nombre.empty()) {
            Menu::mostrarError("El nombre no puede estar vacio");
            return;
        }

        Categoria* categoria = categoriaController.obtenerPorNombre(nombre);

        if (!categoria) {
            Menu::mostrarInfo("No se encontro la categoria");
            return;
        }

        std::cout << "\nCategoria encontrada:" << std::endl;
        categoria->mostrar();

        Utilidades::pausar();
    }

    void agregarCategoria() {
        Utilidades::limpiarPantalla();
        std::cout << "===== AGREGAR CATEGORIA =====" << std::endl;

        std::string nombre, descripcion;

        std::cout << "Nombre: ";
        std::getline(std::cin, nombre);

        if (nombre.empty()) {
            Menu::mostrarError("El nombre no puede estar vacio");
            return;
        }

        // Verificar si ya existe una categoría con ese nombre
        if (categoriaController.obtenerPorNombre(nombre)) {
            Menu::mostrarError("Ya existe una categoria con ese nombre");
            return;
        }

        std::cout << "Descripcion: ";
        std::getline(std::cin, descripcion);

        std::string id = "C" + Utilidades::generarId().substr(0, 8);
        Categoria nuevaCategoria(id, nombre, descripcion);

        if (categoriaController.crear(nuevaCategoria)) {
            Menu::mostrarExito("Categoria agregada correctamente");
        }
        else {
            Menu::mostrarError("No se pudo agregar la categoria");
        }
    }

    void editarCategoria() {
        Utilidades::limpiarPantalla();
        std::cout << "===== EDITAR CATEGORIA =====" << std::endl;

        std::cout << "Ingrese ID de la categoria a editar: ";
        std::string id;
        std::getline(std::cin, id);

        Categoria* categoria = categoriaController.obtenerPorId(id);

        if (!categoria) {
            Menu::mostrarError("No se encontro la categoria");
            return;
        }

        std::cout << "\nCategoria encontrada:" << std::endl;
        categoria->mostrar();

        if (!Menu::confirmar("\n¿Desea editar esta categoria?")) {
            return;
        }

        std::string nombre, descripcion;
        bool activa;

        std::cout << "\nNuevo nombre (" << categoria->getNombre() << "): ";
        std::getline(std::cin, nombre);
        if (nombre.empty()) {
            nombre = categoria->getNombre();
        }
        else {
            // Verificar si ya existe otra categoría con ese nombre
            Categoria* existente = categoriaController.obtenerPorNombre(nombre);
            if (existente && existente->getId() != categoria->getId()) {
                Menu::mostrarError("Ya existe una categoria con ese nombre");
                return;
            }
        }

        std::cout << "Nueva descripcion (" << categoria->getDescripcion() << "): ";
        std::getline(std::cin, descripcion);
        if (descripcion.empty()) {
            descripcion = categoria->getDescripcion();
        }

        std::string activaStr;
        std::cout << "¿Activa? (S/N) (" << (categoria->isActiva() ? "S" : "N") << "): ";
        std::getline(std::cin, activaStr);

        if (activaStr.empty()) {
            activa = categoria->isActiva();
        }
        else {
            activa = (Utilidades::aMinusculas(activaStr) == "s" ||
                Utilidades::aMinusculas(activaStr) == "si" ||
                Utilidades::aMinusculas(activaStr) == "y" ||
                Utilidades::aMinusculas(activaStr) == "yes");
        }

        Categoria categoriaActualizada(categoria->getId(), nombre, descripcion, activa);

        if (categoriaController.actualizar(categoriaActualizada)) {
            Menu::mostrarExito("Categoria actualizada correctamente");
        }
        else {
            Menu::mostrarError("No se pudo actualizar la categoria");
        }
    }

    void eliminarCategoria() {
        Utilidades::limpiarPantalla();
        std::cout << "===== ELIMINAR CATEGORIA =====" << std::endl;

        std::cout << "Ingrese ID de la categoria a eliminar: ";
        std::string id;
        std::getline(std::cin, id);

        Categoria* categoria = categoriaController.obtenerPorId(id);

        if (!categoria) {
            Menu::mostrarError("No se encontro la categoria");
            return;
        }

        std::cout << "\nCategoria encontrada:" << std::endl;
        categoria->mostrar();

        if (!Menu::confirmar("\n¿Esta seguro de que desea eliminar esta categoria?")) {
            return;
        }

        if (categoriaController.eliminar(id)) {
            Menu::mostrarExito("Categoria eliminada correctamente");
        }
        else {
            Menu::mostrarError("No se pudo eliminar la categoria");
        }
    }

    void ordenarPorNombre() {
        Utilidades::limpiarPantalla();
        std::cout << "===== CATEGORIAS ORDENADAS POR NOMBRE =====" << std::endl;

        std::vector<Categoria> categorias = categoriaController.ordenarPorNombreAsc();

        if (categorias.empty()) {
            Menu::mostrarInfo("No hay categorias registradas");
            return;
        }

        std::cout << "\nCategorias ordenadas por nombre:" << std::endl;
        std::cout << Utilidades::generarLinea('-', 70) << std::endl;
        std::cout << std::left << std::setw(5) << "ID"
            << std::left << std::setw(20) << "Nombre"
            << std::left << std::setw(30) << "Descripcion"
            << std::left << std::setw(10) << "Estado" << std::endl;
        std::cout << Utilidades::generarLinea('-', 70) << std::endl;

        for (const auto& categoria : categorias) {
            std::cout << categoria.obtenerFilaTabla() << std::endl;
        }

        Utilidades::pausar();
    }

    void mostrarTablaCategorias() {
        std::cout << Utilidades::generarLinea('-', 70) << std::endl;
        std::cout << std::left << std::setw(5) << "ID"
            << std::left << std::setw(20) << "Nombre"
            << std::left << std::setw(30) << "Descripcion"
            << std::left << std::setw(10) << "Estado" << std::endl;
        std::cout << Utilidades::generarLinea('-', 70) << std::endl;

        auto mostrarCategoria = [](const Categoria& c) {
            std::cout << c.obtenerFilaTabla() << std::endl;
            };

        categoriaController.obtenerActivas().forEach(mostrarCategoria);
    }

    void mostrarCatalogo() {
        Utilidades::limpiarPantalla();
        std::cout << "===== CATALOGO POR CATEGORIAS =====" << std::endl;

        Lista<Categoria> categorias = categoriaController.obtenerActivas();

        if (categorias.estaVacia()) {
            Menu::mostrarInfo("No hay categorias disponibles");
            return;
        }

        std::cout << "\nCategorias disponibles:" << std::endl;
        mostrarTablaCategorias();

        std::cout << "\nSeleccione una categoria (ID): ";
        std::string categoriaId;
        std::getline(std::cin, categoriaId);

        Categoria* categoria = categoriaController.obtenerPorId(categoriaId);
        if (categoria && categoria->isActiva()) {
            Utilidades::limpiarPantalla();
            std::cout << "===== PRODUCTOS EN CATEGORIA: " << categoria->getNombre() << " =====" << std::endl;

            Lista<Producto> productos = productoController.obtenerPorCategoria(categoria->getNombre());

            if (productos.estaVacia()) {
                Menu::mostrarInfo("No hay productos disponibles en esta categoria");
                return;
            }

            std::cout << Utilidades::generarLinea('-', 70) << std::endl;
            std::cout << std::left << std::setw(5) << "ID"
                << std::left << std::setw(20) << "Nombre"
                << std::right << std::setw(10) << "Precio"
                << std::right << std::setw(8) << "Stock"
                << std::left << std::setw(15) << "Categoria"
                << std::left << std::setw(10) << "Disponible" << std::endl;
            std::cout << Utilidades::generarLinea('-', 70) << std::endl;

            auto mostrarProducto = [](const Producto& p) {
                if (p.isDisponible()) {
                    std::cout << p.obtenerFilaTabla() << std::endl;
                }
                };

            productos.forEach(mostrarProducto);
        }
        else {
            Menu::mostrarError("Categoria no valida");
        }

        Utilidades::pausar();
    }
};

#endif