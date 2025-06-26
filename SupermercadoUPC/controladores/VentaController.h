#ifndef VENTA_CONTROLLER_H
#define VENTA_CONTROLLER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>
#include "../modelos/Venta.h"
#include "../modelos/Carrito.h"
#include "../modelos/Cliente.h"
#include "../estructuras/Lista.h"
#include "../estructuras/Pila.h"
#include "../utilidades/Utilidades.h"
#include "../utilidades/Ordenamiento.h"
#include "../controladores/ProductoController.h"
#include "../controladores/ClienteController.h"

class VentaController {
private:
    Lista<Venta> ventas;
    ProductoController& productoController;
    ClienteController& clienteController;
    const std::string archivoVentas = "datos/ventas.txt";
    Pila<Venta> ultimasVentas; // Para mantener historial de últimas ventas

public:
    // Constructor
    VentaController(ProductoController& _productoController, ClienteController& _clienteController)
        : productoController(_productoController), clienteController(_clienteController) {
        cargarVentas();
    }
    
    // Crear una nueva venta a partir de un carrito
    bool crear(Carrito& carrito, const std::string& empleadoId, const std::string& metodoPago) {
        if (carrito.getEstado() != "finalizado" || carrito.getCantidadItems() == 0) {
            return false;
        }
        
        std::string id = "V" + Utilidades::generarId();
        std::string fecha = Utilidades::obtenerFechaActual();
        std::string hora = Utilidades::obtenerHoraActual();
        
        // Verificar stock de productos y actualizarlo
        std::vector<ItemCarrito> items = carrito.obtenerItemsVector();
        for (const auto& item : items) {
            Producto* producto = productoController.obtenerPorId(item.getProductoId());
            if (!producto || !producto->isDisponible() || producto->getStock() < item.getCantidad()) {
                return false;
            }
            
            // Reducir stock
            producto->reducirStock(item.getCantidad());
            productoController.actualizar(*producto);
        }
        
        // Crear la venta
        Lista<ItemCarrito> itemsLista;
        for (const auto& item : items) {
            itemsLista.insertarFinal(item);
        }
        
        double subtotal = carrito.getTotal() / (1.0 + carrito.getImpuesto() / 100.0);
        
        Venta nuevaVenta(id, carrito.getClienteId(), empleadoId, fecha, hora, 
                          itemsLista, subtotal, carrito.getDescuento(), 
                          carrito.getImpuesto(), carrito.getTotal(), metodoPago);
        
        ventas.insertarFinal(nuevaVenta);
        ultimasVentas.apilar(nuevaVenta);
        
        // Actualizar el total de compras del cliente
        Cliente* cliente = clienteController.obtenerPorId(carrito.getClienteId());
        if (cliente) {
            cliente->agregarCompra(carrito.getTotal());
            clienteController.actualizar(*cliente);
        }
        
        guardarVentas();
        return true;
    }
    
    // Obtener una venta por ID
    Venta* obtenerPorId(const std::string& id) {
        auto buscarPorId = [&id](const Venta& v) {
            return v.getId() == id;
        };
        
        return ventas.buscar(buscarPorId);
    }
    
    // Cancelar una venta
    bool cancelar(const std::string& id) {
        Venta* venta = obtenerPorId(id);
        if (!venta || venta->getEstado() != "completada") {
            return false;
        }
        
        // Devolver productos al inventario
        auto devolverInventario = [this](const ItemCarrito& item) {
            Producto* producto = this->productoController.obtenerPorId(item.getProductoId());
            if (producto) {
                producto->aumentarStock(item.getCantidad());
                this->productoController.actualizar(*producto);
            }
        };
        
        venta->getItems().forEach(devolverInventario);
        
        // Actualizar estado de la venta
        venta->setEstado("cancelada");
        
        // Restar la compra del cliente
        Cliente* cliente = clienteController.obtenerPorId(venta->getClienteId());
        if (cliente) {
            cliente->agregarCompra(-venta->getTotal());
            clienteController.actualizar(*cliente);
        }
        
        guardarVentas();
        return true;
    }
    
