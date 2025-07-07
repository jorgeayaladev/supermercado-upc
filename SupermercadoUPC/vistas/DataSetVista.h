#ifndef DATASET_VISTA_H
#define DATASET_VISTA_H

#include <string>
#include <iostream>
#include "../utilidades/DataSetGenerator.h"
#include "../controladores/ProductoController.h"
#include "../controladores/CategoriaController.h"
#include "../controladores/ClienteController.h"
#include "../controladores/EmpleadoController.h"
#include "../controladores/ProveedorController.h"
#include "../controladores/VentaController.h"
#include "../controladores/CarritoController.h"
#include "../utilidades/Utilidades.h"
#include "Menu.h"

class DataSetVista {
private:
    DataSetGenerator& generator;
    ProductoController& productoController;
    CategoriaController& categoriaController;
    ClienteController& clienteController;
    EmpleadoController& empleadoController;
    ProveedorController& proveedorController;
    VentaController& ventaController;
    CarritoController& carritoController;

public:
    DataSetVista(DataSetGenerator& _generator,
                 ProductoController& _productoController,
                 CategoriaController& _categoriaController,
                 ClienteController& _clienteController,
                 EmpleadoController& _empleadoController,
                 ProveedorController& _proveedorController,
                 VentaController& _ventaController,
                 CarritoController& _carritoController)
        : generator(_generator),
          productoController(_productoController),
          categoriaController(_categoriaController),
          clienteController(_clienteController),
          empleadoController(_empleadoController),
          proveedorController(_proveedorController),
          ventaController(_ventaController),
          carritoController(_carritoController) {}
    
    void mostrarMenu() {
        bool salir = false;
        
        while (!salir) {
            Menu menu("GENERADOR DE DATASET");
            menu.agregarOpcion("Generar dataset completo");
            menu.agregarOpcion("Generar solo categorias");
            menu.agregarOpcion("Generar solo productos");
            menu.agregarOpcion("Generar solo clientes");
            menu.agregarOpcion("Generar solo empleados");
            menu.agregarOpcion("Generar solo proveedores");
            menu.agregarOpcion("Generar dataset personalizado");
            menu.agregarOpcion("Mostrar estadisticas del dataset");
            menu.agregarOpcion("Volver al menu principal");
            
            int opcion = menu.mostrar();
            
            switch (opcion) {
                case 1: generarDataSetCompleto(); break;
                case 2: generarCategorias(); break;
                case 3: generarProductos(); break;
                case 4: generarClientes(); break;
                case 5: generarEmpleados(); break;
                case 6: generarProveedores(); break;
                case 7: generarDataSetPersonalizado(); break;
                case 8: mostrarEstadisticas(); break;
                case 9: salir = true; break;
            }
        }
    }
    
    void generarDataSetCompleto() {
        Utilidades::limpiarPantalla();
        std::cout << "===== GENERAR DATASET COMPLETO =====" << std::endl;
        
        if (!Menu::confirmar("¿Esta seguro de que desea generar un dataset completo?\nEsto puede sobrescribir datos existentes.")) {
            return;
        }
        
        Utilidades::mostrarCarga("Generando dataset completo", 3);
        
        generator.generarDataSetCompleto(productoController, categoriaController,
                                       clienteController, empleadoController,
                                       proveedorController);
        
        Menu::mostrarExito("Dataset completo generado exitosamente");
    }
    
    void generarCategorias() {
        Utilidades::limpiarPantalla();
        std::cout << "===== GENERAR CATEGORIAS =====" << std::endl;
        
        std::cout << "Ingrese la cantidad de categorias a generar (por defecto 15): ";
        std::string cantidadStr;
        std::getline(std::cin, cantidadStr);
        
        int cantidad = 15;
        if (!cantidadStr.empty()) {
            try {
                cantidad = std::stoi(cantidadStr);
                if (cantidad <= 0 || cantidad > 100) {
                    throw std::invalid_argument("Cantidad fuera de rango");
                }
            } catch (...) {
                Menu::mostrarError("Cantidad invalida, usando valor por defecto (15)");
                cantidad = 15;
            }
        }
        
        Utilidades::mostrarCarga("Generando categorias", 2);
        generator.generarCategorias(categoriaController, cantidad);
        
        Menu::mostrarExito("Categorias generadas exitosamente");
    }
    
