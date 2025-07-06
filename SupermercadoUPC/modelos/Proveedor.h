#ifndef PROVEEDOR_H
#define PROVEEDOR_H

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

class Proveedor {
private:
    std::string id;
    std::string nombre;
    std::string contacto;
    std::string email;
    std::string telefono;
    std::string direccion;
    std::vector<std::string> categorias;
    bool activo;

public:
    // Constructores
    Proveedor() : id(""), nombre(""), contacto(""), email(""), 
                  telefono(""), direccion(""), activo(true) {}
    
    Proveedor(std::string _id, std::string _nombre, std::string _contacto, 
              std::string _email, std::string _telefono, std::string _direccion, 
              const std::vector<std::string>& _categorias, bool _activo = true)
        : id(_id), nombre(_nombre), contacto(_contacto), email(_email), 
          telefono(_telefono), direccion(_direccion), categorias(_categorias), activo(_activo) {}
    
    // Getters y setters
    std::string getId() const { return id; }
    void setId(const std::string& _id) { id = _id; }
    
    std::string getNombre() const { return nombre; }
    void setNombre(const std::string& _nombre) { nombre = _nombre; }
    
    std::string getContacto() const { return contacto; }
    void setContacto(const std::string& _contacto) { contacto = _contacto; }
    
    std::string getEmail() const { return email; }
    void setEmail(const std::string& _email) { email = _email; }
    
    std::string getTelefono() const { return telefono; }
    void setTelefono(const std::string& _telefono) { telefono = _telefono; }
    
    std::string getDireccion() const { return direccion; }
    void setDireccion(const std::string& _direccion) { direccion = _direccion; }
    
    std::vector<std::string> getCategorias() const { return categorias; }
    void setCategorias(const std::vector<std::string>& _categorias) { categorias = _categorias; }
    
    void agregarCategoria(const std::string& categoria) {
        categorias.push_back(categoria);
    }
    
    bool isActivo() const { return activo; }
    void setActivo(bool _activo) { activo = _activo; }
    
    // Método para obtener las categorías como una cadena
    std::string getCategoriasString() const {
        if (categorias.empty()) {
            return "";
        }
        
        std::stringstream ss;
        for (size_t i = 0; i < categorias.size(); i++) {
            ss << categorias[i];
            if (i < categorias.size() - 1) {
                ss << "|";
            }
        }
        return ss.str();
    }
    
    // Serialización
    std::string aCSV() const {
        return id + "," + nombre + "," + contacto + "," + email + "," + 
               telefono + "," + direccion + "," + getCategoriasString() + "," + 
               (activo ? "1" : "0");
    }
    
    // Deserialización
    static Proveedor desdeCSV(const std::string& csv) {
        Proveedor p;
        std::stringstream ss(csv);
        std::string token;
        
        std::getline(ss, token, ','); p.id = token;
        std::getline(ss, token, ','); p.nombre = token;
        std::getline(ss, token, ','); p.contacto = token;
        std::getline(ss, token, ','); p.email = token;
        std::getline(ss, token, ','); p.telefono = token;
        std::getline(ss, token, ','); p.direccion = token;
        
        std::getline(ss, token, ',');
        std::stringstream categoriasStream(token);
        std::string categoria;
        while (std::getline(categoriasStream, categoria, '|')) {
            if (!categoria.empty()) {
                p.categorias.push_back(categoria);
            }
        }
        
        std::getline(ss, token, ','); p.activo = (token == "1");
        
        return p;
    }
    
    // Método para mostrar información
    void mostrar() const {
        std::cout << "ID: " << id << std::endl;
        std::cout << "Nombre: " << nombre << std::endl;
        std::cout << "Contacto: " << contacto << std::endl;
        std::cout << "Email: " << email << std::endl;
        std::cout << "Telefono: " << telefono << std::endl;
        std::cout << "Direccion: " << direccion << std::endl;
        std::cout << "Categorias: ";
        for (size_t i = 0; i < categorias.size(); i++) {
            std::cout << categorias[i];
            if (i < categorias.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
        std::cout << "Estado: " << (activo ? "Activo" : "Inactivo") << std::endl;
    }
    
    // Método para mostrar información en formato tabular
    std::string obtenerFilaTabla() const {
        std::stringstream ss;
        ss << std::left << std::setw(10) << id.substr(0, 5)
           << std::left << std::setw(25) << (nombre.length() > 25 ? nombre.substr(0, 25) + "..." : nombre)
           << std::left << std::setw(20) << (contacto.length() > 20 ? contacto.substr(0, 20) + "..." : contacto)
           << std::left << std::setw(30) << (email.length() > 30 ? email.substr(0, 30) + "..." : email)
           << std::left << std::setw(15) << telefono;
        return ss.str();
    }
    
    // Sobrecarga del operador de comparación
    bool operator<(const Proveedor& otro) const {
        return nombre < otro.nombre;
    }
    
    bool operator>(const Proveedor& otro) const {
        return nombre > otro.nombre;
    }
};

#endif