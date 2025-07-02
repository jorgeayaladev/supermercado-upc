#ifndef REPORTE_VISTA_H
#define REPORTE_VISTA_H

#include <string>
#include <iostream>
#include <iomanip>
#include "../modelos/Reporte.h"
#include "../controladores/ReporteController.h"
#include "../utilidades/Utilidades.h"
#include "Menu.h"

class ReporteVista {
private:
    ReporteController& reporteController;

public:
    ReporteVista(ReporteController& _reporteController)
        : reporteController(_reporteController) {}
    
    void mostrarMenu() {
        bool salir = false;
        
        while (!salir) {
            Menu menu("GESTION DE REPORTES");
            menu.agregarOpcion("Generar reporte de ventas");
            menu.agregarOpcion("Generar reporte de stock bajo");
            menu.agregarOpcion("Generar reporte de clientes frecuentes");
            menu.agregarOpcion("Ver reportes generados");
            menu.agregarOpcion("Ver reportes pendientes");
            menu.agregarOpcion("Procesar siguiente reporte");
            menu.agregarOpcion("Volver al menu principal");
            
            int opcion = menu.mostrar();
            
            switch (opcion) {
                case 1:
                    generarReporteVentas();
                    break;
                case 2:
                    generarReporteStockBajo();
                    break;
                case 3:
                    generarReporteClientesFrecuentes();
                    break;
                case 4:
                    verReportesGenerados();
                    break;
                case 5:
                    verReportesPendientes();
                    break;
                case 6:
                    procesarSiguienteReporte();
                    break;
                case 7:
                    salir = true;
                    break;
            }
        }
    }
    
    void generarReporteVentas() {
        Utilidades::limpiarPantalla();
        std::cout << "===== GENERAR REPORTE DE VENTAS =====" << std::endl;
        
        std::string fechaInicio, fechaFin;
        
        std::cout << "Fecha inicio (YYYY-MM-DD): ";
        std::getline(std::cin, fechaInicio);
        
        if (!validarFormatoFecha(fechaInicio)) {
            Menu::mostrarError("Formato de fecha invalido");
            return;
        }
        
        std::cout << "Fecha fin (YYYY-MM-DD): ";
        std::getline(std::cin, fechaFin);
        
        if (!validarFormatoFecha(fechaFin)) {
            Menu::mostrarError("Formato de fecha invalido");
            return;
        }
        
        if (fechaInicio > fechaFin) {
            Menu::mostrarError("La fecha de inicio no puede ser posterior a la fecha fin");
            return;
        }
        
        if (reporteController.generarReporteVentas(fechaInicio, fechaFin)) {
            Menu::mostrarExito("Reporte generado correctamente");
        } else {
            Menu::mostrarError("No se pudo generar el reporte");
        }
    }
    
    void generarReporteStockBajo() {
        Utilidades::limpiarPantalla();
        std::cout << "===== GENERAR REPORTE DE STOCK BAJO =====" << std::endl;
        
        std::string umbralStr;
        std::cout << "Ingrese el umbral de stock: ";
        std::getline(std::cin, umbralStr);
        
        int umbral;
        try {
            umbral = std::stoi(umbralStr);
            if (umbral < 0) {
                throw std::invalid_argument("El umbral no puede ser negativo");
            }
        } catch (...) {
            Menu::mostrarError("Umbral invalido");
            return;
        }
        
        if (reporteController.generarReporteBajoStock(umbral)) {
            Menu::mostrarExito("Reporte generado correctamente");
        } else {
            Menu::mostrarError("No se pudo generar el reporte");
        }
    }
    
    void generarReporteClientesFrecuentes() {
        Utilidades::limpiarPantalla();
        std::cout << "===== GENERAR REPORTE DE CLIENTES FRECUENTES =====" << std::endl;
        
        std::string cantidadStr;
        std::cout << "Ingrese la cantidad de clientes a incluir: ";
        std::getline(std::cin, cantidadStr);
        
        int cantidad;
        try {
            cantidad = std::stoi(cantidadStr);
            if (cantidad <= 0) {
                throw std::invalid_argument("La cantidad debe ser mayor que cero");
            }
        } catch (...) {
            Menu::mostrarError("Cantidad invalida");
            return;
        }
        
        if (reporteController.generarReporteClientesFrecuentes(cantidad)) {
            Menu::mostrarExito("Reporte generado correctamente");
        } else {
            Menu::mostrarError("No se pudo generar el reporte");
        }
    }
    
    void verReportesGenerados() {
        Utilidades::limpiarPantalla();
        std::cout << "===== REPORTES GENERADOS =====" << std::endl;
        
        std::vector<Reporte> reportes = reporteController.ordenarPorFechaDesc();
        
        if (reportes.empty()) {
            Menu::mostrarInfo("No hay reportes generados");
            return;
        }
        
        std::cout << Utilidades::generarLinea('-', 65) << std::endl;
        std::cout << std::left << std::setw(10) << "ID"
                  << std::left << std::setw(25) << "Titulo"
                  << std::left << std::setw(15) << "Tipo"
                  << std::left << std::setw(12) << "Fecha" << std::endl;
        std::cout << Utilidades::generarLinea('-', 65) << std::endl;
        
        for (const auto& reporte : reportes) {
            std::cout << reporte.obtenerFilaTabla() << std::endl;
        }
        
        std::cout << "\nIngrese ID del reporte para ver detalles (Enter para volver): ";
        std::string id;
        std::getline(std::cin, id);
        
        if (!id.empty()) {
            Reporte* reporte = reporteController.obtenerPorId(id);
            if (reporte) {
                std::cout << "\n";
                reporte->mostrar();
            } else {
                Menu::mostrarError("No se encontro el reporte");
            }
        }
        
        Utilidades::pausar();
    }
    
    void verReportesPendientes() {
        Utilidades::limpiarPantalla();
        std::cout << "===== REPORTES PENDIENTES =====" << std::endl;
        
        Reporte* proximoReporte = reporteController.verProximoReportePendiente();
        
        if (!proximoReporte) {
            Menu::mostrarInfo("No hay reportes pendientes");
            return;
        }
        
        std::cout << "Proximo reporte a procesar:" << std::endl;
        proximoReporte->mostrar();
        
        Utilidades::pausar();
    }
    
    void procesarSiguienteReporte() {
        Utilidades::limpiarPantalla();
        std::cout << "===== PROCESAR SIGUIENTE REPORTE =====" << std::endl;
        
        Reporte* reporte = reporteController.procesarSiguienteReporte();
        
        if (!reporte) {
            Menu::mostrarInfo("No hay reportes pendientes para procesar");
            return;
        }
        
        std::cout << "Reporte procesado:" << std::endl;
        reporte->mostrar();
        
        Utilidades::pausar();
    }
    
private:
    bool validarFormatoFecha(const std::string& fecha) {
        if (fecha.length() != 10) return false;
        if (fecha[4] != '-' || fecha[7] != '-') return false;
        
        try {
            int anio = std::stoi(fecha.substr(0, 4));
            int mes = std::stoi(fecha.substr(5, 2));
            int dia = std::stoi(fecha.substr(8, 2));
            
            if (anio < 2000 || anio > 2100) return false;
            if (mes < 1 || mes > 12) return false;
            if (dia < 1 || dia > 31) return false;
            
            return true;
        } catch (...) {
            return false;
        }
    }
};

#endif