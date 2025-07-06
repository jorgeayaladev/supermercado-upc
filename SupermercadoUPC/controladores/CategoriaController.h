#ifndef CATEGORIA_CONTROLLER_H
#define CATEGORIA_CONTROLLER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>
#include "../modelos/Categoria.h"
#include "../estructuras/Lista.h"
#include "../utilidades/Utilidades.h"
#include "../utilidades/Ordenamiento.h"

class CategoriaController {
private:
    Lista<Categoria> categorias;
    const std::string archivoCategorias = "datos/categorias.txt";

public:
    // Constructor
    CategoriaController() {
        cargarCategorias();
    }
    
    // Métodos CRUD
    
    // Crear una nueva categoría
    bool crear(const Categoria& categoria) {
        // Verificar si ya existe una categoría con el mismo ID o nombre
        auto buscarExistente = [&categoria](const Categoria& c) {
            return c.getId() == categoria.getId() || 
                   Utilidades::aMinusculas(c.getNombre()) == Utilidades::aMinusculas(categoria.getNombre());
        };
        
        if (categorias.buscar(buscarExistente) != nullptr) {
            return false; // Ya existe una categoría con ese ID o nombre
        }
        
        categorias.insertarFinal(categoria);
        guardarCategorias();
        return true;
    }
    
    // Obtener una categoría por ID
    Categoria* obtenerPorId(const std::string& id) {
        auto buscarPorId = [&id](const Categoria& c) {
            return c.getId() == id;
        };
        
        return categorias.buscar(buscarPorId);
    }
    
    // Obtener una categoría por nombre
    Categoria* obtenerPorNombre(const std::string& nombre) {
        auto buscarPorNombre = [&nombre](const Categoria& c) {
            return Utilidades::aMinusculas(c.getNombre()) == Utilidades::aMinusculas(nombre);
        };
        
        return categorias.buscar(buscarPorNombre);
    }
    
    // Actualizar una categoría existente
    bool actualizar(const Categoria& categoria) {
        bool encontrado = false;
        
        auto actualizarCategoria = [&categoria, &encontrado](Categoria& c) {
            if (c.getId() == categoria.getId()) {
                c = categoria;
                encontrado = true;
            }
        };
        
        categorias.forEach(actualizarCategoria);
        
        if (encontrado) {
            guardarCategorias();
        }
        
        return encontrado;
    }
    
    // Eliminar una categoría (marcándola como inactiva)
    bool eliminar(const std::string& id) {
        bool encontrado = false;
        
        auto eliminarCategoria = [&id, &encontrado](Categoria& c) {
            if (c.getId() == id) {
                c.setActiva(false);
                encontrado = true;
            }
        };
        
        categorias.forEach(eliminarCategoria);
        
        if (encontrado) {
            guardarCategorias();
        }
        
        return encontrado;
    }
    
    // Obtener todas las categorías
    Lista<Categoria>& obtenerTodas() { return categorias; }
	int obtenerCantidad() const { return categorias.getTamano(); }
    
    // Obtener categorías activas
    Lista<Categoria> obtenerActivas() {
        auto filtrarActivas = [](const Categoria& c) {
            return c.isActiva();
        };
        
        return categorias.filtrar(filtrarActivas);
    }
    
    // Ordenar categorías por nombre (A-Z)
    std::vector<Categoria> ordenarPorNombreAsc() {
        std::vector<Categoria> categoriasVector;
        
        auto agregarAVector = [&categoriasVector](const Categoria& c) {
            if (c.isActiva()) {
                categoriasVector.push_back(c);
            }
        };
        
        categorias.forEach(agregarAVector);
        
        Ordenamiento<Categoria>::mergeSort(categoriasVector);
        
        return categoriasVector;
    }
    
    // Cargar categorías desde archivo
    void cargarCategorias() {
        std::ifstream archivo(archivoCategorias);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo de categorías. Se creará uno nuevo al guardar." << std::endl;
            // Crear categorías de ejemplo si no existe el archivo
            generarCategoriasEjemplo();
            return;
        }
        
        std::string linea;
        while (std::getline(archivo, linea)) {
            if (!linea.empty()) {
                Categoria categoria = Categoria::desdeCSV(linea);
                categorias.insertarFinal(categoria);
            }
        }
        
        archivo.close();
    }
    
    // Guardar categorías en archivo
    void guardarCategorias() {        
        std::ofstream archivo(archivoCategorias);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para guardar las categorías." << std::endl;
            return;
        }
        
        auto guardarCategoria = [&archivo](const Categoria& c) {
            archivo << c.aCSV() << std::endl;
        };
        categorias.forEach(guardarCategoria);
        
        archivo.close();
    }
    
private:
    // Generar categorías de ejemplo
    void generarCategoriasEjemplo() {
        categorias.insertarFinal(Categoria("C001", "Abarrotes", "Productos básicos no perecederos"));
        categorias.insertarFinal(Categoria("C002", "Lacteos", "Productos lácteos y derivados"));
        categorias.insertarFinal(Categoria("C003", "Frutas", "Frutas frescas"));
        categorias.insertarFinal(Categoria("C004", "Verduras", "Verduras y hortalizas frescas"));
        categorias.insertarFinal(Categoria("C005", "Carnes", "Carnes frescas y congeladas"));
        categorias.insertarFinal(Categoria("C006", "Panaderia", "Productos de panadería y repostería"));
        categorias.insertarFinal(Categoria("C007", "Bebidas", "Refrescos, jugos y bebidas"));
        categorias.insertarFinal(Categoria("C008", "Limpieza", "Productos de limpieza para el hogar"));
        categorias.insertarFinal(Categoria("C009", "Higiene", "Productos de higiene personal"));
        categorias.insertarFinal(Categoria("C010", "Hogar", "Artículos para el hogar"));
        
        guardarCategorias();
    }
};

#endif