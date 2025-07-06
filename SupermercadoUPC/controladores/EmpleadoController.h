#ifndef EMPLEADO_CONTROLLER_H
#define EMPLEADO_CONTROLLER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>
#include "../modelos/Empleado.h"
#include "../estructuras/Lista.h"
#include "../utilidades/Utilidades.h"
#include "../utilidades/Ordenamiento.h"

class EmpleadoController {
private:
    Lista<Empleado> empleados;
    const std::string archivoEmpleados = "datos/empleados.txt";

public:
    // Constructor
    EmpleadoController() {
        cargarEmpleados();
    }
    
    // Métodos CRUD
    
    // Crear un nuevo empleado
    bool crear(const Empleado& empleado) {
        // Verificar si ya existe un empleado con el mismo ID o email
        auto buscarExistente = [&empleado](const Empleado& e) {
            return e.getId() == empleado.getId() || 
                   Utilidades::aMinusculas(e.getEmail()) == Utilidades::aMinusculas(empleado.getEmail());
        };
        
        if (empleados.buscar(buscarExistente) != nullptr) {
            return false; // Ya existe un empleado con ese ID o email
        }
        
        empleados.insertarFinal(empleado);
        guardarEmpleados();
        return true;
    }
    
    // Obtener un empleado por ID
    Empleado* obtenerPorId(const std::string& id) {
        auto buscarPorId = [&id](const Empleado& e) {
            return e.getId() == id;
        };
        
        return empleados.buscar(buscarPorId);
    }
    
    // Obtener un empleado por email
    Empleado* obtenerPorEmail(const std::string& email) {
        auto buscarPorEmail = [&email](const Empleado& e) {
            return Utilidades::aMinusculas(e.getEmail()) == Utilidades::aMinusculas(email);
        };
        
        return empleados.buscar(buscarPorEmail);
    }
    
    // Actualizar un empleado existente
    bool actualizar(const Empleado& empleado) {
        bool encontrado = false;
        
        auto actualizarEmpleado = [&empleado, &encontrado](Empleado& e) {
            if (e.getId() == empleado.getId()) {
                e = empleado;
                encontrado = true;
            }
        };
        
        empleados.forEach(actualizarEmpleado);
        
        if (encontrado) {
            guardarEmpleados();
        }
        
        return encontrado;
    }
    
    // Eliminar un empleado (marcándolo como inactivo)
    bool eliminar(const std::string& id) {
        bool encontrado = false;
        
        auto eliminarEmpleado = [&id, &encontrado](Empleado& e) {
            if (e.getId() == id) {
                e.setActivo(false);
                encontrado = true;
            }
        };
        
        empleados.forEach(eliminarEmpleado);
        
        if (encontrado) {
            guardarEmpleados();
        }
        
        return encontrado;
    }
    
    // Obtener todos los empleados
    Lista<Empleado>& obtenerTodos() { return empleados; }
	int obtenerCantidad() const { return empleados.getTamano(); }
    
    // Obtener empleados activos
    Lista<Empleado> obtenerActivos() {
        auto filtrarActivos = [](const Empleado& e) {
            return e.isActivo();
        };
        
        return empleados.filtrar(filtrarActivos);
    }
    
    // Obtener empleados por cargo
    Lista<Empleado> obtenerPorCargo(const std::string& cargo) {
        auto filtrarPorCargo = [&cargo](const Empleado& e) {
            return e.getCargo() == cargo && e.isActivo();
        };
        
        return empleados.filtrar(filtrarPorCargo);
    }
    
    // Buscar empleados por nombre o apellido
    Lista<Empleado> buscarPorNombre(const std::string& busqueda) {
        auto filtrarPorNombre = [&busqueda](const Empleado& e) {
            std::string nombreCompleto = Utilidades::aMinusculas(e.getNombre() + " " + e.getApellido());
            std::string busquedaLower = Utilidades::aMinusculas(busqueda);
            return nombreCompleto.find(busquedaLower) != std::string::npos && e.isActivo();
        };
        
        return empleados.filtrar(filtrarPorNombre);
    }
    
    // Ordenar empleados por apellido (A-Z)
    std::vector<Empleado> ordenarPorApellidoAsc() {
        std::vector<Empleado> empleadosVector;
        
        auto agregarAVector = [&empleadosVector](const Empleado& e) {
            if (e.isActivo()) {
                empleadosVector.push_back(e);
            }
        };
        
        empleados.forEach(agregarAVector);
        
        Ordenamiento<Empleado>::heapSort(empleadosVector);
        
        return empleadosVector;
    }
    
    // Ordenar empleados por salario (mayor a menor)
    std::vector<Empleado> ordenarPorSalarioDesc() {
        std::vector<Empleado> empleadosVector;
        
        auto agregarAVector = [&empleadosVector](const Empleado& e) {
            if (e.isActivo()) {
                empleadosVector.push_back(e);
            }
        };
        
        empleados.forEach(agregarAVector);
        
        Ordenamiento<Empleado>::ordenarPersonalizado(empleadosVector, 
            [](const Empleado& a, const Empleado& b) { 
                return a.getSalario() > b.getSalario(); 
            });
        
        return empleadosVector;
    }
    
    // Cargar empleados desde archivo
    void cargarEmpleados() {
        std::ifstream archivo(archivoEmpleados);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo de empleados. Se creará uno nuevo al guardar." << std::endl;
            // Crear empleados de ejemplo si no existe el archivo
            generarEmpleadosEjemplo();
            return;
        }
        
        std::string linea;
        while (std::getline(archivo, linea)) {
            if (!linea.empty()) {
                Empleado empleado = Empleado::desdeCSV(linea);
                empleados.insertarFinal(empleado);
            }
        }
        
        archivo.close();
    }
    
    // Guardar empleados en archivo
    void guardarEmpleados() {        
        std::ofstream archivo(archivoEmpleados);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para guardar los empleados." << std::endl;
            return;
        }
        
        auto guardarEmpleado = [&archivo](const Empleado& e) {
            archivo << e.aCSV() << std::endl;
        };
        
        empleados.forEach(guardarEmpleado);
        
        archivo.close();
    }
    
private:
    // Generar empleados de ejemplo
    void generarEmpleadosEjemplo() {
        empleados.insertarFinal(Empleado("E001", "Roberto", "Gomez", "Gerente", "robertogomez@supermercado.com", "930284332", 3500.00, "2020-01-15"));
        empleados.insertarFinal(Empleado("E002", "Sofia", "Hernandez", "Cajero", "sofiahernandez@supermercado.com", "904324323", 1800.00, "2021-03-10"));
        empleados.insertarFinal(Empleado("E003", "Luis", "Torres", "Almacenista", "luistorres@supermercado.com", "984323383", 1600.00, "2021-05-22"));
        empleados.insertarFinal(Empleado("E004", "Carmen", "Diaz", "Cajero", "carmendiaz@supermercado.com", "984373847", 1800.00, "2022-02-01"));
        empleados.insertarFinal(Empleado("E005", "Miguel", "Sanchez", "Supervisor", "miguelsanchez@supermercado.com", "983743328", 2500.00, "2020-11-05"));
        
        guardarEmpleados();
    }
};

#endif