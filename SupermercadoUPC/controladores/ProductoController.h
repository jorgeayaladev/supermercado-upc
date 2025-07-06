#ifndef PRODUCTO_CONTROLLER_H
#define PRODUCTO_CONTROLLER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>
#include "../modelos/Producto.h"
#include "../estructuras/Lista.h"
#include "../utilidades/Utilidades.h"
#include "../utilidades/Ordenamiento.h"

class ProductoController {
private:
    Lista<Producto> productos;
    const std::string archivoProductos = "datos/productos.txt";

public:
    // Constructor
    ProductoController() {
        cargarProductos();
    }
    
    // Métodos CRUD
    
    // Crear un nuevo producto
    bool crear(const Producto& producto) {
        // Verificar si ya existe un producto con el mismo ID o código de barras
        auto buscarExistente = [&producto](const Producto& p) {
            return p.getId() == producto.getId() || p.getCodigoBarras() == producto.getCodigoBarras();
        };
        
        if (productos.buscar(buscarExistente) != nullptr) {
            return false; // Ya existe un producto con ese ID o código de barras
        }
        
        productos.insertarFinal(producto);
        guardarProductos();
        return true;
    }
    
    // Obtener un producto por ID
    Producto* obtenerPorId(const std::string& id) {
        auto buscarPorId = [&id](const Producto& p) {
            return p.getId() == id;
        };
        
        return productos.buscar(buscarPorId);
    }
    
    // Obtener un producto por código de barras
    Producto* obtenerPorCodigoBarras(const std::string& codigo) {
        auto buscarPorCodigo = [&codigo](const Producto& p) {
            return p.getCodigoBarras() == codigo;
        };
        
        return productos.buscar(buscarPorCodigo);
    }
    
    // Actualizar un producto existente
    bool actualizar(const Producto& producto) {
        bool encontrado = false;
        
        auto actualizarProducto = [&producto, &encontrado](Producto& p) {
            if (p.getId() == producto.getId()) {
                p = producto;
                encontrado = true;
            }
        };
        
        productos.forEach(actualizarProducto);
        
        if (encontrado) {
            guardarProductos();
        }
        
        return encontrado;
    }
    
    // Eliminar un producto (marcándolo como no disponible)
    bool eliminar(const std::string& id) {
        bool encontrado = false;
        
        auto eliminarProducto = [&id, &encontrado](Producto& p) {
            if (p.getId() == id) {
                p.setDisponible(false);
                encontrado = true;
            }
        };
        
        productos.forEach(eliminarProducto);
        
        if (encontrado) {
            guardarProductos();
        }
        
        return encontrado;
    }
    
    // Obtener todos los productos
    Lista<Producto>& obtenerTodos() { return productos; }
    int obtenerCantidad() const { return productos.getTamano(); }
    
    // Obtener productos por categoría
    Lista<Producto> obtenerPorCategoria(const std::string& categoria) {
        auto filtrarPorCategoria = [&categoria](const Producto& p) {
            return p.getCategoria() == categoria && p.isDisponible();
        };
        
        return productos.filtrar(filtrarPorCategoria);
    }
    
    // Buscar productos por nombre
    Lista<Producto> buscarPorNombre(const std::string& nombre) {
        auto filtrarPorNombre = [&nombre](const Producto& p) {
            std::string nombreLower = Utilidades::aMinusculas(p.getNombre());
            std::string busquedaLower = Utilidades::aMinusculas(nombre);
            return nombreLower.find(busquedaLower) != std::string::npos && p.isDisponible();
        };
        
        return productos.filtrar(filtrarPorNombre);
    }
    
    // Obtener productos con stock bajo
    Lista<Producto> obtenerStockBajo(int umbral) {
        auto filtrarPorStock = [umbral](const Producto& p) {
            return p.getStock() < umbral && p.isDisponible();
        };
        
        return productos.filtrar(filtrarPorStock);
    }
    
    // Ordenar productos por nombre (A-Z)
    std::vector<Producto> ordenarPorNombreAsc() {
        std::vector<Producto> productosVector;
        
        auto agregarAVector = [&productosVector](const Producto& p) {
            if (p.isDisponible()) {
                productosVector.push_back(p);
            }
        };
        
        productos.forEach(agregarAVector);
        
        Ordenamiento<Producto>::quickSort(productosVector);
        
        return productosVector;
    }
    
    // Ordenar productos por nombre (Z-A)
    std::vector<Producto> ordenarPorNombreDesc() {
        std::vector<Producto> productosVector;
        
        auto agregarAVector = [&productosVector](const Producto& p) {
            if (p.isDisponible()) {
                productosVector.push_back(p);
            }
        };
        
        productos.forEach(agregarAVector);
        
        Ordenamiento<Producto>::ordenarPersonalizado(productosVector, 
            [](const Producto& a, const Producto& b) { return a.getNombre() > b.getNombre(); });
        
        return productosVector;
    }
    
    // Ordenar productos por precio (menor a mayor)
    std::vector<Producto> ordenarPorPrecioAsc() {
        std::vector<Producto> productosVector;
        
        auto agregarAVector = [&productosVector](const Producto& p) {
            if (p.isDisponible()) {
                productosVector.push_back(p);
            }
        };
        
        productos.forEach(agregarAVector);
        
        Ordenamiento<Producto>::ordenarPersonalizado(productosVector, 
            [](const Producto& a, const Producto& b) { return a.getPrecio() < b.getPrecio(); });
        
        return productosVector;
    }
    
