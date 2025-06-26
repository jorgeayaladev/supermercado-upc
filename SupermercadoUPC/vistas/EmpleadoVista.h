#ifndef EMPLEADO_VISTA_H
#define EMPLEADO_VISTA_H

#include <string>
#include <iostream>
#include <iomanip>
#include "../modelos/Empleado.h"
#include "../controladores/EmpleadoController.h"
#include "../utilidades/Utilidades.h"
#include "Menu.h"

class EmpleadoVista {
private:
    EmpleadoController& empleadoController;

public:
    EmpleadoVista(EmpleadoController& _empleadoController)
        : empleadoController(_empleadoController) {}
    
    void mostrarMenu() {
        bool salir = false;
        
        while (!salir) {
            Menu menu("GESTION DE EMPLEADOS");
            menu.agregarOpcion("Listar todos los empleados");
            menu.agregarOpcion("Buscar empleado");
            menu.agregarOpcion("Agregar nuevo empleado");
            menu.agregarOpcion("Editar empleado");
            menu.agregarOpcion("Eliminar empleado");
            menu.agregarOpcion("Listar por cargo");
            menu.agregarOpcion("Ordenar por salario");
            menu.agregarOpcion("Volver al menu principal");
            
            int opcion = menu.mostrar();
            
            switch (opcion) {
                case 1: listarEmpleados(); break;
                case 2: buscarEmpleado(); break;
                case 3: agregarEmpleado(); break;
                case 4: editarEmpleado(); break;
                case 5: eliminarEmpleado(); break;
                case 6: listarPorCargo(); break;
                case 7: ordenarPorSalario(); break;
                case 8: salir = true; break;
            }
        }
    }
    
    void listarEmpleados() {
        Utilidades::limpiarPantalla();
        std::cout << "===== LISTADO DE EMPLEADOS =====" << std::endl;
        
        mostrarTablaEmpleados();
        
        Utilidades::pausar();
    }
    
    void buscarEmpleado() {
        Utilidades::limpiarPantalla();
        std::cout << "===== BUSCAR EMPLEADO =====" << std::endl;
        
        std::cout << "Ingrese nombre o apellido a buscar: ";
        std::string busqueda;
        std::getline(std::cin, busqueda);
        
        if (busqueda.empty()) {
            Menu::mostrarError("La busqueda no puede estar vacia");
            return;
        }
        
        Lista<Empleado> resultados = empleadoController.buscarPorNombre(busqueda);
        
        if (resultados.estaVacia()) {
            Menu::mostrarInfo("No se encontraron empleados");
            return;
        }
        
        std::cout << "\nEmpleados encontrados:" << std::endl;
        mostrarTablaEmpleados(resultados);
        
        Utilidades::pausar();
    }
    
    void agregarEmpleado() {
        Utilidades::limpiarPantalla();
        std::cout << "===== AGREGAR EMPLEADO =====" << std::endl;
        
        std::string nombre, apellido, cargo, email, telefono;
        double salario;
        
        std::cout << "Nombre: ";
        std::getline(std::cin, nombre);
        
        if (nombre.empty()) {
            Menu::mostrarError("El nombre no puede estar vacio");
            return;
        }
        
        std::cout << "Apellido: ";
        std::getline(std::cin, apellido);
        
        if (apellido.empty()) {
            Menu::mostrarError("El apellido no puede estar vacio");
            return;
        }
        
        std::cout << "Cargo: ";
        std::getline(std::cin, cargo);
        
        if (cargo.empty()) {
            Menu::mostrarError("El cargo no puede estar vacio");
            return;
        }
        
        std::cout << "Email: ";
        std::getline(std::cin, email);
        
        if (email.empty()) {
            Menu::mostrarError("El email no puede estar vacio");
            return;
        }
        
        std::cout << "Telefono: ";
        std::getline(std::cin, telefono);
        
        std::string salarioStr;
        std::cout << "Salario: ";
        std::getline(std::cin, salarioStr);
        
        try {
            salario = std::stod(salarioStr);
            if (salario <= 0) {
                throw std::invalid_argument("El salario debe ser mayor que cero");
            }
        } catch (const std::exception& e) {
            Menu::mostrarError("Salario invalido");
            return;
        }
        
        std::string id = "E" + Utilidades::generarId().substr(0, 8);
        Empleado nuevoEmpleado(id, nombre, apellido, cargo, email, telefono, 
                              salario, Utilidades::obtenerFechaActual());
        
        if (empleadoController.crear(nuevoEmpleado)) {
            Menu::mostrarExito("Empleado agregado correctamente");
        } else {
            Menu::mostrarError("No se pudo agregar el empleado");
        }
    }
    
