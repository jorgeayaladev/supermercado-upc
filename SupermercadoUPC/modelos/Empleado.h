#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

class Empleado {
private:
    std::string id;
    std::string nombre;
    std::string apellido;
    std::string cargo;
    std::string email;
    std::string telefono;
    double salario;
    std::string fechaContratacion;
    bool activo;

public:
    // Constructores
    Empleado() : id(""), nombre(""), apellido(""), cargo(""), email(""), 
                 telefono(""), salario(0.0), fechaContratacion(""), activo(true) {}
    
    Empleado(std::string _id, std::string _nombre, std::string _apellido, 
             std::string _cargo, std::string _email, std::string _telefono, 
             double _salario, std::string _fechaContratacion, bool _activo = true)
        : id(_id), nombre(_nombre), apellido(_apellido), cargo(_cargo), 
          email(_email), telefono(_telefono), salario(_salario), 
          fechaContratacion(_fechaContratacion), activo(_activo) {}
    
    // Getters y setters
    std::string getId() const { return id; }
    void setId(const std::string& _id) { id = _id; }
    
    std::string getNombre() const { return nombre; }
    void setNombre(const std::string& _nombre) { nombre = _nombre; }
    
    std::string getApellido() const { return apellido; }
    void setApellido(const std::string& _apellido) { apellido = _apellido; }
    
    std::string getNombreCompleto() const { return nombre + " " + apellido; }
    
    std::string getCargo() const { return cargo; }
    void setCargo(const std::string& _cargo) { cargo = _cargo; }
    
    std::string getEmail() const { return email; }
    void setEmail(const std::string& _email) { email = _email; }
    
    std::string getTelefono() const { return telefono; }
    void setTelefono(const std::string& _telefono) { telefono = _telefono; }
    
    double getSalario() const { return salario; }
    void setSalario(double _salario) { salario = _salario; }
    
    std::string getFechaContratacion() const { return fechaContratacion; }
    void setFechaContratacion(const std::string& _fechaContratacion) { fechaContratacion = _fechaContratacion; }
    
    bool isActivo() const { return activo; }
    void setActivo(bool _activo) { activo = _activo; }
    
    // Métodos
    double calcularSalarioAnual() const {
        return salario * 12;
    }
    
    // Serialización
    std::string aCSV() const {
        return id + "," + nombre + "," + apellido + "," + cargo + "," + 
               email + "," + telefono + "," + std::to_string(salario) + "," + 
               fechaContratacion + "," + (activo ? "1" : "0");
    }
    
    // Deserialización
    static Empleado desdeCSV(const std::string& csv) {
        Empleado e;
        std::stringstream ss(csv);
        std::string token;
        
        std::getline(ss, token, ','); e.id = token;
        std::getline(ss, token, ','); e.nombre = token;
        std::getline(ss, token, ','); e.apellido = token;
        std::getline(ss, token, ','); e.cargo = token;
        std::getline(ss, token, ','); e.email = token;
        std::getline(ss, token, ','); e.telefono = token;
        std::getline(ss, token, ','); e.salario = std::stod(token);
        std::getline(ss, token, ','); e.fechaContratacion = token;
        std::getline(ss, token, ','); e.activo = (token == "1");
        
        return e;
    }
    
    // Método para mostrar información
    void mostrar() const {
        std::cout << "ID: " << id << std::endl;
        std::cout << "Nombre: " << nombre << " " << apellido << std::endl;
        std::cout << "Cargo: " << cargo << std::endl;
        std::cout << "Email: " << email << std::endl;
        std::cout << "Telefono: " << telefono << std::endl;
        std::cout << "Salario: $" << std::fixed << std::setprecision(2) << salario << std::endl;
        std::cout << "Fecha de contratacion: " << fechaContratacion << std::endl;
        std::cout << "Estado: " << (activo ? "Activo" : "Inactivo") << std::endl;
    }
    
    // Método para mostrar información en formato tabular
    std::string obtenerFilaTabla() const {
        std::stringstream ss;
        ss << std::left << std::setw(5) << id.substr(0, 5)
           << std::left << std::setw(25) << (getNombreCompleto().length() > 23 ? getNombreCompleto().substr(0, 23) + "..." : getNombreCompleto())
           << std::left << std::setw(15) << (cargo.length() > 13 ? cargo.substr(0, 13) + "..." : cargo)
           << std::right << std::setw(12) << "$" + std::to_string(int(salario)) + "." + std::to_string(int(salario * 100) % 100)
           << std::left << std::setw(13) << fechaContratacion
           << std::left << std::setw(10) << (activo ? "Activo" : "Inactivo");
        return ss.str();
    }
    
    // Sobrecarga del operador de comparación por apellido
    bool operator<(const Empleado& otro) const {
        if (apellido == otro.apellido) {
            return nombre < otro.nombre;
        }
        return apellido < otro.apellido;
    }
    
    bool operator>(const Empleado& otro) const {
        if (apellido == otro.apellido) {
            return nombre > otro.nombre;
        }
        return apellido > otro.apellido;
    }
};

#endif