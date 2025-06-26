#ifndef REPORTE_H
#define REPORTE_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include "../estructuras/Lista.h"
#include "Venta.h"
#include "Producto.h"
#include "Cliente.h"
#include "Empleado.h"

class Reporte {
private:
    std::string id;
    std::string titulo;
    std::string descripcion;
    std::string fechaCreacion;
    std::string tipoReporte; // "ventas", "inventario", "clientes", "empleados"
    std::string fechaInicio;
    std::string fechaFin;
    std::string datos; // Datos específicos según el tipo de reporte

public:
    // Constructores
    Reporte() : id(""), titulo(""), descripcion(""), fechaCreacion(""), 
                tipoReporte(""), fechaInicio(""), fechaFin(""), datos("") {}
    
    Reporte(std::string _id, std::string _titulo, std::string _descripcion, 
            std::string _fechaCreacion, std::string _tipoReporte, 
            std::string _fechaInicio, std::string _fechaFin, std::string _datos)
        : id(_id), titulo(_titulo), descripcion(_descripcion), 
          fechaCreacion(_fechaCreacion), tipoReporte(_tipoReporte), 
          fechaInicio(_fechaInicio), fechaFin(_fechaFin), datos(_datos) {}
    
    // Getters y setters
    std::string getId() const { return id; }
    void setId(const std::string& _id) { id = _id; }
    
    std::string getTitulo() const { return titulo; }
    void setTitulo(const std::string& _titulo) { titulo = _titulo; }
    
    std::string getDescripcion() const { return descripcion; }
    void setDescripcion(const std::string& _descripcion) { descripcion = _descripcion; }
    
    std::string getFechaCreacion() const { return fechaCreacion; }
    void setFechaCreacion(const std::string& _fechaCreacion) { fechaCreacion = _fechaCreacion; }
    
    std::string getTipoReporte() const { return tipoReporte; }
    void setTipoReporte(const std::string& _tipoReporte) { tipoReporte = _tipoReporte; }
    
    std::string getFechaInicio() const { return fechaInicio; }
    void setFechaInicio(const std::string& _fechaInicio) { fechaInicio = _fechaInicio; }
    
    std::string getFechaFin() const { return fechaFin; }
    void setFechaFin(const std::string& _fechaFin) { fechaFin = _fechaFin; }
    
    std::string getDatos() const { return datos; }
    void setDatos(const std::string& _datos) { datos = _datos; }
    
    // Métodos para generar diferentes tipos de reportes
    
    // Reporte de ventas por período
    static Reporte generarReporteVentas(Lista<Venta>& ventas, 
                                         const std::string& fechaInicio, 
                                         const std::string& fechaFin) {
        Reporte reporte;
        reporte.setId(std::to_string(std::time(nullptr)));
        reporte.setTitulo("Reporte de Ventas");
        reporte.setDescripcion("Resumen de ventas entre " + fechaInicio + " y " + fechaFin);
        reporte.setFechaCreacion(obtenerFechaActual());
        reporte.setTipoReporte("ventas");
        reporte.setFechaInicio(fechaInicio);
        reporte.setFechaFin(fechaFin);
        
        // Filtrar ventas en el rango de fechas
        auto filtrarPorFecha = [&fechaInicio, &fechaFin](const Venta& venta) {
            return venta.getFecha() >= fechaInicio && venta.getFecha() <= fechaFin;
        };
        
        Lista<Venta> ventasFiltradas = ventas.filtrar(filtrarPorFecha);
        
        double totalVentas = 0.0;
        int cantidadVentas = 0;
        
        auto calcularTotales = [&totalVentas, &cantidadVentas](const Venta& venta) {
            totalVentas += venta.getTotal();
            cantidadVentas++;
        };
        
        ventasFiltradas.forEach(calcularTotales);
        
        std::string datos = "Cantidad de ventas: " + std::to_string(cantidadVentas) + "\n";
        datos += "Total de ventas: $" + std::to_string(totalVentas) + "\n";
        datos += "Promedio por venta: $" + std::to_string(cantidadVentas > 0 ? totalVentas / cantidadVentas : 0) + "\n";
        
        reporte.setDatos(datos);
        
        return reporte;
    }
    
