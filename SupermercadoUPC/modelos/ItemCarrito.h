#ifndef ITEM_CARRITO_H
#define ITEM_CARRITO_H

#include <string>
#include "Producto.h"

class ItemCarrito {
private:
    std::string productoId;
    std::string nombre;
    double precioUnitario;
    int cantidad;
    double subtotal;

public:
    // Constructores
    ItemCarrito() : productoId(""), nombre(""), precioUnitario(0.0), cantidad(0), subtotal(0.0) {}
    
    ItemCarrito(const Producto& producto, int _cantidad)
        : productoId(producto.getId()), nombre(producto.getNombre()),
          precioUnitario(producto.getPrecio()), cantidad(_cantidad) {
        calcularSubtotal();
    }
    
    ItemCarrito(std::string _productoId, std::string _nombre, double _precioUnitario, int _cantidad)
        : productoId(_productoId), nombre(_nombre), precioUnitario(_precioUnitario), cantidad(_cantidad) {
        calcularSubtotal();
    }
    
    // Getters y setters
    std::string getProductoId() const { return productoId; }
    
    std::string getNombre() const { return nombre; }
    
    double getPrecioUnitario() const { return precioUnitario; }
    
    int getCantidad() const { return cantidad; }
    void setCantidad(int _cantidad) {
        cantidad = _cantidad;
        calcularSubtotal();
    }
    
    double getSubtotal() const { return subtotal; }
    
    // Métodos
    void aumentarCantidad(int incremento = 1) {
        cantidad += incremento;
        calcularSubtotal();
    }
    
    void disminuirCantidad(int decremento = 1) {
        if (cantidad > decremento) {
            cantidad -= decremento;
            calcularSubtotal();
        }
    }
    
    void calcularSubtotal() {
        subtotal = precioUnitario * cantidad;
    }
    
    // Serialización
    std::string aCSV() const {
        return productoId + "," + nombre + "," + std::to_string(precioUnitario) + "," + 
               std::to_string(cantidad) + "," + std::to_string(subtotal);
    }
    
    // Deserialización
    static ItemCarrito desdeCSV(const std::string& csv) {
        ItemCarrito item;
        std::stringstream ss(csv);
        std::string token;
        
        std::getline(ss, token, ','); item.productoId = token;
        std::getline(ss, token, ','); item.nombre = token;
        std::getline(ss, token, ','); item.precioUnitario = std::stod(token);
        std::getline(ss, token, ','); item.cantidad = std::stoi(token);
        std::getline(ss, token, ','); item.subtotal = std::stod(token);
        
        return item;
    }
    
    // Método para mostrar información
    void mostrar() const {
        std::cout << "Producto ID: " << productoId << std::endl;
        std::cout << "Nombre: " << nombre << std::endl;
        std::cout << "Precio unitario: $" << std::fixed << std::setprecision(2) << precioUnitario << std::endl;
        std::cout << "Cantidad: " << cantidad << std::endl;
        std::cout << "Subtotal: $" << std::fixed << std::setprecision(2) << subtotal << std::endl;
    }
    
    // Método para mostrar información en formato tabular
    std::string obtenerFilaTabla() const {
        std::stringstream ss;
        ss << std::left << std::setw(30) << (nombre.length() > 28 ? nombre.substr(0, 28) + "..." : nombre)
           << std::right << std::setw(12) << "$" + std::to_string(int(precioUnitario)) + "." + std::to_string(int(precioUnitario * 100) % 100)
           << std::right << std::setw(10) << cantidad
           << std::right << std::setw(15) << "$" + std::to_string(int(subtotal)) + "." + std::to_string(int(subtotal * 100) % 100);
        return ss.str();
    }
};

#endif