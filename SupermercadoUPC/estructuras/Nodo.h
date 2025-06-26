#ifndef NODO_H
#define NODO_H

#include <iostream>

template <typename T>
class Nodo {
private:
    T dato;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;

public:
    // Constructor
    Nodo(T _dato) : dato(_dato), siguiente(nullptr), anterior(nullptr) {}

    // Getters y setters
    T& getDato() { return dato; }
    void setDato(T _dato) { dato = _dato; }
    
    Nodo<T>* getSiguiente() const { return siguiente; }
    void setSiguiente(Nodo<T>* _siguiente) { siguiente = _siguiente; }
    
    Nodo<T>* getAnterior() const { return anterior; }
    void setAnterior(Nodo<T>* _anterior) { anterior = _anterior; }
    
    // Sobrecarga del operador de comparación para uso en algoritmos de ordenamiento
    bool operator<(const Nodo<T>& otro) const {
        return dato < otro.dato;
    }
    
    bool operator>(const Nodo<T>& otro) const {
        return dato > otro.dato;
    }
    
    bool operator==(const Nodo<T>& otro) const {
        return dato == otro.dato;
    }
};

#endif