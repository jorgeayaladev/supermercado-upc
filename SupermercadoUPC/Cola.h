#ifndef COLA_H
#define COLA_H

#include <iostream>
#include "Nodo.h"

template <typename T>
class Cola {
private:
    Nodo<T>* frente;
    Nodo<T>* final;

public:
    Cola() : frente(nullptr), final(nullptr) {}
    ~Cola();

    void encolar(const T& valor);
    T desencolar();
    T frenteCola() const;
    bool estaVacia() const;
    int tamano() const;
    void mostrar() const;
};

// Destructor
template <typename T>
Cola<T>::~Cola() {
    while (!estaVacia()) {
        desencolar();
    }
}

template <typename T>
void Cola<T>::encolar(const T& valor) {
    Nodo<T>* nuevo = new Nodo<T>(valor);
    if (estaVacia()) {
        frente = final = nuevo;
    }
    else {
        final->setSiguiente(nuevo);
        final = nuevo;
    }
}

template <typename T>
T Cola<T>::desencolar() {
    if (estaVacia()) throw std::runtime_error("Cola vacía");
    Nodo<T>* temp = frente;
    T dato = temp->getDato();
    frente = frente->getSiguiente();
    if (frente == nullptr) final = nullptr;
    delete temp;
    return dato;
}

template <typename T>
T Cola<T>::frenteCola() const {
    if (estaVacia()) throw std::runtime_error("Cola vacía");
    return frente->getDato();
}

template <typename T>
bool Cola<T>::estaVacia() const {
    return frente == nullptr;
}

template <typename T>
int Cola<T>::tamano() const {
    int contador = 0;
    Nodo<T>* actual = frente;
    while (actual != nullptr) {
        contador++;
        actual = actual->getSiguiente();
    }
    return contador;
}

template <typename T>
void Cola<T>::mostrar() const {
    Nodo<T>* actual = frente;
    while (actual != nullptr) {
        std::cout << actual->getDato() << " -> ";
        actual = actual->getSiguiente();
    }
    std::cout << "NULL" << std::endl;
}

#endif
