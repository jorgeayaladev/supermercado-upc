#ifndef CLIENTE_CONTROLLER_H
#define CLIENTE_CONTROLLER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>
#include "../modelos/Cliente.h"
#include "../estructuras/Lista.h"
#include "../utilidades/Utilidades.h"
#include "../utilidades/Ordenamiento.h"

class ClienteController {
private:
    Lista<Cliente> clientes;
    const std::string archivoClientes = "datos/clientes.txt";

public:
    // Constructor
    ClienteController() {
        cargarClientes();
    }
    
    // Métodos CRUD
    
    // Crear un nuevo cliente
    bool crear(const Cliente& cliente) {
        // Verificar si ya existe un cliente con el mismo ID o email
        auto buscarExistente = [&cliente](const Cliente& c) {
            return c.getId() == cliente.getId() || 
                   Utilidades::aMinusculas(c.getEmail()) == Utilidades::aMinusculas(cliente.getEmail());
        };
        
        if (clientes.buscar(buscarExistente) != nullptr) {
            return false; // Ya existe un cliente con ese ID o email
        }
        
        clientes.insertarFinal(cliente);
        guardarClientes();
        return true;
    }
    
    // Obtener un cliente por ID
    Cliente* obtenerPorId(const std::string& id) {
        auto buscarPorId = [&id](const Cliente& c) {
            return c.getId() == id;
        };
        
        return clientes.buscar(buscarPorId);
    }
    
    // Obtener un cliente por email
    Cliente* obtenerPorEmail(const std::string& email) {
        auto buscarPorEmail = [&email](const Cliente& c) {
            return Utilidades::aMinusculas(c.getEmail()) == Utilidades::aMinusculas(email);
        };
        
        return clientes.buscar(buscarPorEmail);
    }
    
    // Actualizar un cliente existente
    bool actualizar(const Cliente& cliente) {
        bool encontrado = false;
        
        auto actualizarCliente = [&cliente, &encontrado](Cliente& c) {
            if (c.getId() == cliente.getId()) {
                c = cliente;
                encontrado = true;
            }
        };
        
        clientes.forEach(actualizarCliente);
        
        if (encontrado) {
            guardarClientes();
        }
        
        return encontrado;
    }
    
    // Eliminar un cliente (marcándolo como inactivo)
    bool eliminar(const std::string& id) {
        bool encontrado = false;
        
        auto eliminarCliente = [&id, &encontrado](Cliente& c) {
            if (c.getId() == id) {
                c.setActivo(false);
                encontrado = true;
            }
        };
        
        clientes.forEach(eliminarCliente);
        
        if (encontrado) {
            guardarClientes();
        }
        
        return encontrado;
    }
    
    // Obtener todos los clientes
    Lista<Cliente>& obtenerTodos() {
        return clientes;
    }
    
    // Obtener clientes activos
    Lista<Cliente> obtenerActivos() {
        auto filtrarActivos = [](const Cliente& c) {
            return c.isActivo();
        };
        
        return clientes.filtrar(filtrarActivos);
    }
    
    // Buscar clientes por nombre o apellido
    Lista<Cliente> buscarPorNombre(const std::string& busqueda) {
        auto filtrarPorNombre = [&busqueda](const Cliente& c) {
            std::string nombreCompleto = Utilidades::aMinusculas(c.getNombre() + " " + c.getApellido());
            std::string busquedaLower = Utilidades::aMinusculas(busqueda);
            return nombreCompleto.find(busquedaLower) != std::string::npos && c.isActivo();
        };
        
        return clientes.filtrar(filtrarPorNombre);
    }
    
    // Obtener clientes frecuentes (con más compras)
    std::vector<Cliente> obtenerClientesFrecuentes(int limite) {
        std::vector<Cliente> clientesVector;
        
        auto agregarAVector = [&clientesVector](const Cliente& c) {
            if (c.isActivo()) {
                clientesVector.push_back(c);
            }
        };
        
        clientes.forEach(agregarAVector);
        
        // Ordenar por total de compras (descendente)
        Ordenamiento<Cliente>::ordenarPersonalizado(clientesVector, 
            [](const Cliente& a, const Cliente& b) { 
                return a.getTotalCompras() > b.getTotalCompras(); 
            });
        
        // Limitar la cantidad de resultados
        if (clientesVector.size() > limite) {
            clientesVector.resize(limite);
        }
        
        return clientesVector;
    }
    
    // Ordenar clientes por apellido (A-Z)
    std::vector<Cliente> ordenarPorApellidoAsc() {
        std::vector<Cliente> clientesVector;
        
        auto agregarAVector = [&clientesVector](const Cliente& c) {
            if (c.isActivo()) {
                clientesVector.push_back(c);
            }
        };
        
        clientes.forEach(agregarAVector);
        
        Ordenamiento<Cliente>::heapSort(clientesVector);
        
        return clientesVector;
    }
    
    // Cargar clientes desde archivo
    void cargarClientes() {
        std::ifstream archivo(archivoClientes);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo de clientes. Se creará uno nuevo al guardar." << std::endl;
            // Crear clientes de ejemplo si no existe el archivo
            // generarClientesEjemplo();
            return;
        }
        
        std::string linea;
        while (std::getline(archivo, linea)) {
            if (!linea.empty()) {
                Cliente cliente = Cliente::desdeCSV(linea);
                clientes.insertarFinal(cliente);
            }
        }
        
        archivo.close();
    }
    
    // Guardar clientes en archivo
    void guardarClientes() {
        // Crear el directorio si no existe
        system("mkdir -p datos");
        
        std::ofstream archivo(archivoClientes);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para guardar los clientes." << std::endl;
            return;
        }
        
        auto guardarCliente = [&archivo](const Cliente& c) {
            archivo << c.aCSV() << std::endl;
        };
        
        clientes.forEach(guardarCliente);
        
        archivo.close();
    }

    double calcularTotalCompras(Nodo<Cliente>* nodo) {
        if (nodo == nullptr) {
            return 0.0; // Caso base: no hay más clientes
        }

        double total = nodo->getDato().getTotalCompras();
        double calculo = calcularTotalCompras(nodo->getSiguiente());

        return total + calculo; // Llamada recursiva
    }
    
private:
    // Generar clientes de ejemplo
    /*
    void generarClientesEjemplo() {
        clientes.insertarFinal(Cliente("CL001", "Juan", "Perez", "juanperez@gmail.com", "904892343", "Calle Principal 123", 580.50, 5));
        clientes.insertarFinal(Cliente("CL002", "Maria", "Garcia", "mariagarcia@gmail.com", "940234233", "Av. Central 456", 1200.75, 12));
        clientes.insertarFinal(Cliente("CL003", "Carlos", "Rodriguez", "carlosrodriguez@gmail.com", "978654333", "Plaza Mayor 789", 320.25, 3));
        clientes.insertarFinal(Cliente("CL004", "Ana", "Martinez", "anamartinez@gmail.com", "903923222", "Calle Secundaria 234", 950.00, 9));
        clientes.insertarFinal(Cliente("CL005", "Pedro", "Lopez", "pedrolopez@gmail.com", "901293123", "Av. Principal 567", 150.50, 1));
        
        guardarClientes();
    }
    */
};

#endif