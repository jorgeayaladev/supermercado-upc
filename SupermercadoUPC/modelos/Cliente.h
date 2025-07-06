#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include "../estructuras/Lista.h"

class Cliente {
private:
    std::string id;
    std::string nombre;
    std::string apellido;
    std::string email;
    std::string telefono;
    std::string direccion;
    double totalCompras;
    int puntosAcumulados;
    bool activo;

public:
    // Constructores
    Cliente() : id(""), nombre(""), apellido(""), email(""), telefono(""), 
                direccion(""), totalCompras(0.0), puntosAcumulados(0), activo(true) {}
    
    Cliente(std::string _id, std::string _nombre, std::string _apellido, 
            std::string _email, std::string _telefono, std::string _direccion, 
            double _totalCompras = 0.0, int _puntosAcumulados = 0, bool _activo = true)
        : id(_id), nombre(_nombre), apellido(_apellido), email(_email), 
          telefono(_telefono), direccion(_direccion), totalCompras(_totalCompras), 
          puntosAcumulados(_puntosAcumulados), activo(_activo) {}
    
    // Getters y setters
    std::string getId() const { return id; }
    void setId(const std::string& _id) { id = _id; }
    
    std::string getNombre() const { return nombre; }
    void setNombre(const std::string& _nombre) { nombre = _nombre; }
    
    std::string getApellido() const { return apellido; }
    void setApellido(const std::string& _apellido) { apellido = _apellido; }
    
    std::string getNombreCompleto() const { return nombre + " " + apellido; }
    
    std::string getEmail() const { return email; }
    void setEmail(const std::string& _email) { email = _email; }
    
    std::string getTelefono() const { return telefono; }
    void setTelefono(const std::string& _telefono) { telefono = _telefono; }
    
    std::string getDireccion() const { return direccion; }
    void setDireccion(const std::string& _direccion) { direccion = _direccion; }
    
    double getTotalCompras() const { return totalCompras; }
    void setTotalCompras(double _totalCompras) { totalCompras = _totalCompras; }
    
    int getPuntosAcumulados() const { return puntosAcumulados; }
    void setPuntosAcumulados(int _puntosAcumulados) { puntosAcumulados = _puntosAcumulados; }
    
    bool isActivo() const { return activo; }
    void setActivo(bool _activo) { activo = _activo; }
    
    // Métodos
    void agregarCompra(double monto) {
        totalCompras += monto;
        // Por cada $100 de compra se otorga un punto
        puntosAcumulados += static_cast<int>(monto / 100);
    }
    
    void redimirPuntos(int puntos) {
        if (puntos > 0 && puntos <= puntosAcumulados) {
            puntosAcumulados -= puntos;
        }
    }
    
    // Serialización
    std::string aCSV() const {
        return id + "," + nombre + "," + apellido + "," + email + "," + 
               telefono + "," + direccion + "," + std::to_string(totalCompras) + "," + 
               std::to_string(puntosAcumulados) + "," + (activo ? "1" : "0");
    }
    
    // Deserialización
    static Cliente desdeCSV(const std::string& csv) {
        Cliente c;
        std::stringstream ss(csv);
        std::string token;
        
        std::getline(ss, token, ','); c.id = token;
        std::getline(ss, token, ','); c.nombre = token;
        std::getline(ss, token, ','); c.apellido = token;
        std::getline(ss, token, ','); c.email = token;
        std::getline(ss, token, ','); c.telefono = token;
        std::getline(ss, token, ','); c.direccion = token;
        std::getline(ss, token, ','); c.totalCompras = std::stod(token);
        std::getline(ss, token, ','); c.puntosAcumulados = std::stoi(token);
        std::getline(ss, token, ','); c.activo = (token == "1");
        
        return c;
    }
    
    // Método para mostrar información
    void mostrar() const {
        std::cout << "ID: " << id << std::endl;
        std::cout << "Nombre: " << nombre << " " << apellido << std::endl;
        std::cout << "Email: " << email << std::endl;
        std::cout << "Telefono: " << telefono << std::endl;
        std::cout << "Direccion: " << direccion << std::endl;
        std::cout << "Total de compras: $" << std::fixed << std::setprecision(2) << totalCompras << std::endl;
        std::cout << "Puntos acumulados: " << puntosAcumulados << std::endl;
        std::cout << "Estado: " << (activo ? "Activo" : "Inactivo") << std::endl;
    }
    
    // Método para mostrar información en formato tabular
    std::string obtenerFilaTabla() const {
        std::stringstream ss;
        ss << std::left << std::setw(10) << id.substr(0, 5)
           << std::left << std::setw(20) << (getNombreCompleto().length() > 20 ? getNombreCompleto().substr(0, 20) + "..." : getNombreCompleto())
           << std::left << std::setw(30) << (email.length() > 30 ? email.substr(0, 30) + "..." : email)
           << std::left << std::setw(15) << telefono
           << std::left << std::setw(15) << "$" + std::to_string(int(totalCompras)) + "." + std::to_string(int(totalCompras * 100) % 100)
           << std::left << std::setw(10) << puntosAcumulados;
        return ss.str();
    }
    
    // Sobrecarga del operador de comparación por apellido
    bool operator<(const Cliente& otro) const {
        if (apellido == otro.apellido) {
            return nombre < otro.nombre;
        }
        return apellido < otro.apellido;
    }
    
    bool operator>(const Cliente& otro) const {
        if (apellido == otro.apellido) {
            return nombre > otro.nombre;
        }
        return apellido > otro.apellido;
    }
};

#endif