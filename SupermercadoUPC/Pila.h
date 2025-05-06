#ifndef PILA_H
#define PILA_H

#include <iostream>
#include "Nodo.h"

template <typename T>
class Pila {
private:
    Nodo<T>* cima;

public:
    Pila() : cima(nullptr) {}
    ~Pila();

    void push(const T& valor);
    T pop();
    T peek() const;
    bool estaVacia() const;
    int tamano() const;
    void mostrar() const;
};

// Destructor
template <typename T>
Pila<T>::~Pila() {
    while (!estaVacia()) {
        pop();
    }
}

template <typename T>
void Pila<T>::push(const T& valor) {
    Nodo<T>* nuevo = new Nodo<T>(valor);
    nuevo->setSiguiente(cima);
    cima = nuevo;
}

template <typename T>
T Pila<T>::pop() {
    if (estaVacia()) throw std::runtime_error("Pila vacía");
    Nodo<T>* temp = cima;
    T dato = temp->getDato();
    cima = cima->getSiguiente();
    delete temp;
    return dato;
}

template <typename T>
T Pila<T>::peek() const {
    if (estaVacia()) throw std::runtime_error("Pila vacía");
    return cima->getDato();
}

template <typename T>
bool Pila<T>::estaVacia() const {
    return cima == nullptr;
}

template <typename T>
int Pila<T>::tamano() const {
    int contador = 0;
    Nodo<T>* actual = cima;
    while (actual != nullptr) {
        contador++;
        actual = actual->getSiguiente();
    }
    return contador;
}

template <typename T>
void Pila<T>::mostrar() const {
    Nodo<T>* actual = cima;
    while (actual != nullptr) {
        std::cout << actual->getDato() << " -> ";
        actual = actual->getSiguiente();
    }
    std::cout << "NULL" << std::endl;
}

#endif
