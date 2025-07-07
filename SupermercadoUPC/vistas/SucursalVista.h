#ifndef SUCURSAL_VISTA_H
#define SUCURSAL_VISTA_H

#include <string>
#include <iostream>
#include <iomanip>
#include "../modelos/Sucursal.h"
#include "../controladores/SucursalController.h"
#include "../utilidades/Utilidades.h"
#include "Menu.h"

class SucursalVista {
private:
    SucursalController& sucursalController;

public:
    SucursalVista(SucursalController& _sucursalController)
        : sucursalController(_sucursalController) {}
    
    void mostrarMenu() {
        bool salir = false;
        
        while (!salir) {
            Menu menu("GESTION DE SUCURSALES:");
            menu.agregarOpcion("Listar todas las sucursales");
            menu.agregarOpcion("Buscar sucursal por ID (Tabla Hash)");
            menu.agregarOpcion("Buscar sucursal por nombre (Arbol Binario)");
            menu.agregarOpcion("Listar ordenadas por nombre");
            menu.agregarOpcion("Buscar por rango de ventas (Arbol Balanceado)");
            menu.agregarOpcion("Agregar nueva sucursal");
            menu.agregarOpcion("Editar sucursal");
            menu.agregarOpcion("Eliminar sucursal");
            menu.agregarOpcion("Conectar sucursales (Grafo)");
            menu.agregarOpcion("Encontrar ruta mas corta");
            menu.agregarOpcion("Analizar red de sucursales");
            menu.agregarOpcion("Mostrar estadisticas");
            menu.agregarOpcion("Volver al menu principal");
            
            int opcion = menu.mostrar();
            
            switch (opcion) {
                case 1: listarSucursales(); break;
                case 2: buscarPorId(); break;
                case 3: buscarPorNombre(); break;
                case 4: listarOrdenadasPorNombre(); break;
                case 5: buscarPorRangoVentas(); break;
                case 6: agregarSucursal(); break;
                case 7: editarSucursal(); break;
                case 8: eliminarSucursal(); break;
                case 9: conectarSucursales(); break;
                case 10: encontrarRutaMasCorta(); break;
                case 11: analizarRedSucursales(); break;
                case 12: mostrarEstadisticas(); break;
                case 13: salir = true; break;
            }
        }
    }
    
    void listarSucursales() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "LISTADO DE SUCURSALES" << std::endl;
        
        mostrarTablaSucursales();
        
