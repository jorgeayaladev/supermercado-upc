#ifndef PRODUCTO_VISTA_H
#define PRODUCTO_VISTA_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <functional>
#include "../modelos/Producto.h"
#include "../modelos/Categoria.h"
#include "../controladores/ProductoController.h"
#include "../controladores/CategoriaController.h"
#include "../utilidades/Utilidades.h"
#include "Menu.h"

class ProductoVista {
private:
    ProductoController& productoController;
    CategoriaController& categoriaController;

public:
    // Constructor
    ProductoVista(ProductoController& _productoController, CategoriaController& _categoriaController)
        : productoController(_productoController), categoriaController(_categoriaController) {}
    
    // Mostrar menú principal de productos
    void mostrarMenu() {
        bool salir = false;
        
        while (!salir) {
            Menu menu("GESTION DE PRODUCTOS");
            menu.agregarOpcion("Listar todos los productos");
            menu.agregarOpcion("Buscar producto");
            menu.agregarOpcion("Agregar nuevo producto");
            menu.agregarOpcion("Editar producto existente");
            menu.agregarOpcion("Eliminar producto");
            menu.agregarOpcion("Listar productos por categoria");
            menu.agregarOpcion("Ordenar productos por nombre");
            menu.agregarOpcion("Ordenar productos por precio");
            menu.agregarOpcion("Productos con stock bajo");
            menu.agregarOpcion("Volver al menu principal");
            
            int opcion = menu.mostrar();
            
            switch (opcion) {
                case 1:
                    listarProductos();
                    break;
                case 2:
                    buscarProducto();
                    break;
                case 3:
                    agregarProducto();
                    break;
                case 4:
                    editarProducto();
                    break;
                case 5:
                    eliminarProducto();
                    break;
                case 6:
                    listarPorCategoria();
                    break;
                case 7:
                    ordenarPorNombre();
                    break;
                case 8:
                    ordenarPorPrecio();
                    break;
                case 9:
                    productosStockBajo();
                    break;
                case 10:
                    salir = true;
                    break;
            }
        }
    }
    
    // Listar todos los productos
    void listarProductos() {
        Utilidades::limpiarPantalla();
        std::cout << "===== LISTADO DE PRODUCTOS =====" << std::endl;
        
        mostrarTablaProductos();
        
        Utilidades::pausar();
    }
    
    // Buscar producto
    void buscarProducto() {
        Utilidades::limpiarPantalla();
        std::cout << "===== BUSCAR PRODUCTO =====" << std::endl;
        
        std::cout << "Ingrese nombre a buscar: ";
        std::string busqueda;
        std::getline(std::cin, busqueda);
        
        if (busqueda.empty()) {
            Menu::mostrarError("La busqueda no puede estar vacia");
            return;
        }
        
        Lista<Producto> resultados = productoController.buscarPorNombre(busqueda);
        
        if (resultados.estaVacia()) {
            Menu::mostrarInfo("No se encontraron productos que coincidan con la busqueda");
            return;
        }
        
        std::cout << "\nResultados de la busqueda para: '" << busqueda << "'" << std::endl;
        std::cout << Utilidades::generarLinea('-', 70) << std::endl;
        std::cout << std::left << std::setw(5) << "ID"
                  << std::left << std::setw(20) << "Nombre"
                  << std::right << std::setw(10) << "Precio"
                  << std::right << std::setw(8) << "Stock"
                  << std::left << std::setw(15) << "Categoria"
                  << std::left << std::setw(10) << "Disponible" << std::endl;
        std::cout << Utilidades::generarLinea('-', 70) << std::endl;
        
        auto mostrarProducto = [](const Producto& p) {
            std::cout << p.obtenerFilaTabla() << std::endl;
        };
        
        resultados.forEach(mostrarProducto);
        
        Utilidades::pausar();
    }
    
