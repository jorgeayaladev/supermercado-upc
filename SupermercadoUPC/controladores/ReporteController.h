#ifndef REPORTE_CONTROLLER_H
#define REPORTE_CONTROLLER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>
#include <algorithm>
#include "../modelos/Reporte.h"
#include "../modelos/Venta.h"
#include "../modelos/Producto.h"
#include "../modelos/Cliente.h"
#include "../estructuras/Lista.h"
#include "../estructuras/Cola.h"
#include "../utilidades/Utilidades.h"
#include "../controladores/ProductoController.h"
#include "../controladores/ClienteController.h"
#include "../controladores/VentaController.h"

class ReporteController {
private:
    Lista<Reporte> reportes;
    const std::string archivoReportes = "datos/reportes.txt";
    ProductoController& productoController;
    ClienteController& clienteController;
    VentaController& ventaController;
    Cola<Reporte> reportesPendientes; // Cola de reportes pendientes

public:
    // Constructor
    ReporteController(ProductoController& _productoController, 
                      ClienteController& _clienteController, 
                      VentaController& _ventaController)
        : productoController(_productoController),
          clienteController(_clienteController), 
          ventaController(_ventaController) {
        cargarReportes();
    }
    
    // Generar reporte de ventas por período
    bool generarReporteVentas(const std::string& fechaInicio, const std::string& fechaFin) {
        Lista<Venta> ventas = ventaController.obtenerEntreFechas(fechaInicio, fechaFin);
        
        Reporte reporte = Reporte::generarReporteVentas(ventas, fechaInicio, fechaFin);
        reportes.insertarFinal(reporte);
        reportesPendientes.encolar(reporte);
        
        guardarReportes();
        return true;
    }
    
    // Generar reporte de productos con bajo stock
    bool generarReporteBajoStock(int umbral) {
        Lista<Producto> productos = productoController.obtenerTodos();
        
        Reporte reporte = Reporte::generarReporteBajoStock(productos, umbral);
        reportes.insertarFinal(reporte);
        reportesPendientes.encolar(reporte);
        
        guardarReportes();
        return true;
    }
    
    // Generar reporte de clientes frecuentes
    bool generarReporteClientesFrecuentes(int numeroClientes) {
        Lista<Cliente> clientes = clienteController.obtenerTodos();
        
        Reporte reporte = Reporte::generarReporteClientesFrecuentes(clientes, numeroClientes);
        reportes.insertarFinal(reporte);
        reportesPendientes.encolar(reporte);
        
        guardarReportes();
        return true;
    }
    
    // Obtener un reporte por ID
    Reporte* obtenerPorId(const std::string& id) {
        auto buscarPorId = [&id](const Reporte& r) {
            return r.getId() == id;
        };
        
        return reportes.buscar(buscarPorId);
    }
    
    // Obtener todos los reportes
    Lista<Reporte>& obtenerTodos() {
        return reportes;
    }
    
    // Obtener reportes por tipo
    Lista<Reporte> obtenerPorTipo(const std::string& tipo) {
        auto filtrarPorTipo = [&tipo](const Reporte& r) {
            return r.getTipoReporte() == tipo;
        };
        
        return reportes.filtrar(filtrarPorTipo);
    }
    
    // Procesar el siguiente reporte pendiente
    Reporte* procesarSiguienteReporte() {
        if (reportesPendientes.estaVacia()) {
            return nullptr;
        }
        
        Reporte reporte = reportesPendientes.desencolar();
        return obtenerPorId(reporte.getId());
    }
    
    // Obtener próximo reporte pendiente sin procesarlo
    Reporte* verProximoReportePendiente() {
        if (reportesPendientes.estaVacia()) {
            return nullptr;
        }
        
        return &(reportesPendientes.verFrente());
    }
    
    // Ordenar reportes por fecha de creación (más reciente primero)
    std::vector<Reporte> ordenarPorFechaDesc() {
        std::vector<Reporte> reportesVector;
        
        auto agregarAVector = [&reportesVector](const Reporte& r) {
            reportesVector.push_back(r);
        };
        
        reportes.forEach(agregarAVector);
        
        std::sort(reportesVector.begin(), reportesVector.end(), 
            [](const Reporte& a, const Reporte& b) {
                return a.getFechaCreacion() > b.getFechaCreacion();
            });
        
        return reportesVector;
    }
    
    // Cargar reportes desde archivo
    void cargarReportes() {
        std::ifstream archivo(archivoReportes);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo de reportes. Se creará uno nuevo al guardar." << std::endl;
            return;
        }
        
        std::string linea;
        while (std::getline(archivo, linea)) {
            if (!linea.empty()) {
                Reporte reporte = Reporte::desdeCSV(linea);
                reportes.insertarFinal(reporte);
            }
        }
        
        archivo.close();
    }
    
    // Guardar reportes en archivo
    void guardarReportes() {
        // Crear el directorio si no existe
        system("mkdir -p datos");
        
        std::ofstream archivo(archivoReportes);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para guardar los reportes." << std::endl;
            return;
        }
        
        auto guardarReporte = [&archivo](const Reporte& r) {
            archivo << r.aCSV() << std::endl;
        };
        
        reportes.forEach(guardarReporte);
        
        archivo.close();
    }
};

#endif