        Utilidades::pausar();
    }
    
    void buscarPorId() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "BUSCAR SUCURSAL POR ID (TABLA HASH)" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        std::cout << "Ingrese ID de la sucursal: ";
        std::string id;
        std::getline(std::cin, id);
        
        if (id.empty()) {
            Menu::mostrarError("El ID no puede estar vacio");
            return;
        }
        
        Sucursal* sucursal = sucursalController.obtenerPorId(id);
        
        if (!sucursal) {
            Menu::mostrarInfo("No se encontro la sucursal con ID: " + id);
            return;
        }
        
        std::cout << "\nSucursal encontrada usando Tabla Hash:" << std::endl;
        sucursal->mostrar();

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        Utilidades::pausar();
    }
    
    void buscarPorNombre() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "BUSCAR SUCURSAL POR NOMBRE (ARBOL BINARIO)" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        std::cout << "Ingrese nombre de la sucursal: ";
        std::string nombre;
        std::getline(std::cin, nombre);
        
        if (nombre.empty()) {
            Menu::mostrarError("El nombre no puede estar vacio");
            return;
        }
        
        Sucursal* sucursal = sucursalController.buscarPorNombre(nombre);
        
        if (!sucursal) {
            Menu::mostrarInfo("No se encontro la sucursal con nombre: " + nombre);
            return;
        }
        
        std::cout << "\nSucursal encontrada usando Arbol Binario:" << std::endl;
        sucursal->mostrar();

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        Utilidades::pausar();
    }
    
    void listarOrdenadasPorNombre() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "SUCURSALES ORDENADAS POR NOMBRE (ARBOL BINARIO)" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        std::vector<Sucursal> sucursalesOrdenadas = sucursalController.obtenerOrdenadasPorNombre();
        
        if (sucursalesOrdenadas.empty()) {
            Menu::mostrarInfo("No hay sucursales registradas");
            return;
        }
        
        std::cout << "Sucursales ordenadas alfabeticamente:" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << std::left << std::setw(8) << "ID"
            << std::left << std::setw(25) << "Nombre"
            << std::left << std::setw(22) << "Direccion"
            << std::left << std::setw(12) << "Telefono"
            << std::left << std::setw(10) << "Ventas"
            << std::left << std::setw(12) << "Empleados"
            << std::left << std::setw(10) << "Estado" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        for (const auto& sucursal : sucursalesOrdenadas) {
            if (sucursal.isActiva()) {
                std::cout << sucursal.obtenerFilaTabla() << std::endl;
            }
        }

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        Utilidades::pausar();
    }
    
    void buscarPorRangoVentas() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "BUSCAR POR RANGO DE VENTAS (ARBOL BALANCEADO)" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        std::string ventasMinStr, ventasMaxStr;
        double ventasMin, ventasMax;
        
        std::cout << "Ingrese ventas minimas: ";
        std::getline(std::cin, ventasMinStr);
        
        std::cout << "Ingrese ventas maximas: ";
        std::getline(std::cin, ventasMaxStr);
        
        try {
            ventasMin = std::stod(ventasMinStr);
            ventasMax = std::stod(ventasMaxStr);
            
            if (ventasMin < 0 || ventasMax < 0 || ventasMin > ventasMax) {
                throw std::invalid_argument("Rango invalido");
            }
        } catch (...) {
            Menu::mostrarError("Valores de ventas invalidos");
            return;
        }
        
        std::vector<Sucursal> sucursalesEnRango = sucursalController.obtenerPorRangoVentas(ventasMin, ventasMax);
        
        if (sucursalesEnRango.empty()) {
            Menu::mostrarInfo("No hay sucursales en el rango especificado");
            return;
        }
        
        std::cout << "\nSucursales con ventas entre $" << ventasMin << " y $" << ventasMax << ":" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << std::left << std::setw(8) << "ID"
            << std::left << std::setw(25) << "Nombre"
            << std::left << std::setw(22) << "Direccion"
            << std::left << std::setw(12) << "Telefono"
            << std::left << std::setw(10) << "Ventas"
            << std::left << std::setw(12) << "Empleados"
            << std::left << std::setw(10) << "Estado" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        for (const auto& sucursal : sucursalesEnRango) {
            if (sucursal.isActiva()) {
                std::cout << sucursal.obtenerFilaTabla() << std::endl;
            }
        }

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        Utilidades::pausar();
    }
    
    void agregarSucursal() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "AGREGAR NUEVA SUCURSAL" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        std::string nombre, direccion, telefono, gerente;
        double ventasMensuales;
        int numeroEmpleados;
        
        std::cout << "Nombre: ";
        std::getline(std::cin, nombre);
        
        if (nombre.empty()) {
            Menu::mostrarError("El nombre no puede estar vacio");
            return;
        }
        
        std::cout << "Direccion: ";
        std::getline(std::cin, direccion);
        
        if (direccion.empty()) {
            Menu::mostrarError("La direccion no puede estar vacia");
            return;
        }
        
        std::cout << "Telefono: ";
        std::getline(std::cin, telefono);
        
        std::cout << "Gerente: ";
        std::getline(std::cin, gerente);
        
        std::string ventasStr;
        std::cout << "Ventas mensuales: ";
        std::getline(std::cin, ventasStr);
        
        try {
            ventasMensuales = ventasStr.empty() ? 0.0 : std::stod(ventasStr);
            if (ventasMensuales < 0) {
                throw std::invalid_argument("Las ventas no pueden ser negativas");
            }
        } catch (...) {
            Menu::mostrarError("Ventas invalidas");
            return;
        }
        
        std::string empleadosStr;
        std::cout << "Numero de empleados: ";
        std::getline(std::cin, empleadosStr);
        
        try {
            numeroEmpleados = empleadosStr.empty() ? 0 : std::stoi(empleadosStr);
            if (numeroEmpleados < 0) {
                throw std::invalid_argument("El numero de empleados no puede ser negativo");
            }
        } catch (...) {
            Menu::mostrarError("Numero de empleados invalido");
            return;
        }
        
		std::string id = "SUC" + Utilidades::idGenerado(sucursalController.obtenerCantidad() + 1);
        Sucursal nuevaSucursal(id, nombre, direccion, telefono, gerente, 
                              ventasMensuales, numeroEmpleados);
        
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;

        if (sucursalController.crear(nuevaSucursal)) {
            Menu::mostrarExito("Sucursal agregada correctamente con ID: " + id);
        } else {
            Menu::mostrarError("No se pudo agregar la sucursal");
        }
    }
    
    void editarSucursal() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "EDITAR SUCURSAL" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        std::cout << "Ingrese ID de la sucursal a editar: ";
        std::string id;
        std::getline(std::cin, id);
        
        Sucursal* sucursal = sucursalController.obtenerPorId(id);
        
        if (!sucursal) {
            Menu::mostrarError("No se encontro la sucursal");
            return;
        }
        
        std::cout << "\nSucursal encontrada:" << std::endl;
        sucursal->mostrar();
        
        if (!Menu::confirmar("\nDesea editar esta sucursal?")) {
            return;
        }
        
        Menu::mostrarInfo("Funcionalidad de edicion en desarrollo");

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
    }
    
    void eliminarSucursal() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "ELIMINAR SUCURSAL" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        std::cout << "Ingrese ID de la sucursal a eliminar: ";
        std::string id;
        std::getline(std::cin, id);
        
        Sucursal* sucursal = sucursalController.obtenerPorId(id);
        
        if (!sucursal) {
            Menu::mostrarError("No se encontro la sucursal");
            return;
        }
        
        std::cout << "\nSucursal encontrada:" << std::endl;
        sucursal->mostrar();
        
        if (!Menu::confirmar("\nEsta seguro de que desea eliminar esta sucursal?")) {
            return;
        }
        
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;

        if (sucursalController.eliminar(id)) {
            Menu::mostrarExito("Sucursal eliminada correctamente");
        } else {
            Menu::mostrarError("No se pudo eliminar la sucursal");
        }
    }
    
    void conectarSucursales() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "CONECTAR SUCURSALES (GRAFO)" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        std::cout << "ID de sucursal origen: ";
        std::string idOrigen;
        std::getline(std::cin, idOrigen);
        
        std::cout << "ID de sucursal destino: ";
        std::string idDestino;
        std::getline(std::cin, idDestino);
        
        std::cout << "Distancia (km): ";
        std::string distanciaStr;
        std::getline(std::cin, distanciaStr);
        
        double distancia = 1.0;
        try {
            if (!distanciaStr.empty()) {
                distancia = std::stod(distanciaStr);
            }
        } catch (...) {
            Menu::mostrarError("Distancia invalida, usando valor por defecto");
        }
        
        std::cout << "Tipo de conexion (carretera/autopista/etc): ";
        std::string tipoConexion;
        std::getline(std::cin, tipoConexion);
        if (tipoConexion.empty()) {
            tipoConexion = "carretera";
        }

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        if (sucursalController.conectarSucursales(idOrigen, idDestino, distancia, tipoConexion)) {
            Menu::mostrarExito("Sucursales conectadas correctamente");
        } else {
            Menu::mostrarError("No se pudo conectar las sucursales");
        }
    }
    
    void encontrarRutaMasCorta() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "ENCONTRAR RUTA MAS CORTA (DIJKSTRA)" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        std::cout << "ID de sucursal origen: ";
        std::string idOrigen;
        std::getline(std::cin, idOrigen);
        
        std::cout << "ID de sucursal destino: ";
        std::string idDestino;
        std::getline(std::cin, idDestino);
        
        std::vector<std::string> ruta = sucursalController.encontrarRutaMasCorta(idOrigen, idDestino);
        
        if (ruta.empty()) {
            Menu::mostrarInfo("No se encontro una ruta entre las sucursales");
            return;
        }
        
        std::cout << "\nRuta mas corta encontrada:" << std::endl;
        for (size_t i = 0; i < ruta.size(); i++) {
            std::cout << ruta[i];
            if (i < ruta.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
        
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;

        Utilidades::pausar();
    }
    
    void analizarRedSucursales() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "ANALISIS DE RED DE SUCURSALES" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        sucursalController.analizarRedSucursales();
        
        Utilidades::pausar();
    }
    
    void mostrarEstadisticas() {
        Utilidades::limpiarPantalla();
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << "ESTADISTICAS DE ESTRUCTURAS DE DATOS" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        sucursalController.mostrarEstadisticas();
        
        Utilidades::pausar();
    }
    
    void mostrarTablaSucursales() {
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        std::cout << std::left << std::setw(8) << "ID"
            << std::left << std::setw(25) << "Nombre"
            << std::left << std::setw(22) << "Direccion"
            << std::left << std::setw(12) << "Telefono"
            << std::left << std::setw(10) << "Ventas"
            << std::left << std::setw(12) << "Empleados"
            << std::left << std::setw(10) << "Estado" << std::endl;
        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
        
        auto mostrarSucursal = [](const Sucursal& s) {
            if (s.isActiva()) {
                std::cout << s.obtenerFilaTabla() << std::endl;
            }
        };        
        sucursalController.obtenerTodas().forEach(mostrarSucursal);

        std::cout << Utilidades::generarLinea('=', 100) << std::endl;
    }
};

#endif