    void editarEmpleado() {
        Utilidades::limpiarPantalla();
        std::cout << "===== EDITAR EMPLEADO =====" << std::endl;
        
        std::cout << "Ingrese ID del empleado a editar: ";
        std::string id;
        std::getline(std::cin, id);
        
        Empleado* empleado = empleadoController.obtenerPorId(id);
        
        if (!empleado) {
            Menu::mostrarError("No se encontro el empleado");
            return;
        }
        
        std::cout << "\nEmpleado encontrado:" << std::endl;
        empleado->mostrar();
        
        if (!Menu::confirmar("\n¿Desea editar este empleado?")) {
            return;
        }
        
        std::string nombre, apellido, cargo, email, telefono;
        double salario;
        bool activo;
        
        std::cout << "\nNuevo nombre (" << empleado->getNombre() << "): ";
        std::getline(std::cin, nombre);
        if (nombre.empty()) {
            nombre = empleado->getNombre();
        }
        
        std::cout << "Nuevo apellido (" << empleado->getApellido() << "): ";
        std::getline(std::cin, apellido);
        if (apellido.empty()) {
            apellido = empleado->getApellido();
        }
        
        std::cout << "Nuevo cargo (" << empleado->getCargo() << "): ";
        std::getline(std::cin, cargo);
        if (cargo.empty()) {
            cargo = empleado->getCargo();
        }
        
        std::cout << "Nuevo email (" << empleado->getEmail() << "): ";
        std::getline(std::cin, email);
        if (email.empty()) {
            email = empleado->getEmail();
        }
        
        std::cout << "Nuevo telefono (" << empleado->getTelefono() << "): ";
        std::getline(std::cin, telefono);
        if (telefono.empty()) {
            telefono = empleado->getTelefono();
        }
        
        std::string salarioStr;
        std::cout << "Nuevo salario (" << empleado->getSalario() << "): ";
        std::getline(std::cin, salarioStr);
        
        if (salarioStr.empty()) {
            salario = empleado->getSalario();
        } else {
            try {
                salario = std::stod(salarioStr);
                if (salario <= 0) {
                    throw std::invalid_argument("El salario debe ser mayor que cero");
                }
            } catch (const std::exception& e) {
                Menu::mostrarError("Salario invalido. Se mantendra el valor original");
                salario = empleado->getSalario();
            }
        }
        
        std::string activoStr;
        std::cout << "¿Activo? (S/N) (" << (empleado->isActivo() ? "S" : "N") << "): ";
        std::getline(std::cin, activoStr);
        
        if (activoStr.empty()) {
            activo = empleado->isActivo();
        } else {
            activo = (Utilidades::aMinusculas(activoStr) == "s" || 
                     Utilidades::aMinusculas(activoStr) == "si" ||
                     Utilidades::aMinusculas(activoStr) == "y" ||
                     Utilidades::aMinusculas(activoStr) == "yes");
        }
        
        Empleado empleadoActualizado(empleado->getId(), nombre, apellido, cargo, 
                                   email, telefono, salario, 
                                   empleado->getFechaContratacion(), activo);
        
        if (empleadoController.actualizar(empleadoActualizado)) {
            Menu::mostrarExito("Empleado actualizado correctamente");
        } else {
            Menu::mostrarError("No se pudo actualizar el empleado");
        }
    }
    
