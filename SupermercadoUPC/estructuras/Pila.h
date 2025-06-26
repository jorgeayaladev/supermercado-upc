#ifndef PILA_H
#define PILA_H

#include "Nodo.h"
#include <stdexcept>
#include <functional>

template <typename T>
class Pila {
private:
    Nodo<T>* tope;
    int tamano;

public:
    // Constructor y destructor
    Pila() : tope(nullptr), tamano(0) {}
    
    ~Pila() {
        vaciar();
    }
    
    // Métodos básicos
    void apilar(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        
        if (estaVacia()) {
            tope = nuevo;
        } else {
            nuevo->setSiguiente(tope);
            tope = nuevo;
        }
        
        tamano++;
    }
    
    T desapilar() {
        if (estaVacia()) {
            throw std::runtime_error("La pila esta vacia");
        }
        
        Nodo<T>* temp = tope;
        T dato = temp->getDato();
        
        tope = tope->getSiguiente();
        delete temp;
        tamano--;
        
        return dato;
    }
    
    T& verTope() const {
        if (estaVacia()) {
            throw std::runtime_error("La pila esta vacia");
        }
        
        return tope->getDato();
    }
    
    bool estaVacia() const {
        return tope == nullptr;
    }
    
    int getTamano() const {
        return tamano;
    }
    
    void vaciar() {
        while (!estaVacia()) {
            desapilar();
        }
    }
    
    // Método para aplicar una función a cada elemento de la pila (no modifica la pila)
    void aplicar(std::function<void(const T&)> funcion) const {
        Nodo<T>* actual = tope;
        
        while (actual != nullptr) {
            funcion(actual->getDato());
            actual = actual->getSiguiente();
        }
    }
    
    // Método para filtrar elementos y devolver una nueva pila
    Pila<T> filtrar(std::function<bool(const T&)> predicado) const {
        Pila<T> resultado;
        Pila<T> auxiliar;
        
        // Copiar elementos a pila auxiliar
        Nodo<T>* actual = tope;
        while (actual != nullptr) {
            auxiliar.apilar(actual->getDato());
            actual = actual->getSiguiente();
        }
        
        // Filtrar y apilar en orden correcto
        while (!auxiliar.estaVacia()) {
            T elemento = auxiliar.desapilar();
            if (predicado(elemento)) {
                resultado.apilar(elemento);
            }
        }
        
        return resultado;
    }
};

#endif