#ifndef PROVEEDOR_CONTROLLER_H
#define PROVEEDOR_CONTROLLER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>
#include "../modelos/Proveedor.h"
#include "../estructuras/Lista.h"
#include "../utilidades/Utilidades.h"
#include "../utilidades/Ordenamiento.h"

class ProveedorController {
private:
    Lista<Proveedor> proveedores;
    const std::string archivoProveedores = "datos/proveedores.txt";

public:
    // Constructor
    ProveedorController() {
        cargarProveedores();
    }
    
    // Métodos CRUD
    
    // Crear un nuevo proveedor
    bool crear(const Proveedor& proveedor) {
        // Verificar si ya existe un proveedor con el mismo ID o email
        auto buscarExistente = [&proveedor](const Proveedor& p) {
            return p.getId() == proveedor.getId() || 
                   Utilidades::aMinusculas(p.getEmail()) == Utilidades::aMinusculas(proveedor.getEmail());
        };
        
        if (proveedores.buscar(buscarExistente) != nullptr) {
            return false; // Ya existe un proveedor con ese ID o email
        }
        
        proveedores.insertarFinal(proveedor);
        guardarProveedores();
        return true;
    }
    
    // Obtener un proveedor por ID
    Proveedor* obtenerPorId(const std::string& id) {
        auto buscarPorId = [&id](const Proveedor& p) {
            return p.getId() == id;
        };
        
        return proveedores.buscar(buscarPorId);
    }
    
    // Obtener un proveedor por nombre
    Proveedor* obtenerPorNombre(const std::string& nombre) {
        auto buscarPorNombre = [&nombre](const Proveedor& p) {
            return Utilidades::aMinusculas(p.getNombre()) == Utilidades::aMinusculas(nombre);
        };
        
        return proveedores.buscar(buscarPorNombre);
    }
    
    // Actualizar un proveedor existente
    bool actualizar(const Proveedor& proveedor) {
        bool encontrado = false;
        
        auto actualizarProveedor = [&proveedor, &encontrado](Proveedor& p) {
            if (p.getId() == proveedor.getId()) {
                p = proveedor;
                encontrado = true;
            }
        };
        
        proveedores.forEach(actualizarProveedor);
        
        if (encontrado) {
            guardarProveedores();
        }
        
        return encontrado;
    }
    
    // Eliminar un proveedor (marcándolo como inactivo)
    bool eliminar(const std::string& id) {
        bool encontrado = false;
        
        auto eliminarProveedor = [&id, &encontrado](Proveedor& p) {
            if (p.getId() == id) {
                p.setActivo(false);
                encontrado = true;
            }
        };
        
        proveedores.forEach(eliminarProveedor);
        
        if (encontrado) {
            guardarProveedores();
        }
        
        return encontrado;
    }
    
    // Obtener todos los proveedores
    Lista<Proveedor>& obtenerTodos() { return proveedores; }
	int obtenerCantidad() const { return proveedores.getTamano(); }
    
    // Obtener proveedores activos
    Lista<Proveedor> obtenerActivos() {
        auto filtrarActivos = [](const Proveedor& p) {
            return p.isActivo();
        };
        
        return proveedores.filtrar(filtrarActivos);
    }
    
    // Obtener proveedores por categoría
    Lista<Proveedor> obtenerPorCategoria(const std::string& categoria) {
        auto filtrarPorCategoria = [&categoria](const Proveedor& p) {
            auto categorias = p.getCategorias();
            return std::find(categorias.begin(), categorias.end(), categoria) != categorias.end() && p.isActivo();
        };
        
        return proveedores.filtrar(filtrarPorCategoria);
    }
    
    // Buscar proveedores por nombre
    Lista<Proveedor> buscarPorNombre(const std::string& busqueda) {
        auto filtrarPorNombre = [&busqueda](const Proveedor& p) {
            std::string nombreLower = Utilidades::aMinusculas(p.getNombre());
            std::string busquedaLower = Utilidades::aMinusculas(busqueda);
            return nombreLower.find(busquedaLower) != std::string::npos && p.isActivo();
        };
        
        return proveedores.filtrar(filtrarPorNombre);
    }
    
    // Ordenar proveedores por nombre (A-Z)
    std::vector<Proveedor> ordenarPorNombreAsc() {
        std::vector<Proveedor> proveedoresVector;
        
        auto agregarAVector = [&proveedoresVector](const Proveedor& p) {
            if (p.isActivo()) {
                proveedoresVector.push_back(p);
            }
        };
        
        proveedores.forEach(agregarAVector);
        
        Ordenamiento<Proveedor>::quickSort(proveedoresVector);
        
        return proveedoresVector;
    }
    
    // Cargar proveedores desde archivo
    void cargarProveedores() {
        std::ifstream archivo(archivoProveedores);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo de proveedores. Se creará uno nuevo al guardar." << std::endl;
            // Crear proveedores de ejemplo si no existe el archivo
            generarProveedoresEjemplo();
            return;
        }
        
        std::string linea;
        while (std::getline(archivo, linea)) {
            if (!linea.empty()) {
                Proveedor proveedor = Proveedor::desdeCSV(linea);
                proveedores.insertarFinal(proveedor);
            }
        }
        
        archivo.close();
    }
    
    // Guardar proveedores en archivo
    void guardarProveedores() {
        std::ofstream archivo(archivoProveedores);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para guardar los proveedores." << std::endl;
            return;
        }
        
        auto guardarProveedor = [&archivo](const Proveedor& p) {
            archivo << p.aCSV() << std::endl;
        };
        proveedores.forEach(guardarProveedor);
        
        archivo.close();
    }

    Proveedor* buscarProveedor(Nodo<Proveedor>* nodo, const std::string& id) {
        if (nodo == nullptr) {
            return nullptr; // Caso base: no se encontró el proveedor
        }
        if (nodo->getDato().getId() == id) {
            return &(nodo->getDato()); // Caso base: se encontró el proveedor
        }
        return buscarProveedor(nodo->getSiguiente(), id); // Llamada recursiva
    }
    
private:
    // Generar proveedores de ejemplo
    void generarProveedoresEjemplo() {
        std::vector<std::string> categorias1 = {"Lacteos", "Abarrotes"};
        std::vector<std::string> categorias2 = {"Frutas", "Verduras"};
        std::vector<std::string> categorias3 = {"Limpieza", "Higiene"};
        std::vector<std::string> categorias4 = {"Carnes"};
        std::vector<std::string> categorias5 = {"Panaderia", "Abarrotes"};
        
        proveedores.insertarFinal(Proveedor("PR001", "Lacteos del Valle", "Juan Ramirez", "info@lacteosdelvalle.com", "904337284", "Calle Industrial 123", categorias1));
        proveedores.insertarFinal(Proveedor("PR002", "Frutas Frescas SA", "Maria Ortiz", "ventas@frutasfrescas.com", "978432748", "Av. Campo 456", categorias2));
        proveedores.insertarFinal(Proveedor("PR003", "Limpieza Total", "Carlos Mendez", "contacto@limpiezatotal.com", "992039233", "Blvd. Central 789", categorias3));
        proveedores.insertarFinal(Proveedor("PR004", "Carnes Premium", "Laura Vega", "info@carnespremium.com", "909192221", "Calle Ganaderos 321", categorias4));
        proveedores.insertarFinal(Proveedor("PR005", "Panaderia San Juan", "Pedro Rosales", "ventas@panaderiasjuan.com", "903484439", "Av. Trigo 567", categorias5));
        
        guardarProveedores();
    }
};

#endif