    void eliminarEmpleado() {
        Utilidades::limpiarPantalla();
        std::cout << "===== ELIMINAR EMPLEADO =====" << std::endl;
        
        std::cout << "Ingrese ID del empleado a eliminar: ";
        std::string id;
        std::getline(std::cin, id);
        
        Empleado* empleado = empleadoController.obtenerPorId(id);
        
        if (!empleado) {
            Menu::mostrarError("No se encontro el empleado");
            return;
        }
        
        std::cout << "\nEmpleado encontrado:" << std::endl;
        empleado->mostrar();
        
        if (!Menu::confirmar("\n¿Esta seguro de que desea eliminar este empleado?")) {
            return;
        }
        
        if (empleadoController.eliminar(id)) {
            Menu::mostrarExito("Empleado eliminado correctamente");
        } else {
            Menu::mostrarError("No se pudo eliminar el empleado");
        }
    }
    
    void listarPorCargo() {
        Utilidades::limpiarPantalla();
        std::cout << "===== EMPLEADOS POR CARGO =====" << std::endl;
        
        std::cout << "Ingrese cargo a buscar: ";
        std::string cargo;
        std::getline(std::cin, cargo);
        
        if (cargo.empty()) {
            Menu::mostrarError("El cargo no puede estar vacio");
            return;
        }
        
        Lista<Empleado> empleados = empleadoController.obtenerPorCargo(cargo);
        
        if (empleados.estaVacia()) {
            Menu::mostrarInfo("No hay empleados con el cargo especificado");
            return;
        }
        
        std::cout << "\nEmpleados con cargo '" << cargo << "':" << std::endl;
        mostrarTablaEmpleados(empleados);
        
        Utilidades::pausar();
    }
    
    void ordenarPorSalario() {
        Utilidades::limpiarPantalla();
        std::cout << "===== EMPLEADOS ORDENADOS POR SALARIO =====" << std::endl;
        
        std::vector<Empleado> empleados = empleadoController.ordenarPorSalarioDesc();
        
        if (empleados.empty()) {
            Menu::mostrarInfo("No hay empleados registrados");
            return;
        }
        
        std::cout << "\nEmpleados ordenados por salario (mayor a menor):" << std::endl;
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;
        std::cout << std::left << std::setw(5) << "ID"
                  << std::left << std::setw(25) << "Nombre"
                  << std::left << std::setw(15) << "Cargo"
                  << std::right << std::setw(12) << "Salario"
                  << std::left << std::setw(13) << "Fecha Contr."
                  << std::left << std::setw(10) << "Estado" << std::endl;
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;
        
        for (const auto& empleado : empleados) {
            std::cout << empleado.obtenerFilaTabla() << std::endl;
        }
        
        Utilidades::pausar();
    }
    
    void mostrarTablaEmpleados() {
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;
        std::cout << std::left << std::setw(5) << "ID"
                  << std::left << std::setw(25) << "Nombre"
                  << std::left << std::setw(15) << "Cargo"
                  << std::right << std::setw(12) << "Salario"
                  << std::left << std::setw(13) << "Fecha Contr."
                  << std::left << std::setw(10) << "Estado" << std::endl;
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;
        
        auto mostrarEmpleado = [](const Empleado& e) {
            if (e.isActivo()) {
                std::cout << e.obtenerFilaTabla() << std::endl;
            }
        };
        
        empleadoController.obtenerTodos().forEach(mostrarEmpleado);
    }
    
    void mostrarTablaEmpleados(Lista<Empleado>& empleados) {
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;
        std::cout << std::left << std::setw(5) << "ID"
                  << std::left << std::setw(25) << "Nombre"
                  << std::left << std::setw(15) << "Cargo"
                  << std::right << std::setw(12) << "Salario"
                  << std::left << std::setw(13) << "Fecha Contr."
                  << std::left << std::setw(10) << "Estado" << std::endl;
        std::cout << Utilidades::generarLinea('-', 85) << std::endl;
        
        auto mostrarEmpleado = [](const Empleado& e) {
            if (e.isActivo()) {
                std::cout << e.obtenerFilaTabla() << std::endl;
            }
        };
        
        empleados.forEach(mostrarEmpleado);
    }
};

#endif