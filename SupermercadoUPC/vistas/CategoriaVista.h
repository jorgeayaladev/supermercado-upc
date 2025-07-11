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
        : categoriaController(_categoriaController), productoController(_productoController) {}
    
    // Perfecto
    void mostrarMenu() {
        bool salir = false;
        
        while (!salir) {
            Menu menu("GESTION DE CATEGORIAS:");
            menu.agregarOpcion("Listar todas las categorias");
            menu.agregarOpcion("Buscar categoria");
            menu.agregarOpcion("Agregar nueva categoria");
            menu.agregarOpcion("Editar categoria");
            menu.agregarOpcion("Eliminar categoria");
            menu.agregarOpcion("Ver productos por categoria");
            menu.agregarOpcion("Ordenar categorias por nombre");
            menu.agregarOpcion("Volver al menu principal");
            
            int opcion = menu.mostrar();
            
            switch (opcion) {
                case 1: listarCategorias(); break;
                case 2: buscarCategoria(); break;
                case 3: agregarCategoria(); break;
                case 4: editarCategoria(); break;
                case 5: eliminarCategoria(); break;
                case 6: verProductosPorCategoria(); break;
                case 7: ordenarCategoriasPorNombre(); break;
                case 8: salir = true; break;
            }
        }
    }
    
    // Perfecto
    void listarCategorias() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "LISTADO DE CATEGORIAS" << std::endl;
        
        mostrarTablaCategorias();
        
        Utilidades::pausar();
    }
    
    // Perfecto
    void buscarCategoria() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "BUSCAR CATEGORIA" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
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

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        Utilidades::pausar();
    }
    
    // Perfecto
    void agregarCategoria() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "AGREGAR CATEGORIA" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        std::string nombre, descripcion;
        
        std::cout << "Nombre: ";
        std::getline(std::cin, nombre);
        
        if (nombre.empty()) {
            Menu::mostrarError("El nombre no puede estar vacio");
            return;
        }
        
        std::cout << "Descripcion: ";
        std::getline(std::cin, descripcion);
        
        if (descripcion.empty()) {
            descripcion = "Descripcion de " + nombre;
        }
        
        std::string id = "C" + Utilidades::idGenerado(categoriaController.obtenerCantidad() + 1);
        Categoria nuevaCategoria(id, nombre, descripcion);

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        if (categoriaController.crear(nuevaCategoria)) {
            Menu::mostrarExito("Categoria agregada correctamente");
        } else {
            Menu::mostrarError("No se pudo agregar la categoria. Puede que ya exista una con el mismo nombre");
        }
    }
    
    // Perfecto
    void editarCategoria() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "EDITAR CATEGORIA" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
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
        
        if (!Menu::confirmar("Desea editar esta categoria?")) {
            return;
        }
        
        std::string nombre, descripcion;
        bool activa;
        
        std::cout << "\nNuevo nombre (" << categoria->getNombre() << "): ";
        std::getline(std::cin, nombre);
        if (nombre.empty()) {
            nombre = categoria->getNombre();
        }
        
        std::cout << "Nueva descripcion (" << categoria->getDescripcion() << "): ";
        std::getline(std::cin, descripcion);
        if (descripcion.empty()) {
            descripcion = categoria->getDescripcion();
        }
        
        std::string activaStr;
        std::cout << "Activa? (S/N) (" << (categoria->isActiva() ? "S" : "N") << "): ";
        std::getline(std::cin, activaStr);
        
        if (activaStr.empty()) {
            activa = categoria->isActiva();
        } else {
            activa = (Utilidades::aMinusculas(activaStr) == "s" || 
                     Utilidades::aMinusculas(activaStr) == "si" ||
                     Utilidades::aMinusculas(activaStr) == "y" ||
                     Utilidades::aMinusculas(activaStr) == "yes");
        }
        
        Categoria categoriaActualizada(categoria->getId(), nombre, descripcion, activa);
        
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;

        if (categoriaController.actualizar(categoriaActualizada)) {
            Menu::mostrarExito("Categoria actualizada correctamente");
        } else {
            Menu::mostrarError("No se pudo actualizar la categoria");
        }
    }
    
    // Perfecto
    void eliminarCategoria() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "ELIMINAR CATEGORIA" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
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
        
        // Verificar si hay productos en esta categoria
        Lista<Producto> productosEnCategoria = productoController.obtenerPorCategoria(categoria->getNombre());
        
        if (!productosEnCategoria.estaVacia()) {
            std::cout << "\nADVERTENCIA: Esta categoria tiene " << productosEnCategoria.getTamano() 
                      << " productos asociados." << std::endl;
        }
        
        if (!Menu::confirmar("Esta seguro de que desea eliminar esta categoria?")) {
            return;
        }

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        if (categoriaController.eliminar(id)) {
            Menu::mostrarExito("Categoria eliminada correctamente");
        } else {
            Menu::mostrarError("No se pudo eliminar la categoria");
        }
    }
    
    // Perfecto
    void verProductosPorCategoria() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "PRODUCTOS POR CATEGORIA" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        // Mostrar categorías disponibles
        Lista<Categoria> categoriasActivas = categoriaController.obtenerActivas();
        
        if (categoriasActivas.estaVacia()) {
            Menu::mostrarError("No hay categorias disponibles");
            return;
        }
        
        std::cout << "Categorias disponibles:" << std::endl;
        auto mostrarCategoria = [](const Categoria& c) {
            std::cout << "- " << c.getNombre() << std::endl;
        };
        
        categoriasActivas.forEach(mostrarCategoria);
        
        std::cout << "\nIngrese nombre de la categoria: ";
        std::string categoria;
        std::getline(std::cin, categoria);
        
        // Verificar si la categoría existe
        Categoria* categoriaExistente = categoriaController.obtenerPorNombre(categoria);
        if (!categoriaExistente) {
            Menu::mostrarError("La categoria ingresada no existe");
            return;
        }
        
        Lista<Producto> productos = productoController.obtenerPorCategoria(categoriaExistente->getNombre());
        
        if (productos.estaVacia()) {
            Menu::mostrarInfo("No hay productos en la categoria " + categoriaExistente->getNombre());
            return;
        }
        
        std::cout << "\nProductos en la categoria " << categoriaExistente->getNombre() << ":" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << std::left << std::setw(10) << "ID"
                  << std::left << std::setw(25) << "Nombre"
                  << std::left << std::setw(15) << "Precio"
                  << std::left << std::setw(15) << "Stock"
                  << std::left << std::setw(20) << "Categoria"
                  << std::left << std::setw(15) << "Disponible" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        auto mostrarProducto = [](const Producto& p) {
            std::cout << p.obtenerFilaTabla() << std::endl;
        };
        productos.forEach(mostrarProducto);

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        Utilidades::pausar();
    }
    
    // Perfecto
    void ordenarCategoriasPorNombre() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "CATEGORIAS ORDENADAS POR NOMBRE" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        std::vector<Categoria> categoriasOrdenadas = categoriaController.ordenarPorNombreAsc();
        
        if (categoriasOrdenadas.empty()) {
            Menu::mostrarInfo("No hay categorias registradas");
            return;
        }
        
        std::cout << "Categorias ordenadas alfabeticamente:" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << std::left << std::setw(10) << "ID"
                  << std::left << std::setw(20) << "Nombre"
                  << std::left << std::setw(45) << "Descripcion"
                  << std::left << std::setw(10) << "Activa" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        for (const auto& categoria : categoriasOrdenadas) {
            std::cout << categoria.obtenerFilaTabla() << std::endl;
        }

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        Utilidades::pausar();
    }
    
    // Perfecto
    void mostrarTablaCategorias() {
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << std::left << std::setw(10) << "ID"
                  << std::left << std::setw(20) << "Nombre"
                  << std::left << std::setw(45) << "Descripcion"
                  << std::left << std::setw(10) << "Activa" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        auto mostrarCategoria = [](const Categoria& c) {
            if (c.isActiva()) {
                std::cout << c.obtenerFilaTabla() << std::endl;
            }
        };
        categoriaController.obtenerTodas().forEach(mostrarCategoria);

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
    }

    // Perfecto
    void mostrarCatalogo() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "CATALOGO DE CATEGORIAS" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;

        mostrarTablaCategorias();

        std::cout << "\nPresione Enter para volver al menu...";
        std::cin.get();
    }
};

#endif