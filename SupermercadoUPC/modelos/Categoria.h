#ifndef CATEGORIA_H
#define CATEGORIA_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "../estructuras/Lista.h"

class Categoria {
private:
    std::string id;
    std::string nombre;
    std::string descripcion;
    bool activa;

public:
    // Constructores
    Categoria() : id(""), nombre(""), descripcion(""), activa(true) {}
    
    Categoria(std::string _id, std::string _nombre, std::string _descripcion, bool _activa = true)
        : id(_id), nombre(_nombre), descripcion(_descripcion), activa(_activa) {}
    
    // Getters y setters
    std::string getId() const { return id; }
    void setId(const std::string& _id) { id = _id; }
    
    std::string getNombre() const { return nombre; }
    void setNombre(const std::string& _nombre) { nombre = _nombre; }
    
    std::string getDescripcion() const { return descripcion; }
    void setDescripcion(const std::string& _descripcion) { descripcion = _descripcion; }
    
    bool isActiva() const { return activa; }
    void setActiva(bool _activa) { activa = _activa; }
    
    // Serialización
    std::string aCSV() const {
        return id + "," + nombre + "," + descripcion + "," + (activa ? "1" : "0");
    }
    
    // Deserialización
    static Categoria desdeCSV(const std::string& csv) {
        Categoria c;
        std::stringstream ss(csv);
        std::string token;
        
        std::getline(ss, token, ','); c.id = token;
        std::getline(ss, token, ','); c.nombre = token;
        std::getline(ss, token, ','); c.descripcion = token;
        std::getline(ss, token, ','); c.activa = (token == "1");
        
        return c;
    }
    
    // Método para mostrar información
    void mostrar() const {
        std::cout << "ID: " << id << std::endl;
        std::cout << "Nombre: " << nombre << std::endl;
        std::cout << "Descripcion: " << descripcion << std::endl;
        std::cout << "Activa: " << (activa ? "Si" : "No") << std::endl;
    }
    
    // Método para mostrar información en formato tabular
    std::string obtenerFilaTabla() const {
        std::stringstream ss;
        ss << std::left << std::setw(10) << id.substr(0, 5)
           << std::left << std::setw(20) << (nombre.length() > 20 ? nombre.substr(0, 20) + "..." : nombre)
           << std::left << std::setw(45) << (descripcion.length() > 45 ? descripcion.substr(0, 45) + "..." : descripcion)
           << std::left << std::setw(10) << (activa ? "Si" : "No");
        return ss.str();
    }
    
    // Sobrecarga del operador de comparación
    bool operator<(const Categoria& otra) const {
        return nombre < otra.nombre;
    }
    
    bool operator>(const Categoria& otra) const {
        return nombre > otra.nombre;
    }
};

#endif