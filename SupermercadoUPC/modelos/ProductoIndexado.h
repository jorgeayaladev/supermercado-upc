#ifndef PRODUCTO_INDEXADO_H
#define PRODUCTO_INDEXADO_H

#include "Producto.h"
#include <string>

// Clase wrapper para usar productos en estructuras de datos con índices
class ProductoIndexado {
private:
    Producto producto;
    std::string indice; // Puede ser precio, nombre, categoria, etc.

public:
    ProductoIndexado() : producto(), indice("") {}
    
    ProductoIndexado(const Producto& _producto, const std::string& _indice)
        : producto(_producto), indice(_indice) {}
    
    // Getters y setters
    Producto& getProducto() { return producto; }
    const Producto& getProducto() const { return producto; }
    void setProducto(const Producto& _producto) { producto = _producto; }
    
    std::string getIndice() const { return indice; }
    void setIndice(const std::string& _indice) { indice = _indice; }
    
    // Operadores de comparación basados en el índice
    bool operator<(const ProductoIndexado& otro) const {
        return indice < otro.indice;
    }
    
    bool operator>(const ProductoIndexado& otro) const {
        return indice > otro.indice;
    }
    
    bool operator==(const ProductoIndexado& otro) const {
        return indice == otro.indice;
    }
    
    bool operator!=(const ProductoIndexado& otro) const {
        return indice != otro.indice;
    }
    
    // Método para mostrar información
    void mostrar() const {
        std::cout << "Indice: " << indice << std::endl;
        producto.mostrar();
    }
};

#endif