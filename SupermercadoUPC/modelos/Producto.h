#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <functional>
#include "../estructuras/Lista.h"

class Producto {
private:
    std::string id;
    std::string nombre;
    std::string descripcion;
    double precio;
    int stock;
    std::string categoria;
    std::string codigoBarras;
    bool disponible;

public:
    // Constructores
    Producto() : id(""), nombre(""), descripcion(""), precio(0.0), stock(0), 
                 categoria(""), codigoBarras(""), disponible(true) {}
    
    Producto(std::string _id, std::string _nombre, std::string _descripcion, 
             double _precio, int _stock, std::string _categoria, 
             std::string _codigoBarras, bool _disponible = true)
        : id(_id), nombre(_nombre), descripcion(_descripcion), precio(_precio), 
          stock(_stock), categoria(_categoria), codigoBarras(_codigoBarras), 
          disponible(_disponible) {}
    
    // Getters y setters
    std::string getId() const { return id; }
    void setId(const std::string& _id) { id = _id; }
    
    std::string getNombre() const { return nombre; }
    void setNombre(const std::string& _nombre) { nombre = _nombre; }
    
    std::string getDescripcion() const { return descripcion; }
    void setDescripcion(const std::string& _descripcion) { descripcion = _descripcion; }
    
    double getPrecio() const { return precio; }
    void setPrecio(double _precio) { precio = _precio; }
    
    int getStock() const { return stock; }
    void setStock(int _stock) { stock = _stock; }
    
    std::string getCategoria() const { return categoria; }
    void setCategoria(const std::string& _categoria) { categoria = _categoria; }
    
    std::string getCodigoBarras() const { return codigoBarras; }
    void setCodigoBarras(const std::string& _codigoBarras) { codigoBarras = _codigoBarras; }
    
    bool isDisponible() const { return disponible; }
    void setDisponible(bool _disponible) { disponible = _disponible; }
    
    // Métodos
    void reducirStock(int cantidad) {
        if (cantidad > 0 && cantidad <= stock) {
            stock -= cantidad;
            if (stock == 0) {
                disponible = false;
            }
        }
    }
    
    void aumentarStock(int cantidad) {
        if (cantidad > 0) {
            stock += cantidad;
            disponible = true;
        }
    }
    
    // Método para serializar a formato CSV
    std::string aCSV() const {
        return id + "," + nombre + "," + descripcion + "," + 
               std::to_string(precio) + "," + std::to_string(stock) + "," + 
               categoria + "," + codigoBarras + "," + 
               (disponible ? "1" : "0");
    }
    
    // Método para deserializar desde formato CSV
    static Producto desdeCSV(const std::string& csv) {
        Producto p;
        std::stringstream ss(csv);
        std::string token;
        
        std::getline(ss, token, ','); p.id = token;
        std::getline(ss, token, ','); p.nombre = token;
        std::getline(ss, token, ','); p.descripcion = token;
        std::getline(ss, token, ','); p.precio = std::stod(token);
        std::getline(ss, token, ','); p.stock = std::stoi(token);
        std::getline(ss, token, ','); p.categoria = token;
        std::getline(ss, token, ','); p.codigoBarras = token;
        std::getline(ss, token, ','); p.disponible = (token == "1");
        
        return p;
    }
    
    // Método para mostrar información
    void mostrar() const {
        std::cout << "ID: " << id << std::endl;
        std::cout << "Nombre: " << nombre << std::endl;
        std::cout << "Descripcion: " << descripcion << std::endl;
        std::cout << "Precio: $" << precio << std::endl;
        std::cout << "Stock: " << stock << std::endl;
        std::cout << "Categoria: " << categoria << std::endl;
        std::cout << "Codigo de barras: " << codigoBarras << std::endl;
        std::cout << "Disponible: " << (disponible ? "Si" : "No") << std::endl;
    }
    
    // Método para mostrar información en formato tabular
    std::string obtenerFilaTabla() const {
        std::stringstream ss;
        ss << std::left << std::setw(10) << id.substr(0, 5)
           << std::left << std::setw(25) << (nombre.length() > 18 ? nombre.substr(0, 18) + "..." : nombre)
           << std::left << std::setw(15) << "$" + std::to_string(int(precio)) + "." + std::to_string(int(precio * 100) % 100)
           << std::left << std::setw(15) << stock
           << std::left << std::setw(20) << (categoria.length() > 13 ? categoria.substr(0, 13) + "..." : categoria)
           << std::left << std::setw(15) << (disponible ? "Si" : "No");
        return ss.str();
    }
    
    // Sobrecarga del operador de comparación
    bool operator<(const Producto& otro) const {
        return nombre < otro.nombre;
    }
    
    bool operator>(const Producto& otro) const {
        return nombre > otro.nombre;
    }
};

#endif