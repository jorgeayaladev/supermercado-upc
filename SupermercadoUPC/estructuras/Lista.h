#ifndef LISTA_H
#define LISTA_H

#include "Nodo.h"
#include <functional>
#include <stdexcept>

template <typename T>
class Lista {
private:
    Nodo<T>* primero;
    Nodo<T>* ultimo;
    int tamano;

public:
    // Constructor y destructor
    Lista() : primero(nullptr), ultimo(nullptr), tamano(0) {}
    
    ~Lista() {
        vaciar();
    }

    // Métodos básicos
    void insertarInicio(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        
        if (estaVacia()) {
            primero = ultimo = nuevo;
        } else {
            nuevo->setSiguiente(primero);
            primero->setAnterior(nuevo);
            primero = nuevo;
        }
        
        tamano++;
    }
    
    void insertarFinal(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        
        if (estaVacia()) {
            primero = ultimo = nuevo;
        } else {
            ultimo->setSiguiente(nuevo);
            nuevo->setAnterior(ultimo);
            ultimo = nuevo;
        }
        
        tamano++;
    }
    
    T eliminarInicio() {
        if (estaVacia()) {
            throw std::runtime_error("La lista esta vacia");
        }
        
        Nodo<T>* temp = primero;
        T dato = temp->getDato();
        
        if (primero == ultimo) {
            primero = ultimo = nullptr;
        } else {
            primero = primero->getSiguiente();
            primero->setAnterior(nullptr);
        }
        
        delete temp;
        tamano--;
        return dato;
    }
    
    T eliminarFinal() {
        if (estaVacia()) {
            throw std::runtime_error("La lista esta vacia");
        }
        
        Nodo<T>* temp = ultimo;
        T dato = temp->getDato();
        
        if (primero == ultimo) {
            primero = ultimo = nullptr;
        } else {
            ultimo = ultimo->getAnterior();
            ultimo->setSiguiente(nullptr);
        }
        
        delete temp;
        tamano--;
        return dato;
    }

    void vaciar() {
        while (!estaVacia()) {
            eliminarInicio();
        }
    }
    
    bool estaVacia() const {
        return primero == nullptr;
    }
    
    int getTamano() const {
        return tamano;
    }
    
    // Método para iterar sobre la lista con una función lambda
    void forEach(std::function<void(T&)> funcion) {
        Nodo<T>* actual = primero;
        while (actual != nullptr) {
            funcion(actual->getDato());
            actual = actual->getSiguiente();
        }
    }
    
    // Método para filtrar elementos y devolver una nueva lista
    Lista<T> filtrar(std::function<bool(const T&)> predicado) {
        Lista<T> resultado;
        Nodo<T>* actual = primero;
        
        while (actual != nullptr) {
            if (predicado(actual->getDato())) {
                resultado.insertarFinal(actual->getDato());
            }
            actual = actual->getSiguiente();
        }
        
        return resultado;
    }
    
    // Método para buscar un elemento
    T* buscar(std::function<bool(const T&)> predicado) {
        Nodo<T>* actual = primero;
        
        while (actual != nullptr) {
            if (predicado(actual->getDato())) {
                return &(actual->getDato());
            }
            actual = actual->getSiguiente();
        }
        
        return nullptr;
    }
    
    // Método para obtener un elemento por índice
    T& obtener(int indice) {
        if (indice < 0 || indice >= tamano) {
            throw std::out_of_range("Indice fuera de rango");
        }
        
        Nodo<T>* actual = primero;
        for (int i = 0; i < indice; i++) {
            actual = actual->getSiguiente();
        }
        
        return actual->getDato();
    }
    
    // Método para modificar un elemento por índice
    void modificar(int indice, T dato) {
        if (indice < 0 || indice >= tamano) {
            throw std::out_of_range("Indice fuera de rango");
        }
        
        Nodo<T>* actual = primero;
        for (int i = 0; i < indice; i++) {
            actual = actual->getSiguiente();
        }
        
        actual->setDato(dato);
    }
};

#endif