    void generarProductos() {
        Utilidades::limpiarPantalla();
        std::cout << "===== GENERAR PRODUCTOS =====" << std::endl;
        
        std::cout << "Ingrese la cantidad de productos a generar (por defecto 100): ";
        std::string cantidadStr;
        std::getline(std::cin, cantidadStr);
        
        int cantidad = 100;
        if (!cantidadStr.empty()) {
            try {
                cantidad = std::stoi(cantidadStr);
                if (cantidad <= 0 || cantidad > 1000) {
                
                    throw std::invalid_argument("Cantidad fuera de rango");
                }
            } catch (...) {
                Menu::mostrarError("Cantidad invalida, usando valor por defecto (100)");
                cantidad = 100;
            }
        }
        
        Utilidades::mostrarCarga("Generando productos", 2);
        generator.generarProductos(productoController, categoriaController, cantidad);
        
        Menu::mostrarExito("Productos generados exitosamente");
    }
    
    void generarClientes() {
        Utilidades::limpiarPantalla();
        std::cout << "===== GENERAR CLIENTES =====" << std::endl;
        
        std::cout << "Ingrese la cantidad de clientes a generar (por defecto 50): ";
        std::string cantidadStr;
        std::getline(std::cin, cantidadStr);
        
        int cantidad = 50;
        if (!cantidadStr.empty()) {
            try {
                cantidad = std::stoi(cantidadStr);
                if (cantidad <= 0 || cantidad > 500) {
                    throw std::invalid_argument("Cantidad fuera de rango");
                }
            } catch (...) {
                Menu::mostrarError("Cantidad invalida, usando valor por defecto (50)");
                cantidad = 50;
            }
        }
        
        Utilidades::mostrarCarga("Generando clientes", 2);
        generator.generarClientes(clienteController, cantidad);
        
        Menu::mostrarExito("Clientes generados exitosamente");
    }
    
    void generarEmpleados() {
        Utilidades::limpiarPantalla();
        std::cout << "===== GENERAR EMPLEADOS =====" << std::endl;
        
        std::cout << "Ingrese la cantidad de empleados a generar (por defecto 20): ";
        std::string cantidadStr;
        std::getline(std::cin, cantidadStr);
        
        int cantidad = 20;
        if (!cantidadStr.empty()) {
            try {
                cantidad = std::stoi(cantidadStr);
                if (cantidad <= 0 || cantidad > 100) {
                    throw std::invalid_argument("Cantidad fuera de rango");
                }
            } catch (...) {
                Menu::mostrarError("Cantidad invalida, usando valor por defecto (20)");
                cantidad = 20;
            }
        }
        
        Utilidades::mostrarCarga("Generando empleados", 2);
        generator.generarEmpleados(empleadoController, cantidad);
        
        Menu::mostrarExito("Empleados generados exitosamente");
    }
    
    void generarProveedores() {
        Utilidades::limpiarPantalla();
        std::cout << "===== GENERAR PROVEEDORES =====" << std::endl;
        
        std::cout << "Ingrese la cantidad de proveedores a generar (por defecto 15): ";
        std::string cantidadStr;
        std::getline(std::cin, cantidadStr);
        
        int cantidad = 15;
        if (!cantidadStr.empty()) {
            try {
                cantidad = std::stoi(cantidadStr);
                if (cantidad <= 0 || cantidad > 50) {
                    throw std::invalid_argument("Cantidad fuera de rango");
                }
            } catch (...) {
                Menu::mostrarError("Cantidad invalida, usando valor por defecto (15)");
                cantidad = 15;
            }
        }
        
        Utilidades::mostrarCarga("Generando proveedores", 2);
        generator.generarProveedores(proveedorController, cantidad);
        
        Menu::mostrarExito("Proveedores generados exitosamente");
    }
    
    void generarDataSetPersonalizado() {
        Utilidades::limpiarPantalla();
        std::cout << "===== GENERAR DATASET PERSONALIZADO =====" << std::endl;
        
        int categorias, productos, clientes, empleados, proveedores, ventas;
        
        std::cout << "Configuracion personalizada del dataset:" << std::endl;
        
        categorias = solicitarCantidad("categorias", 15, 1, 50);
        productos = solicitarCantidad("productos", 100, 1, 1000);
        clientes = solicitarCantidad("clientes", 50, 1, 500);
        empleados = solicitarCantidad("empleados", 20, 1, 100);
        proveedores = solicitarCantidad("proveedores", 15, 1, 50);
        
        std::cout << "\nResumen de la configuracion:" << std::endl;
        std::cout << "- Categorias: " << categorias << std::endl;
        std::cout << "- Productos: " << productos << std::endl;
        std::cout << "- Clientes: " << clientes << std::endl;
        std::cout << "- Empleados: " << empleados << std::endl;
        std::cout << "- Proveedores: " << proveedores << std::endl;
        
        if (!Menu::confirmar("\n¿Desea generar el dataset con esta configuracion?")) {
            return;
        }
        
        Utilidades::mostrarCarga("Generando dataset personalizado", 3);
        
        generator.generarCategorias(categoriaController, categorias);
        generator.generarProductos(productoController, categoriaController, productos);
        generator.generarClientes(clienteController, clientes);
        generator.generarEmpleados(empleadoController, empleados);
        generator.generarProveedores(proveedorController, proveedores);
        
        Menu::mostrarExito("Dataset personalizado generado exitosamente");
    }
    