    // Agregar un nuevo producto
    void agregarProducto() {
        Utilidades::limpiarPantalla();
        std::cout << "===== AGREGAR NUEVO PRODUCTO =====" << std::endl;
        
        std::string nombre, descripcion, categoria, codigoBarras;
        double precio;
        int stock;
        
        std::cout << "Nombre: ";
        std::getline(std::cin, nombre);
        
        if (nombre.empty()) {
            Menu::mostrarError("El nombre no puede estar vacio");
            return;
        }
        
        std::cout << "Descripcion: ";
        std::getline(std::cin, descripcion);
        
        std::string precioStr;
        std::cout << "Precio: ";
        std::getline(std::cin, precioStr);
        
        try {
            precio = std::stod(precioStr);
            if (precio <= 0) {
                throw std::invalid_argument("El precio debe ser mayor que cero");
            }
        } catch (const std::exception& e) {
            Menu::mostrarError("Precio invalido. Debe ser un numero mayor que cero");
            return;
        }
        
        std::string stockStr;
        std::cout << "Stock: ";
        std::getline(std::cin, stockStr);
        
        try {
            stock = std::stoi(stockStr);
            if (stock < 0) {
                throw std::invalid_argument("El stock no puede ser negativo");
            }
        } catch (const std::exception& e) {
            Menu::mostrarError("Stock invalido. Debe ser un numero entero no negativo");
            return;
        }
        
        // Mostrar categorías disponibles
        Lista<Categoria> categoriasActivas = categoriaController.obtenerActivas();
        
        if (categoriasActivas.estaVacia()) {
            Menu::mostrarError("No hay categorias disponibles. Cree categorias primero");
            return;
        }
        
        std::cout << "\nCategorias disponibles:" << std::endl;
        auto mostrarCategoria = [](const Categoria& c) {
            std::cout << "- " << c.getNombre() << std::endl;
        };
        
        categoriasActivas.forEach(mostrarCategoria);
        
        std::cout << "\nCategoria: ";
        std::getline(std::cin, categoria);
        
        // Verificar si la categoría existe
        Categoria* categoriaExistente = categoriaController.obtenerPorNombre(categoria);
        if (!categoriaExistente) {
            Menu::mostrarError("La categoria ingresada no existe");
            return;
        }
        
        std::cout << "Codigo de barras: ";
        std::getline(std::cin, codigoBarras);
        
        if (codigoBarras.empty()) {
            Menu::mostrarError("El codigo de barras no puede estar vacio");
            return;
        }
        
        // Verificar si ya existe un producto con ese código de barras
        Producto* existente = productoController.obtenerPorCodigoBarras(codigoBarras);
        if (existente) {
            Menu::mostrarError("Ya existe un producto con ese codigo de barras");
            return;
        }
        
        // Crear el nuevo producto
        std::string id = "P" + Utilidades::generarId().substr(0, 8);
        Producto nuevoProducto(id, nombre, descripcion, precio, stock, categoriaExistente->getNombre(), codigoBarras);
        
        if (productoController.crear(nuevoProducto)) {
            Menu::mostrarExito("Producto agregado correctamente");
        } else {
            Menu::mostrarError("No se pudo agregar el producto");
        }
    }
    