    // Ordenar productos por precio (mayor a menor)
    std::vector<Producto> ordenarPorPrecioDesc() {
        std::vector<Producto> productosVector;
        
        auto agregarAVector = [&productosVector](const Producto& p) {
            if (p.isDisponible()) {
                productosVector.push_back(p);
            }
        };
        
        productos.forEach(agregarAVector);
        
        Ordenamiento<Producto>::ordenarPersonalizado(productosVector, 
            [](const Producto& a, const Producto& b) { return a.getPrecio() > b.getPrecio(); });
        
        return productosVector;
    }
    
    // Ordenar productos por stock (menor a mayor)
    std::vector<Producto> ordenarPorStockAsc() {
        std::vector<Producto> productosVector;
        
        auto agregarAVector = [&productosVector](const Producto& p) {
            if (p.isDisponible()) {
                productosVector.push_back(p);
            }
        };
        
        productos.forEach(agregarAVector);
        
        Ordenamiento<Producto>::ordenarPersonalizado(productosVector, 
            [](const Producto& a, const Producto& b) { return a.getStock() < b.getStock(); });
        
        return productosVector;
    }
    
    // Cargar productos desde archivo
    void cargarProductos() {
        std::ifstream archivo(archivoProductos);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo de productos. Se creará uno nuevo al guardar." << std::endl;
            // Crear productos de ejemplo si no existe el archivo
            generarProductosEjemplo();
            return;
        }
        
        std::string linea;
        while (std::getline(archivo, linea)) {
            if (!linea.empty()) {
                Producto producto = Producto::desdeCSV(linea);
                productos.insertarFinal(producto);
            }
        }
        
        archivo.close();
    }
    
    // Guardar productos en archivo
    void guardarProductos() {
        std::ofstream archivo(archivoProductos);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para guardar los productos." << std::endl;
            return;
        }
        
        auto guardarProducto = [&archivo](const Producto& p) {
            archivo << p.aCSV() << std::endl;
        };
        productos.forEach(guardarProducto);
        
        archivo.close();
    }

    std::vector<Producto> merge(const std::vector<Producto>& izquierda, const std::vector<Producto>& derecha) {
        std::vector<Producto> resultado;
        size_t i = 0, j = 0;

        while (i < izquierda.size() && j < derecha.size()) {
            if (izquierda[i].getPrecio() <= derecha[j].getPrecio()) {
                resultado.push_back(izquierda[i++]);
            }
            else {
                resultado.push_back(derecha[j++]);
            }
        }

        while (i < izquierda.size()) {
            resultado.push_back(izquierda[i++]);
        }
        while (j < derecha.size()) {
            resultado.push_back(derecha[j++]);
        }

        return resultado;
    }
    std::vector<Producto> mergeSortProductos(const std::vector<Producto>& productos) {
        if (productos.size() <= 1) {
            return productos;
        }

        size_t mitad = productos.size() / 2;
        std::vector<Producto> izquierda(productos.begin(), productos.begin() + mitad);
        std::vector<Producto> derecha(productos.begin() + mitad, productos.end());

        return merge(mergeSortProductos(izquierda), mergeSortProductos(derecha));
    }
    
private:
    // Generar productos de ejemplo
    void generarProductosEjemplo() {
        productos.insertarFinal(Producto("P001", "Leche Entera 1L", "Leche entera de vaca en envase de 1 litro", 1.50, 50, "Lacteos", "7501055321001"));
        productos.insertarFinal(Producto("P002", "Pan Integral", "Pan de trigo integral, 500g", 2.20, 30, "Panaderia", "7501055321002"));
        productos.insertarFinal(Producto("P003", "Manzanas Rojas", "Manzanas rojas frescas por kg", 3.50, 40, "Frutas", "7501055321003"));
        productos.insertarFinal(Producto("P004", "Arroz Blanco 1kg", "Arroz blanco grano largo", 1.80, 60, "Abarrotes", "7501055321004"));
        productos.insertarFinal(Producto("P005", "Jabón de Bano", "Jabón de bano con aloe vera", 1.20, 45, "Higiene", "7501055321005"));
        productos.insertarFinal(Producto("P006", "Refresco Cola 2L", "Refresco sabor cola", 2.00, 35, "Bebidas", "7501055321006"));
        productos.insertarFinal(Producto("P007", "Papel Higiénico", "Paquete de 4 rollos", 4.50, 25, "Hogar", "7501055321007"));
        productos.insertarFinal(Producto("P008", "Detergente Líquido", "Detergente líquido 1L", 3.80, 20, "Limpieza", "7501055321008"));
        productos.insertarFinal(Producto("P009", "Jamon de Pavo", "Jamón de pavo bajo en grasa 250g", 3.20, 15, "Embutidos", "7501055321009"));
        productos.insertarFinal(Producto("P010", "Cereal Integral", "Cereal de trigo integral 500g", 4.30, 28, "Desayuno", "7501055321010"));
        
        guardarProductos();
    }
};

#endif