    // Reporte de productos con bajo stock
    static Reporte generarReporteBajoStock(Lista<Producto>& productos, int umbral) {
        Reporte reporte;
        reporte.setId(std::to_string(std::time(nullptr)));
        reporte.setTitulo("Reporte de Productos con Bajo Stock");
        reporte.setDescripcion("Productos con stock inferior a " + std::to_string(umbral));
        reporte.setFechaCreacion(obtenerFechaActual());
        reporte.setTipoReporte("inventario");
        reporte.setFechaInicio("");
        reporte.setFechaFin("");
        
        // Filtrar productos con bajo stock
        auto filtrarBajoStock = [umbral](const Producto& producto) {
            return producto.getStock() < umbral && producto.isDisponible();
        };
        
        Lista<Producto> productosBajoStock = productos.filtrar(filtrarBajoStock);
        
        std::string datos = "Cantidad de productos con bajo stock: " + std::to_string(productosBajoStock.getTamano()) + "\n\n";
        
        productosBajoStock.forEach([&datos](const Producto& producto) {
            datos += "ID: " + producto.getId() + " - " + producto.getNombre() + " - Stock: " + std::to_string(producto.getStock()) + "\n";
        });
        
        reporte.setDatos(datos);
        
        return reporte;
    }
    
    // Reporte de clientes frecuentes
    static Reporte generarReporteClientesFrecuentes(Lista<Cliente>& clientes, int numeroClientes) {
        Reporte reporte;
        reporte.setId(std::to_string(std::time(nullptr)));
        reporte.setTitulo("Reporte de Clientes Frecuentes");
        reporte.setDescripcion("Top " + std::to_string(numeroClientes) + " clientes con mayores compras");
        reporte.setFechaCreacion(obtenerFechaActual());
        reporte.setTipoReporte("clientes");
        reporte.setFechaInicio("");
        reporte.setFechaFin("");
        
        // Convertir a vector para ordenar
        std::vector<Cliente> clientesVector;
        clientes.forEach([&clientesVector](const Cliente& cliente) {
            clientesVector.push_back(cliente);
        });
        
        // Ordenar por total de compras (descendente)
        std::sort(clientesVector.begin(), clientesVector.end(), 
            [](const Cliente& a, const Cliente& b) {
                return a.getTotalCompras() > b.getTotalCompras();
            });
        
        std::string datos = "Top clientes por volumen de compras:\n\n";
        
        int contador = 0;
        for (const auto& cliente : clientesVector) {
            if (contador < numeroClientes) {
                datos += (std::to_string(contador + 1) + ". " + cliente.getNombreCompleto() + 
                         " - Total compras: $" + std::to_string(cliente.getTotalCompras()) + "\n");
                contador++;
            } else {
                break;
            }
        }
        
        reporte.setDatos(datos);
        
        return reporte;
    }
    
    // Serialización
    std::string aCSV() const {
        return id + "," + titulo + "," + descripcion + "," + fechaCreacion + "," + 
               tipoReporte + "," + fechaInicio + "," + fechaFin;
        // Nota: No incluimos los datos completos en el CSV para mantenerlo simple
    }
    
    // Deserialización
    static Reporte desdeCSV(const std::string& csv) {
        Reporte r;
        std::stringstream ss(csv);
        std::string token;
        
        std::getline(ss, token, ','); r.id = token;
        std::getline(ss, token, ','); r.titulo = token;
        std::getline(ss, token, ','); r.descripcion = token;
        std::getline(ss, token, ','); r.fechaCreacion = token;
        std::getline(ss, token, ','); r.tipoReporte = token;
        std::getline(ss, token, ','); r.fechaInicio = token;
        std::getline(ss, token, ','); r.fechaFin = token;
        
        return r;
    }
    
    // Método para mostrar información
    void mostrar() const {
        std::cout << "========== REPORTE ==========" << std::endl;
        std::cout << "ID: " << id << std::endl;
        std::cout << "Titulo: " << titulo << std::endl;
        std::cout << "Descripcion: " << descripcion << std::endl;
        std::cout << "Fecha de creacion: " << fechaCreacion << std::endl;
        std::cout << "Tipo de reporte: " << tipoReporte << std::endl;
        
        if (!fechaInicio.empty() && !fechaFin.empty()) {
            std::cout << "Periodo: " << fechaInicio << " - " << fechaFin << std::endl;
        }
        
        std::cout << "\nDETALLES DEL REPORTE:" << std::endl;
        std::cout << "=============================" << std::endl;
        std::cout << datos << std::endl;
        std::cout << "=============================" << std::endl;
    }
    
    // Método para mostrar información en formato tabular
    std::string obtenerFilaTabla() const {
        std::stringstream ss;
        ss << std::left << std::setw(10) << id.substr(0, 8)
           << std::left << std::setw(25) << (titulo.length() > 23 ? titulo.substr(0, 23) + "..." : titulo)
           << std::left << std::setw(15) << tipoReporte
           << std::left << std::setw(12) << fechaCreacion;
        return ss.str();
    }
    
private:
    // Método auxiliar para obtener la fecha actual
    static std::string obtenerFechaActual() {
        auto t = std::time(nullptr);
        std::tm tm;
        localtime_s(&tm, &t);
        std::stringstream ss;
        ss << std::put_time(&tm, "%Y-%m-%d");
        return ss.str();
    }
};

#endif