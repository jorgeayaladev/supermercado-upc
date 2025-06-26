#ifndef SUCURSAL_H
#define SUCURSAL_H

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

class Sucursal {
private:
    std::string id;
    std::string nombre;
    std::string direccion;
    std::string telefono;
    std::string gerente;
    double ventasMensuales;
    int numeroEmpleados;
    bool activa;

public:
    // Constructores
    Sucursal() : id(""), nombre(""), direccion(""), telefono(""), 
                 gerente(""), ventasMensuales(0.0), numeroEmpleados(0), activa(true) {}
    
    Sucursal(std::string _id, std::string _nombre, std::string _direccion,
             std::string _telefono, std::string _gerente, double _ventasMensuales = 0.0,
             int _numeroEmpleados = 0, bool _activa = true)
        : id(_id), nombre(_nombre), direccion(_direccion), telefono(_telefono),
          gerente(_gerente), ventasMensuales(_ventasMensuales), 
          numeroEmpleados(_numeroEmpleados), activa(_activa) {}
    
    // Getters y setters
    std::string getId() const { return id; }
    void setId(const std::string& _id) { id = _id; }
    
    std::string getNombre() const { return nombre; }
    void setNombre(const std::string& _nombre) { nombre = _nombre; }
    
    std::string getDireccion() const { return direccion; }
    void setDireccion(const std::string& _direccion) { direccion = _direccion; }
    
    std::string getTelefono() const { return telefono; }
    void setTelefono(const std::string& _telefono) { telefono = _telefono; }
    
    std::string getGerente() const { return gerente; }
    void setGerente(const std::string& _gerente) { gerente = _gerente; }
    
    double getVentasMensuales() const { return ventasMensuales; }
    void setVentasMensuales(double _ventasMensuales) { ventasMensuales = _ventasMensuales; }
    
    int getNumeroEmpleados() const { return numeroEmpleados; }
    void setNumeroEmpleados(int _numeroEmpleados) { numeroEmpleados = _numeroEmpleados; }
    
    bool isActiva() const { return activa; }
    void setActiva(bool _activa) { activa = _activa; }
    
    // Métodos
    void agregarVenta(double monto) {
        ventasMensuales += monto;
    }
    
    double calcularVentasAnuales() const {
        return ventasMensuales * 12;
    }
    
    // Serialización
    std::string aCSV() const {
        return id + "," + nombre + "," + direccion + "," + telefono + "," +
               gerente + "," + std::to_string(ventasMensuales) + "," +
               std::to_string(numeroEmpleados) + "," + (activa ? "1" : "0");
    }
    
    // Deserialización
    static Sucursal desdeCSV(const std::string& csv) {
        Sucursal s;
        std::stringstream ss(csv);
        std::string token;
        
        std::getline(ss, token, ','); s.id = token;
        std::getline(ss, token, ','); s.nombre = token;
        std::getline(ss, token, ','); s.direccion = token;
        std::getline(ss, token, ','); s.telefono = token;
        std::getline(ss, token, ','); s.gerente = token;
        std::getline(ss, token, ','); s.ventasMensuales = std::stod(token);
        std::getline(ss, token, ','); s.numeroEmpleados = std::stoi(token);
        std::getline(ss, token, ','); s.activa = (token == "1");
        
        return s;
    }
    
    // Método para mostrar información
    void mostrar() const {
        std::cout << "ID: " << id << std::endl;
        std::cout << "Nombre: " << nombre << std::endl;
        std::cout << "Direccion: " << direccion << std::endl;
        std::cout << "Telefono: " << telefono << std::endl;
        std::cout << "Gerente: " << gerente << std::endl;
        std::cout << "Ventas mensuales: $" << std::fixed << std::setprecision(2) << ventasMensuales << std::endl;
        std::cout << "Numero de empleados: " << numeroEmpleados << std::endl;
        std::cout << "Estado: " << (activa ? "Activa" : "Inactiva") << std::endl;
    }
    
    // Método para mostrar información en formato tabular
    std::string obtenerFilaTabla() const {
        std::stringstream ss;
        ss << std::left << std::setw(5) << id.substr(0, 5)
           << std::left << std::setw(20) << (nombre.length() > 18 ? nombre.substr(0, 18) + "..." : nombre)
           << std::left << std::setw(25) << (direccion.length() > 23 ? direccion.substr(0, 23) + "..." : direccion)
           << std::left << std::setw(15) << telefono
           << std::right << std::setw(12) << "$" + std::to_string(int(ventasMensuales))
           << std::right << std::setw(8) << numeroEmpleados
           << std::left << std::setw(10) << (activa ? "Activa" : "Inactiva");
        return ss.str();
    }
    
    // Sobrecarga del operador de comparación
    bool operator<(const Sucursal& otra) const {
        return nombre < otra.nombre;
    }
    
    bool operator>(const Sucursal& otra) const {
        return nombre > otra.nombre;
    }
    
    bool operator==(const Sucursal& otra) const {
        return id == otra.id;
    }
};

#endif