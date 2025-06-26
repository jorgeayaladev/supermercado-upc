#ifndef CARRITO_H
#define CARRITO_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "../estructuras/Lista.h"
#include "ItemCarrito.h"
#include "Producto.h"

class Carrito {
private:
    std::string id;
    std::string clienteId;
    Lista<ItemCarrito> items;
    double total;
    double descuento;
    double impuesto;
    std::string estado; // "activo", "finalizado", "cancelado"

public:
    // Constructores
    Carrito() : id(""), clienteId(""), total(0.0), descuento(0.0), impuesto(0.0), estado("activo") {}
    
    Carrito(std::string _id, std::string _clienteId)
        : id(_id), clienteId(_clienteId), total(0.0), descuento(0.0), impuesto(0.0), estado("activo") {}
    
    // Getters y setters
    std::string getId() const { return id; }
    void setId(const std::string& _id) { id = _id; }
    
    std::string getClienteId() const { return clienteId; }
    void setClienteId(const std::string& _clienteId) { clienteId = _clienteId; }
    
    double getTotal() const { return total; }
    
    double getDescuento() const { return descuento; }
    void setDescuento(double _descuento) {
        descuento = _descuento;
        calcularTotal();
    }
    
    double getImpuesto() const { return impuesto; }
    void setImpuesto(double _impuesto) {
        impuesto = _impuesto;
        calcularTotal();
    }
    
    std::string getEstado() const { return estado; }
    void setEstado(const std::string& _estado) { estado = _estado; }
    
    int getCantidadItems() const { return items.getTamano(); }
    
    // Métodos para gestionar items
    void agregarItem(const Producto& producto, int cantidad) {
        // Buscar si el producto ya está en el carrito
        auto buscarItem = [&producto](const ItemCarrito& item) {
            return item.getProductoId() == producto.getId();
        };
        
        ItemCarrito* itemExistente = items.buscar(buscarItem);
        
        if (itemExistente) {
            // Si el producto ya está en el carrito, aumentar la cantidad
            itemExistente->aumentarCantidad(cantidad);
        } else {
            // Si no está, crear un nuevo item
            items.insertarFinal(ItemCarrito(producto, cantidad));
        }
        
        calcularTotal();
    }
    
    void eliminarItem(const std::string& productoId) {
        Lista<ItemCarrito> nuevaLista;
        
        // Filtrar la lista, excluyendo el producto a eliminar
        auto filtrarItem = [&productoId](const ItemCarrito& item) {
            return item.getProductoId() != productoId;
        };
        
        nuevaLista = items.filtrar(filtrarItem);
        items = nuevaLista;
        
        calcularTotal();
    }
    
    void actualizarCantidad(const std::string& productoId, int nuevaCantidad) {
        auto actualizarItem = [&productoId, nuevaCantidad](ItemCarrito& item) {
            if (item.getProductoId() == productoId) {
                item.setCantidad(nuevaCantidad);
            }
        };
        
        items.forEach(actualizarItem);
        calcularTotal();
    }
    
    void vaciar() {
        items.vaciar();
        total = 0.0;
        descuento = 0.0;
        impuesto = 0.0;
    }
    
    void calcularTotal() {
        double subtotal = 0.0;
        
        auto sumarSubtotal = [&subtotal](const ItemCarrito& item) {
            subtotal += item.getSubtotal();
        };
        
        items.forEach(sumarSubtotal);
        
        // Aplicar descuento e impuesto
        total = subtotal * (1.0 - descuento / 100.0) * (1.0 + impuesto / 100.0);
    }
    
    // Serialización y deserialización
    // Nota: Para mantener la simplicidad, serializamos solo los metadatos del carrito,
    // no los items individuales.
    std::string aCSV() const {
        return id + "," + clienteId + "," + std::to_string(total) + "," + 
               std::to_string(descuento) + "," + std::to_string(impuesto) + "," + estado;
    }
    
    static Carrito desdeCSV(const std::string& csv) {
        Carrito c;
        std::stringstream ss(csv);
        std::string token;
        
        std::getline(ss, token, ','); c.id = token;
        std::getline(ss, token, ','); c.clienteId = token;
        std::getline(ss, token, ','); c.total = std::stod(token);
        std::getline(ss, token, ','); c.descuento = std::stod(token);
        std::getline(ss, token, ','); c.impuesto = std::stod(token);
        std::getline(ss, token, ','); c.estado = token;
        
        return c;
    }
    
    // Método para mostrar toda la información del carrito
    void mostrar() {
        std::cout << "===== CARRITO DE COMPRAS =====" << std::endl;
        std::cout << "ID: " << id << std::endl;
        std::cout << "Cliente ID: " << clienteId << std::endl;
        std::cout << "Estado: " << estado << std::endl;
        std::cout << std::endl;
        
        std::cout << "ITEMS:" << std::endl;
        std::cout << std::left << std::setw(30) << "Producto"
                  << std::right << std::setw(12) << "Precio Unit."
                  << std::right << std::setw(10) << "Cantidad"
                  << std::right << std::setw(15) << "Subtotal" << std::endl;
        std::cout << std::string(67, '-') << std::endl;
        
        auto mostrarItem = [](const ItemCarrito& item) {
            std::cout << item.obtenerFilaTabla() << std::endl;
        };
        
        items.forEach(mostrarItem);
        
        std::cout << std::string(67, '-') << std::endl;
        std::cout << std::right << std::setw(52) << "Subtotal:"
                  << std::right << std::setw(15) << "$" << std::fixed << std::setprecision(2) << total / (1.0 + impuesto / 100.0) << std::endl;
        if (descuento > 0) {
            std::cout << std::right << std::setw(52) << "Descuento (" << descuento << "%):"
                      << std::right << std::setw(15) << "-$" << std::fixed << std::setprecision(2) << (total / (1.0 + impuesto / 100.0)) * (descuento / 100.0) << std::endl;
        }
        std::cout << std::right << std::setw(52) << "Impuesto (" << impuesto << "%):"
                  << std::right << std::setw(15) << "$" << std::fixed << std::setprecision(2) << total - (total / (1.0 + impuesto / 100.0)) << std::endl;
        std::cout << std::right << std::setw(52) << "TOTAL:"
                  << std::right << std::setw(15) << "$" << std::fixed << std::setprecision(2) << total << std::endl;
    }
    
    // Método para obtener items como vector (útil para algoritmos de ordenamiento)
    std::vector<ItemCarrito> obtenerItemsVector() {
        std::vector<ItemCarrito> resultado;
        
        auto agregarItem = [&resultado](const ItemCarrito& item) {
            resultado.push_back(item);
        };
        
        items.forEach(agregarItem);
        
        return resultado;
    }
    
    // Método para aplicar una función a cada item
    void aplicarFuncionItems(std::function<void(const ItemCarrito&)> funcion) {
        items.forEach(funcion);
    }
};

#endif