    // Editar un producto existente
    void editarProducto() {
        Utilidades::limpiarPantalla();
        std::cout << "===== EDITAR PRODUCTO =====" << std::endl;
        
        std::cout << "Ingrese ID del producto a editar: ";
        std::string id;
        std::getline(std::cin, id);
        
        Producto* producto = productoController.obtenerPorId(id);
        
        if (!producto) {
            Menu::mostrarError("No se encontro ningun producto con el ID proporcionado");
            return;
        }
        
        std::cout << "\nProducto encontrado:" << std::endl;
        producto->mostrar();
        
        if (!Menu::confirmar("\n¿Desea editar este producto?")) {
            return;
        }
        
        std::string nombre, descripcion, categoria, codigoBarras;
        double precio;
        int stock;
        bool disponible;
        
        std::cout << "\nNuevo nombre (" << producto->getNombre() << "): ";
        std::getline(std::cin, nombre);
        if (nombre.empty()) {
            nombre = producto->getNombre();
        }
        
        std::cout << "Nueva descripcion (" << producto->getDescripcion() << "): ";
        std::getline(std::cin, descripcion);
        if (descripcion.empty()) {
            descripcion = producto->getDescripcion();
        }
        
        std::string precioStr;
        std::cout << "Nuevo precio (" << producto->getPrecio() << "): ";
        std::getline(std::cin, precioStr);
        
        if (precioStr.empty()) {
            precio = producto->getPrecio();
        } else {
            try {
                precio = std::stod(precioStr);
                if (precio <= 0) {
                    throw std::invalid_argument("El precio debe ser mayor que cero");
                }
            } catch (const std::exception& e) {
                Menu::mostrarError("Precio invalido. Se mantendra el valor original");
                precio = producto->getPrecio();
            }
        }
        
        std::string stockStr;
        std::cout << "Nuevo stock (" << producto->getStock() << "): ";
        std::getline(std::cin, stockStr);
        
        if (stockStr.empty()) {
            stock = producto->getStock();
        } else {
            try {
                stock = std::stoi(stockStr);
                if (stock < 0) {
                    throw std::invalid_argument("El stock no puede ser negativo");
                }
            } catch (const std::exception& e) {
                Menu::mostrarError("Stock invalido. Se mantendra el valor original");
                stock = producto->getStock();
            }
        }
        
        // Mostrar categorías disponibles
        std::cout << "\nCategorias disponibles:" << std::endl;
        auto mostrarCategoria = [](const Categoria& c) {
            if (c.isActiva()) {
                std::cout << "- " << c.getNombre() << std::endl;
            }
        };
        
        categoriaController.obtenerTodas().forEach(mostrarCategoria);
        
        std::cout << "\nNueva categoria (" << producto->getCategoria() << "): ";
        std::getline(std::cin, categoria);
        if (categoria.empty()) {
            categoria = producto->getCategoria();
        } else {
            // Verificar si la categoría existe
            Categoria* categoriaExistente = categoriaController.obtenerPorNombre(categoria);
            if (!categoriaExistente) {
                Menu::mostrarError("La categoria ingresada no existe. Se mantendra la categoria original");
                categoria = producto->getCategoria();
            }
        }
        
        std::cout << "Nuevo codigo de barras (" << producto->getCodigoBarras() << "): ";
        std::getline(std::cin, codigoBarras);
        if (codigoBarras.empty()) {
            codigoBarras = producto->getCodigoBarras();
        } else {
            // Verificar si ya existe un producto con ese código de barras (que no sea el mismo)
            Producto* existente = productoController.obtenerPorCodigoBarras(codigoBarras);
            if (existente && existente->getId() != producto->getId()) {
                Menu::mostrarError("Ya existe un producto con ese codigo de barras. Se mantendra el codigo original");
                codigoBarras = producto->getCodigoBarras();
            }
        }
        
        std::string disponibleStr;
        std::cout << "¿Disponible? (S/N) (" << (producto->isDisponible() ? "S" : "N") << "): ";
        std::getline(std::cin, disponibleStr);
        
        if (disponibleStr.empty()) {
            disponible = producto->isDisponible();
        } else {
            disponible = (Utilidades::aMinusculas(disponibleStr) == "s" || 
                         Utilidades::aMinusculas(disponibleStr) == "si" ||
                         Utilidades::aMinusculas(disponibleStr) == "y" ||
                         Utilidades::aMinusculas(disponibleStr) == "yes");
        }
        
        // Actualizar el producto
        Producto productoActualizado(producto->getId(), nombre, descripcion, precio, stock, categoria, codigoBarras, disponible);
        
        if (productoController.actualizar(productoActualizado)) {
            Menu::mostrarExito("Producto actualizado correctamente");
        } else {
            Menu::mostrarError("No se pudo actualizar el producto");
        }
    }
    
    // Eliminar un producto
    void eliminarProducto() {
        Utilidades::limpiarPantalla();
        std::cout << "===== ELIMINAR PRODUCTO =====" << std::endl;
        
        std::cout << "Ingrese ID del producto a eliminar: ";
        std::string id;
        std::getline(std::cin, id);
        
        Producto* producto = productoController.obtenerPorId(id);
        
        if (!producto) {
            Menu::mostrarError("No se encontro ningun producto con el ID proporcionado");
            return;
        }
        
        std::cout << "\nProducto encontrado:" << std::endl;
        producto->mostrar();
        
        if (!Menu::confirmar("\n¿Esta seguro de que desea eliminar este producto?")) {
            return;
        }
        
        if (productoController.eliminar(id)) {
            Menu::mostrarExito("Producto eliminado correctamente");
        } else {
            Menu::mostrarError("No se pudo eliminar el producto");
        }
    }
    
    // Listar productos por categoría
    void listarPorCategoria() {
        Utilidades::limpiarPantalla();
        std::cout << "===== PRODUCTOS POR CATEGORIA =====" << std::endl;
        
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
        std::cout << Utilidades::generarLinea('-', 70) << std::endl;
        std::cout << std::left << std::setw(5) << "ID"
                  << std::left << std::setw(20) << "Nombre"
                  << std::right << std::setw(10) << "Precio"
                  << std::right << std::setw(8) << "Stock"
                  << std::left << std::setw(15) << "Categoria"
                  << std::left << std::setw(10) << "Disponible" << std::endl;
        std::cout << Utilidades::generarLinea('-', 70) << std::endl;
        
        auto mostrarProducto = [](const Producto& p) {
            std::cout << p.obtenerFilaTabla() << std::endl;
        };
        
        productos.forEach(mostrarProducto);
        
        Utilidades::pausar();
    }
    