    void mostrarEstadisticas() {
        Utilidades::limpiarPantalla();
        std::cout << "===== ESTADISTICAS DEL DATASET =====" << std::endl;
        
        // Contar elementos en cada controlador
        int totalCategorias = categoriaController.obtenerTodas().getTamano();
        int categoriasActivas = categoriaController.obtenerActivas().getTamano();
        
        int totalProductos = productoController.obtenerTodos().getTamano();
        int productosDisponibles = 0;
        auto contarProductosDisponibles = [&productosDisponibles](const Producto& p) {
            if (p.isDisponible()) productosDisponibles++;
        };
        productoController.obtenerTodos().forEach(contarProductosDisponibles);
        
        int totalClientes = clienteController.obtenerTodos().getTamano();
        int clientesActivos = clienteController.obtenerActivos().getTamano();
        
        int totalEmpleados = empleadoController.obtenerTodos().getTamano();
        int empleadosActivos = empleadoController.obtenerActivos().getTamano();
        
        int totalProveedores = proveedorController.obtenerTodos().getTamano();
        int proveedoresActivos = proveedorController.obtenerActivos().getTamano();
        
        int totalVentas = ventaController.obtenerTodas().getTamano();
        
        std::cout << "Resumen del dataset actual:" << std::endl;
        std::cout << Utilidades::generarLinea('-', 50) << std::endl;
        std::cout << std::left << std::setw(20) << "Entidad"
                  << std::right << std::setw(10) << "Total"
                  << std::right << std::setw(10) << "Activos"
                  << std::right << std::setw(10) << "%" << std::endl;
        std::cout << Utilidades::generarLinea('-', 50) << std::endl;
        
        mostrarEstadisticaEntidad("Categorias", totalCategorias, categoriasActivas);
        mostrarEstadisticaEntidad("Productos", totalProductos, productosDisponibles);
        mostrarEstadisticaEntidad("Clientes", totalClientes, clientesActivos);
        mostrarEstadisticaEntidad("Empleados", totalEmpleados, empleadosActivos);
        mostrarEstadisticaEntidad("Proveedores", totalProveedores, proveedoresActivos);
        
        std::cout << std::left << std::setw(20) << "Ventas"
                  << std::right << std::setw(10) << totalVentas
                  << std::right << std::setw(10) << "-"
                  << std::right << std::setw(10) << "-" << std::endl;
        
        std::cout << Utilidades::generarLinea('-', 50) << std::endl;
        
        // Estadísticas adicionales
        if (totalVentas > 0) {
            double totalVentasValor = 0;
            auto sumarVentas = [&totalVentasValor](const Venta& v) {
                totalVentasValor += v.getTotal();
            };
            ventaController.obtenerTodas().forEach(sumarVentas);
            
            std::cout << "\nEstadisticas de ventas:" << std::endl;
            std::cout << "- Total de ventas: " << totalVentas << std::endl;
            std::cout << "- Valor total: $" << std::fixed << std::setprecision(2) << totalVentasValor << std::endl;
            std::cout << "- Promedio por venta: $" << std::fixed << std::setprecision(2) << (totalVentasValor / totalVentas) << std::endl;
        }
        
        Utilidades::pausar();
    }

private:
    int solicitarCantidad(const std::string& entidad, int valorDefecto, int minimo, int maximo) {
        std::cout << "Cantidad de " << entidad << " (por defecto " << valorDefecto << "): ";
        std::string cantidadStr;
        std::getline(std::cin, cantidadStr);
        
        if (cantidadStr.empty()) {
            return valorDefecto;
        }
        
        try {
            int cantidad = std::stoi(cantidadStr);
            if (cantidad < minimo || cantidad > maximo) {
                std::cout << "Cantidad fuera de rango (" << minimo << "-" << maximo << "), usando valor por defecto." << std::endl;
                return valorDefecto;
            }
            return cantidad;
        } catch (...) {
            std::cout << "Cantidad invalida, usando valor por defecto." << std::endl;
            return valorDefecto;
        }
    }
    
    void mostrarEstadisticaEntidad(const std::string& nombre, int total, int activos) {
        double porcentaje = total > 0 ? (static_cast<double>(activos) / total) * 100 : 0;
        
        std::cout << std::left << std::setw(20) << nombre
                  << std::right << std::setw(10) << total
                  << std::right << std::setw(10) << activos
                  << std::right << std::setw(9) << std::fixed << std::setprecision(1) << porcentaje << "%" << std::endl;
    }
};

#endif