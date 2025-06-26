#ifndef VENTA_H
#define VENTA_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "../estructuras/Lista.h"
#include "ItemCarrito.h"

class Venta {
private:
    std::string id;
    std::string clienteId;
    std::string empleadoId;
    std::string fecha;
    std::string hora;
    Lista<ItemCarrito> items;
    double subtotal;
    double descuento;
    double impuesto;
    double total;
    std::string metodoPago;
    std::string estado; // "completada", "cancelada", "devuelta"

public:
    // Constructores
    Venta() : id(""), clienteId(""), empleadoId(""), fecha(""), hora(""), 
              subtotal(0.0), descuento(0.0), impuesto(0.0), total(0.0), 
              metodoPago(""), estado("completada") {}
    
    Venta(std::string _id, std::string _clienteId, std::string _empleadoId, 
          std::string _fecha, std::string _hora, const Lista<ItemCarrito>& _items, 
          double _subtotal, double _descuento, double _impuesto, double _total, 
          std::string _metodoPago, std::string _estado = "completada")
        : id(_id), clienteId(_clienteId), empleadoId(_empleadoId), fecha(_fecha), 
          hora(_hora), items(_items), subtotal(_subtotal), descuento(_descuento), 
          impuesto(_impuesto), total(_total), metodoPago(_metodoPago), estado(_estado) {}
    
    // Getters y setters
    std::string getId() const { return id; }
    void setId(const std::string& _id) { id = _id; }
    
    std::string getClienteId() const { return clienteId; }
    void setClienteId(const std::string& _clienteId) { clienteId = _clienteId; }
    
    std::string getEmpleadoId() const { return empleadoId; }
    void setEmpleadoId(const std::string& _empleadoId) { empleadoId = _empleadoId; }
    
    std::string getFecha() const { return fecha; }
    void setFecha(const std::string& _fecha) { fecha = _fecha; }
    
    std::string getHora() const { return hora; }
    void setHora(const std::string& _hora) { hora = _hora; }
    
    Lista<ItemCarrito>& getItems() { return items; }
    void setItems(const Lista<ItemCarrito>& _items) { items = _items; }
    
    double getSubtotal() const { return subtotal; }
    void setSubtotal(double _subtotal) { subtotal = _subtotal; }
    
    double getDescuento() const { return descuento; }
    void setDescuento(double _descuento) { descuento = _descuento; }
    
    double getImpuesto() const { return impuesto; }
    void setImpuesto(double _impuesto) { impuesto = _impuesto; }
    
    double getTotal() const { return total; }
    void setTotal(double _total) { total = _total; }
    
    std::string getMetodoPago() const { return metodoPago; }
    void setMetodoPago(const std::string& _metodoPago) { metodoPago = _metodoPago; }
    
    std::string getEstado() const { return estado; }
    void setEstado(const std::string& _estado) { estado = _estado; }
    
    // Serialización
    std::string aCSV() const {
        return id + "," + clienteId + "," + empleadoId + "," + fecha + "," + 
               hora + "," + std::to_string(subtotal) + "," + std::to_string(descuento) + "," + 
               std::to_string(impuesto) + "," + std::to_string(total) + "," + 
               metodoPago + "," + estado;
    }
    
    // Deserialización
    static Venta desdeCSV(const std::string& csv) {
        Venta v;
        std::stringstream ss(csv);
        std::string token;
        
        std::getline(ss, token, ','); v.id = token;
        std::getline(ss, token, ','); v.clienteId = token;
        std::getline(ss, token, ','); v.empleadoId = token;
        std::getline(ss, token, ','); v.fecha = token;
        std::getline(ss, token, ','); v.hora = token;
        std::getline(ss, token, ','); v.subtotal = std::stod(token);
        std::getline(ss, token, ','); v.descuento = std::stod(token);
        std::getline(ss, token, ','); v.impuesto = std::stod(token);
        std::getline(ss, token, ','); v.total = std::stod(token);
        std::getline(ss, token, ','); v.metodoPago = token;
        std::getline(ss, token, ','); v.estado = token;
        
        return v;
    }
    
    // Método para mostrar información
    void mostrar() {
        std::cout << "====== TICKET DE VENTA ======" << std::endl;
        std::cout << "ID: " << id << std::endl;
        std::cout << "Fecha: " << fecha << " " << hora << std::endl;
        std::cout << "Cliente ID: " << clienteId << std::endl;
        std::cout << "Atendido por: " << empleadoId << std::endl;
        std::cout << std::endl;
        
        std::cout << "PRODUCTOS:" << std::endl;
        std::cout << std::left << std::setw(30) << "Producto"
                  << std::right << std::setw(12) << "Precio Unit."
                  << std::right << std::setw(10) << "Cantidad"
                  << std::right << std::setw(15) << "Subtotal" << std::endl;
        std::cout << std::string(67, '-') << std::endl;
        
        items.forEach([](const ItemCarrito& item) {
            std::cout << item.obtenerFilaTabla() << std::endl;
        });
        
        std::cout << std::string(67, '-') << std::endl;
        std::cout << std::right << std::setw(52) << "Subtotal:"
                  << std::right << std::setw(15) << "$" << std::fixed << std::setprecision(2) << subtotal << std::endl;
        
        if (descuento > 0) {
            std::cout << std::right << std::setw(52) << "Descuento (" << descuento << "%):"
                      << std::right << std::setw(15) << "-$" << std::fixed << std::setprecision(2) << (subtotal * descuento / 100.0) << std::endl;
        }
        
        std::cout << std::right << std::setw(52) << "Impuesto (" << impuesto << "%):"
                  << std::right << std::setw(15) << "$" << std::fixed << std::setprecision(2) << (subtotal * (1.0 - descuento / 100.0) * impuesto / 100.0) << std::endl;
        
        std::cout << std::right << std::setw(52) << "TOTAL:"
                  << std::right << std::setw(15) << "$" << std::fixed << std::setprecision(2) << total << std::endl;
        
        std::cout << std::endl;
        std::cout << "Metodo de pago: " << metodoPago << std::endl;
        std::cout << "Estado: " << estado << std::endl;
        std::cout << "=============================" << std::endl;
    }
    
    // Método para mostrar información en formato tabular (resumen)
    std::string obtenerFilaTabla() const {
        std::stringstream ss;
        ss << std::left << std::setw(10) << id.substr(0, 8)
           << std::left << std::setw(12) << fecha
           << std::left << std::setw(8) << hora
           << std::left << std::setw(10) << clienteId.substr(0, 8)
           << std::right << std::setw(12) << "$" + std::to_string(int(total)) + "." + std::to_string(int(total * 100) % 100)
           << std::left << std::setw(15) << (metodoPago.length() > 13 ? metodoPago.substr(0, 13) + "..." : metodoPago)
           << std::left << std::setw(10) << estado;
        return ss.str();
    }
    
    // Sobrecarga del operador de comparación por fecha y hora
    bool operator<(const Venta& otra) const {
        if (fecha == otra.fecha) {
            return hora < otra.hora;
        }
        return fecha < otra.fecha;
    }
    
    bool operator>(const Venta& otra) const {
        if (fecha == otra.fecha) {
            return hora > otra.hora;
        }
        return fecha > otra.fecha;
    }
};

#endif