    // Ordenar productos por nombre
    void ordenarPorNombre() {
        Utilidades::limpiarPantalla();
        std::cout << "===== ORDENAR PRODUCTOS POR NOMBRE =====" << std::endl;
        
        Menu menuOrden("Seleccione el orden");
        menuOrden.agregarOpcion("A-Z (Ascendente)");
        menuOrden.agregarOpcion("Z-A (Descendente)");
        menuOrden.agregarOpcion("Volver");
        
        int opcion = menuOrden.mostrar();
        
        std::vector<Producto> productos;
        
        switch (opcion) {
            case 1:
                productos = productoController.ordenarPorNombreAsc();
                std::cout << "\nProductos ordenados por nombre (A-Z):" << std::endl;
                break;
            case 2:
                productos = productoController.ordenarPorNombreDesc();
                std::cout << "\nProductos ordenados por nombre (Z-A):" << std::endl;
                break;
            case 3:
                return;
            default:
                return;
        }
        
        if (productos.empty()) {
            Menu::mostrarInfo("No hay productos disponibles");
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
        
        for (const auto& producto : productos) {
            std::cout << producto.obtenerFilaTabla() << std::endl;
        }
        
        Utilidades::pausar();
    }
    
    // Ordenar productos por precio
    void ordenarPorPrecio() {
        Utilidades::limpiarPantalla();
        std::cout << "===== ORDENAR PRODUCTOS POR PRECIO =====" << std::endl;
        
        Menu menuOrden("Seleccione el orden");
        menuOrden.agregarOpcion("Menor a Mayor");
        menuOrden.agregarOpcion("Mayor a Menor");
        menuOrden.agregarOpcion("Volver");
        
        int opcion = menuOrden.mostrar();
        
        std::vector<Producto> productos;
        
        switch (opcion) {
            case 1:
                productos = productoController.ordenarPorPrecioAsc();
                std::cout << "\nProductos ordenados por precio (Menor a Mayor):" << std::endl;
                break;
            case 2:
                productos = productoController.ordenarPorPrecioDesc();
                std::cout << "\nProductos ordenados por precio (Mayor a Menor):" << std::endl;
                break;
            case 3:
                return;
            default:
                return;
        }
        
        if (productos.empty()) {
            Menu::mostrarInfo("No hay productos disponibles");
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
        
        for (const auto& producto : productos) {
            std::cout << producto.obtenerFilaTabla() << std::endl;
        }
        
        Utilidades::pausar();
    }
    
    // Mostrar productos con stock bajo
    void productosStockBajo() {
        Utilidades::limpiarPantalla();
        std::cout << "===== PRODUCTOS CON STOCK BAJO =====" << std::endl;
        
        std::string umbralStr;
        std::cout << "Ingrese el umbral de stock: ";
        std::getline(std::cin, umbralStr);
        
        int umbral;
        try {
            umbral = std::stoi(umbralStr);
            if (umbral < 0) {
                throw std::invalid_argument("El umbral no puede ser negativo");
            }
        } catch (const std::exception& e) {
            Menu::mostrarError("Umbral invalido. Debe ser un numero entero no negativo");
            return;
        }
        
        Lista<Producto> productos = productoController.obtenerStockBajo(umbral);
        
        if (productos.estaVacia()) {
            Menu::mostrarInfo("No hay productos con stock menor a " + std::to_string(umbral));
            return;
        }
        
        std::cout << "\nProductos con stock menor a " << umbral << ":" << std::endl;
        std::cout << Utilidades::generarLinea('-', 70) << std::endl;
        std::cout << std::left << std::setw(5) << "ID"
                  << std::left << std::setw(20) << "Nombre"
                  << std::right << std::setw(10) << "Precio"
                  << std::right << std::setw(8) << "Stock"
                  << std::left << std::setw(15) << "Categoria"
                  << std::left << std::setw(10) << "Disponible" << std::endl;
        std::cout << Utilidades::generarLinea('-', 70) << std::endl;
        
        auto mostrarProducto = [](const Producto& p) {
            std::cout << p.obtenerFilaTabla() << std::endl;
        };
        
        productos.forEach(mostrarProducto);
        
        Utilidades::pausar();
    }
    
    // Mostrar tabla de productos
    void mostrarTablaProductos() {
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
        
        productoController.obtenerTodos().forEach(mostrarProducto);
    }

    void mostrarCatalogo() {
        Utilidades::limpiarPantalla();
        std::cout << "===== CATALOGO DE PRODUCTOS =====" << std::endl;

        mostrarTablaProductos();

        std::cout << "\nPresione Enter para volver al menu...";
        std::cin.get();
    }
};

#endif