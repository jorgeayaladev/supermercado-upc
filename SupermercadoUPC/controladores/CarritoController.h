#ifndef CARRITO_CONTROLLER_H
#define CARRITO_CONTROLLER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>
#include "../modelos/Carrito.h"
#include "../modelos/Producto.h"
#include "../estructuras/Lista.h"
#include "../utilidades/Utilidades.h"
#include "../controladores/ProductoController.h"

class CarritoController {
private:
    Lista<Carrito> carritos;
    ProductoController& productoController;
    const std::string archivoCarritos = "datos/carritos.txt";

public:
    // Constructor
    CarritoController(ProductoController& _productoController) 
        : productoController(_productoController) {
        cargarCarritos();
    }
    
    // Crear un nuevo carrito
    Carrito* crear(const std::string& clienteId) {
		std::string id = "CR" + Utilidades::idGenerado(carritos.getTamano() + 1);
        Carrito nuevoCarrito(id, clienteId);
        
        carritos.insertarFinal(nuevoCarrito);
        guardarCarritos();
        
        // Devolver una referencia al último carrito agregado
        return obtenerPorId(id);
    }
    
    // Obtener un carrito por ID
    Carrito* obtenerPorId(const std::string& id) {
        auto buscarPorId = [&id](const Carrito& c) {
            return c.getId() == id;
        };
        
        return carritos.buscar(buscarPorId);
    }
    
    // Obtener carrito activo de un cliente
    Carrito* obtenerCarritoActivoCliente(const std::string& clienteId) {
        auto buscarCarritoActivo = [&clienteId](const Carrito& c) {
            return c.getClienteId() == clienteId && c.getEstado() == "activo";
        };
        
        return carritos.buscar(buscarCarritoActivo);
    }
    
    // Agregar producto al carrito
    bool agregarProducto(const std::string& carritoId, const std::string& productoId, int cantidad) {
        if (cantidad <= 0) {
            return false;
        }
        
        Carrito* carrito = obtenerPorId(carritoId);
        if (!carrito || carrito->getEstado() != "activo") {
            return false;
        }
        
        Producto* producto = productoController.obtenerPorId(productoId);
        if (!producto || !producto->isDisponible() || producto->getStock() < cantidad) {
            return false;
        }
        
        carrito->agregarItem(*producto, cantidad);
        guardarCarritos();
        return true;
    }
    
    // Eliminar producto del carrito
    bool eliminarProducto(const std::string& carritoId, const std::string& productoId) {
        Carrito* carrito = obtenerPorId(carritoId);
        if (!carrito || carrito->getEstado() != "activo") {
            return false;
        }
        
        carrito->eliminarItem(productoId);
        guardarCarritos();
        return true;
    }
    
    // Actualizar cantidad de un producto en el carrito
    bool actualizarCantidad(const std::string& carritoId, const std::string& productoId, int nuevaCantidad) {
        if (nuevaCantidad <= 0) {
            return eliminarProducto(carritoId, productoId);
        }
        
        Carrito* carrito = obtenerPorId(carritoId);
        if (!carrito || carrito->getEstado() != "activo") {
            return false;
        }
        
        Producto* producto = productoController.obtenerPorId(productoId);
        if (!producto || !producto->isDisponible() || producto->getStock() < nuevaCantidad) {
            return false;
        }
        
        carrito->actualizarCantidad(productoId, nuevaCantidad);
        guardarCarritos();
        return true;
    }
    
    // Aplicar descuento al carrito
    bool aplicarDescuento(const std::string& carritoId, double descuento) {
        if (descuento < 0 || descuento > 100) {
            return false;
        }
        
        Carrito* carrito = obtenerPorId(carritoId);
        if (!carrito || carrito->getEstado() != "activo") {
            return false;
        }
        
        carrito->setDescuento(descuento);
        guardarCarritos();
        return true;
    }
    
    // Aplicar impuesto al carrito
    bool aplicarImpuesto(const std::string& carritoId, double impuesto) {
        if (impuesto < 0) {
            return false;
        }
        
        Carrito* carrito = obtenerPorId(carritoId);
        if (!carrito || carrito->getEstado() != "activo") {
            return false;
        }
        
        carrito->setImpuesto(impuesto);
        guardarCarritos();
        return true;
    }
    
    // Finalizar carrito
    bool finalizar(const std::string& carritoId) {
        Carrito* carrito = obtenerPorId(carritoId);
        if (!carrito || carrito->getEstado() != "activo" || carrito->getCantidadItems() == 0) {
            return false;
        }
        
        carrito->setEstado("finalizado");
        guardarCarritos();
        return true;
    }
    
    // Cancelar carrito
    bool cancelar(const std::string& carritoId) {
        Carrito* carrito = obtenerPorId(carritoId);
        if (!carrito || carrito->getEstado() != "activo") {
            return false;
        }
        
        carrito->setEstado("cancelado");
        guardarCarritos();
        return true;
    }
    
    // Vaciar carrito
    bool vaciar(const std::string& carritoId) {
        Carrito* carrito = obtenerPorId(carritoId);
        if (!carrito || carrito->getEstado() != "activo") {
            return false;
        }
        
        carrito->vaciar();
        guardarCarritos();
        return true;
    }
    
    // Obtener todos los carritos
    Lista<Carrito>& obtenerTodos() { return carritos; }
	int getCantidadCarritos() const { return carritos.getTamano(); }
    
    // Cargar carritos desde archivo
    void cargarCarritos() {
        std::ifstream archivo(archivoCarritos);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo de carritos. Se creará uno nuevo al guardar." << std::endl;
            return;
        }
        
        std::string linea;
        while (std::getline(archivo, linea)) {
            if (!linea.empty()) {
                Carrito carrito = Carrito::desdeCSV(linea);
                carritos.insertarFinal(carrito);
            }
        }
        
        archivo.close();
    }
    
    // Guardar carritos en archivo
    void guardarCarritos() {
        std::ofstream archivo(archivoCarritos);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para guardar los carritos." << std::endl;
            return;
        }
        
        auto guardarCarrito = [&archivo](const Carrito& c) {
            archivo << c.aCSV() << std::endl;
        };
        carritos.forEach(guardarCarrito);
        
        archivo.close();
    }
};

#endif