    // Obtener todas las ventas
    Lista<Venta>& obtenerTodas() {
        return ventas;
    }
    
    // Obtener ventas por cliente
    Lista<Venta> obtenerPorCliente(const std::string& clienteId) {
        auto filtrarPorCliente = [&clienteId](const Venta& v) {
            return v.getClienteId() == clienteId;
        };
        
        return ventas.filtrar(filtrarPorCliente);
    }
    
    // Obtener ventas por empleado
    Lista<Venta> obtenerPorEmpleado(const std::string& empleadoId) {
        auto filtrarPorEmpleado = [&empleadoId](const Venta& v) {
            return v.getEmpleadoId() == empleadoId;
        };
        
        return ventas.filtrar(filtrarPorEmpleado);
    }
    
    // Obtener ventas por fecha
    Lista<Venta> obtenerPorFecha(const std::string& fecha) {
        auto filtrarPorFecha = [&fecha](const Venta& v) {
            return v.getFecha() == fecha;
        };
        
        return ventas.filtrar(filtrarPorFecha);
    }
    
    // Obtener ventas entre fechas
    Lista<Venta> obtenerEntreFechas(const std::string& fechaInicio, const std::string& fechaFin) {
        auto filtrarEntreFechas = [&fechaInicio, &fechaFin](const Venta& v) {
            return v.getFecha() >= fechaInicio && v.getFecha() <= fechaFin;
        };
        
        return ventas.filtrar(filtrarEntreFechas);
    }
    
    // Obtener la última venta
    Venta* obtenerUltimaVenta() {
        if (ultimasVentas.estaVacia()) {
            return nullptr;
        }        
        return &(ultimasVentas.verTope());
    }
    
    // Ordenar ventas por fecha (más reciente primero)
    std::vector<Venta> ordenarPorFechaDesc() {
        std::vector<Venta> ventasVector;
        
        auto agregarAVector = [&ventasVector](const Venta& v) {
            ventasVector.push_back(v);
        };
        
        ventas.forEach(agregarAVector);
        
        Ordenamiento<Venta>::ordenarPersonalizado(ventasVector, 
            [](const Venta& a, const Venta& b) { return a > b; });
        
        return ventasVector;
    }
    
    // Obtener ventas por método de pago
    Lista<Venta> obtenerPorMetodoPago(const std::string& metodoPago) {
        auto filtrarPorMetodoPago = [&metodoPago](const Venta& v) {
            return v.getMetodoPago() == metodoPago;
        };
        
        return ventas.filtrar(filtrarPorMetodoPago);
    }
    
    // Cargar ventas desde archivo
    void cargarVentas() {
        std::ifstream archivo(archivoVentas);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo de ventas. Se creará uno nuevo al guardar." << std::endl;
            // Generar ventas de ejemplo
            generarVentasEjemplo();
            return;
        }
        
        std::string linea;
        while (std::getline(archivo, linea)) {
            if (!linea.empty()) {
                Venta venta = Venta::desdeCSV(linea);
                ventas.insertarFinal(venta);
                ultimasVentas.apilar(venta);
            }
        }
        
        archivo.close();
    }
    
    // Guardar ventas en archivo
    void guardarVentas() {
        // Crear el directorio si no existe
        system("mkdir -p datos");
        
        std::ofstream archivo(archivoVentas);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para guardar las ventas." << std::endl;
            return;
        }
        
        auto guardarVenta = [&archivo](const Venta& v) {
            archivo << v.aCSV() << std::endl;
        };
        
        ventas.forEach(guardarVenta);
        
        archivo.close();
    }
    
private:
    // Generar ventas de ejemplo
    void generarVentasEjemplo() {
        // En una implementación real, se generarían ventas a partir de datos existentes
        // Aquí podríamos crearlas pero dependemos de productos, clientes y empleados existentes
        guardarVentas();
    }
};

#endif