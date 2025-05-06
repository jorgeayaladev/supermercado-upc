#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include "Nodo.h"

using namespace std;

template <typename T>
class Lista {
private:
    Nodo<T>* cabeza;

public:
    Lista() : cabeza(nullptr) {}
    ~Lista() { this->eliminarTodo(); }

	void agregarInicio(const T& valor); // Agregar al inicio
	void agregarFinal(const T& valor); // Agregar al final
	bool eliminar(const T& valor); // Eliminar un nodo
	Nodo<T>* buscar(const T& valor); // Buscar un nodo
	void eliminarTodo() const; // Eliminar todos los nodos
	void mostrar() const; // Mostrar la lista
	bool estaVacia() const; // Verificar si la lista está vacía
};

template <typename T>
void Lista<T>::agregarInicio(const T& valor) {
    Nodo<T>* nuevo = new Nodo<T>(valor);
    nuevo->setSiguiente(cabeza);
    cabeza = nuevo;
}

template <typename T>
void Lista<T>::agregarFinal(const T& valor) {
    Nodo<T>* nuevo = new Nodo<T>(valor);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        return;
    }
    Nodo<T>* actual = cabeza;
    while (actual->getSiguiente() != nullptr) {
        actual = actual->getSiguiente();
    }
    actual->setSiguiente(nuevo);
}

template <typename T>
bool Lista<T>::eliminar(const T& valor) {
    if (cabeza == nullptr) return false;

    if (cabeza->getDato() == valor) {
        Nodo<T>* temp = cabeza;
        cabeza = cabeza->getSiguiente();
        delete temp;
        return true;
    }

    Nodo<T>* actual = cabeza;
    while (actual->getSiguiente() != nullptr && actual->getSiguiente()->getDato() != valor) {
        actual = actual->getSiguiente();
    }

    if (actual->getSiguiente() == nullptr) return false;

    Nodo<T>* temp = actual->getSiguiente();
    actual->setSiguiente(temp->getSiguiente());
    delete temp;
    return true;
}

template <typename T>
void Lista<T>::eliminarTodo() const {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        Nodo<T>* temp = actual;
        actual = actual->getSiguiente();
        delete temp;
    }
}

template <typename T>
Nodo<T>* Lista<T>::buscar(const T& valor) {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        if (actual->getDato() == valor)
            return actual;
        actual = actual->getSiguiente();
    }
    return nullptr;
}

template <typename T>
void Lista<T>::mostrar() const {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        cout << actual->getDato() << endl;
        actual = actual->getSiguiente();
    }
}

template <typename T>
bool Lista<T>::estaVacia() const {
    return cabeza == nullptr;
}

#endif // LISTA_H
