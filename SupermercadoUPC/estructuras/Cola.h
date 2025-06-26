#ifndef COLA_H
#define COLA_H

#include "Nodo.h"
#include <stdexcept>
#include <functional>

template <typename T>
class Cola {
private:
    Nodo<T>* frente;
    Nodo<T>* final;
    int tamano;

public:
    // Constructor y destructor
    Cola() : frente(nullptr), final(nullptr), tamano(0) {}
    
    ~Cola() {
        vaciar();
    }
    
    // Métodos básicos
    void encolar(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        
        if (estaVacia()) {
            frente = final = nuevo;
        } else {
            final->setSiguiente(nuevo);
            final = nuevo;
        }
        
        tamano++;
    }
    
    T desencolar() {
        if (estaVacia()) {
            throw std::runtime_error("La cola esta vacia");
        }
        
        Nodo<T>* temp = frente;
        T dato = temp->getDato();
        
        if (frente == final) {
            frente = final = nullptr;
        } else {
            frente = frente->getSiguiente();
        }
        
        delete temp;
        tamano--;
        return dato;
    }
    
    T& verFrente() {
        if (estaVacia()) {
            throw std::runtime_error("La cola esta vacia");
        }
        
        return frente->getDato();
    }
    
    bool estaVacia() const {
        return frente == nullptr;
    }
    
    int getTamano() const {
        return tamano;
    }
    
    void vaciar() {
        while (!estaVacia()) {
            desencolar();
        }
    }
    
    // Método para aplicar una función a cada elemento de la cola
    void aplicar(std::function<void(const T&)> funcion) const {
        Nodo<T>* actual = frente;
        
        while (actual != nullptr) {
            funcion(actual->getDato());
            actual = actual->getSiguiente();
        }
    }
    
    // Método para filtrar elementos y devolver una nueva cola
    Cola<T> filtrar(std::function<bool(const T&)> predicado) const {
        Cola<T> resultado;
        Cola<T> auxiliar;
        
        // Copiar elementos a cola auxiliar
        Nodo<T>* actual = frente;
        while (actual != nullptr) {
            auxiliar.encolar(actual->getDato());
            actual = actual->getSiguiente();
        }
        
        // Filtrar y encolar en orden correcto
        while (!auxiliar.estaVacia()) {
            T elemento = auxiliar.desencolar();
            if (predicado(elemento)) {
                resultado.encolar(elemento);
            }
        }
        
        return resultado;
    }
};

#endif