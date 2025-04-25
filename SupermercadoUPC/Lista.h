#pragma once

#include <iostream>
#include "Nodo.h"

using namespace std;

// Clase Lista enlazada simple
template <typename T>
class Lista {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    int tamano;

public:
    // Constructor
    Lista() : cabeza(nullptr), cola(nullptr), tamano(0) {}

    // Destructor
    ~Lista() { vaciar(); }

    // Métodos básicos
    bool estaVacia() const { return cabeza == nullptr; }
    int getTamano() const { return tamano; }

    // Insertar elementos
    void insertarAlInicio(T valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);

        if (estaVacia()) {
            cabeza = cola = nuevoNodo;
        }
        else {
            nuevoNodo->setSiguiente(cabeza);
            cabeza = nuevoNodo;
        }
        tamano++;
    }

    void insertarAlFinal(T valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);

        if (estaVacia()) {
            cabeza = cola = nuevoNodo;
        }
        else {
            cola->setSiguiente(nuevoNodo);
            cola = nuevoNodo;
        }
        tamano++;
    }

    void insertarEnPosicion(T valor, int posicion) {
        if (posicion < 0 || posicion > tamano) {
            throw out_of_range("Posición fuera de rango");
        }

        if (posicion == 0) {
            insertarAlInicio(valor);
        }
        else if (posicion == tamano) {
            insertarAlFinal(valor);
        }
        else {
            Nodo<T>* nuevoNodo = new Nodo<T>(valor);
            Nodo<T>* actual = cabeza;

            for (int i = 0; i < posicion - 1; i++) {
                actual = actual->getSiguiente();
            }

            nuevoNodo->setSiguiente(actual->getSiguiente());
            actual->setSiguiente(nuevoNodo);
            tamano++;
        }
    }

    // Eliminar elementos
    void eliminarAlInicio() {
        if (estaVacia()) {
            throw runtime_error("La lista está vacía");
        }

        Nodo<T>* temp = cabeza;
        cabeza = cabeza->getSiguiente();
        delete temp;
        tamano--;

        if (cabeza == nullptr) {
            cola = nullptr;
        }
    }

    void eliminarAlFinal() {
        if (estaVacia()) {
            throw runtime_error("La lista está vacía");
        }

        if (tamano == 1) {
            eliminarAlInicio();
            return;
        }

        Nodo<T>* actual = cabeza;
        while (actual->getSiguiente() != cola) {
            actual = actual->getSiguiente();
        }

        delete cola;
        cola = actual;
        cola->setSiguiente(nullptr);
        tamano--;
    }

    void eliminarEnPosicion(int posicion) {
        if (posicion < 0 || posicion >= tamano) {
            throw out_of_range("Posición fuera de rango");
        }

        if (posicion == 0) {
            eliminarAlInicio();
        }
        else if (posicion == tamano - 1) {
            eliminarAlFinal();
        }
        else {
            Nodo<T>* actual = cabeza;
            Nodo<T>* anterior = nullptr;

            for (int i = 0; i < posicion; i++) {
                anterior = actual;
                actual = actual->getSiguiente();
            }

            anterior->setSiguiente(actual->getSiguiente());
            delete actual;
            tamano--;
        }
    }

    // Buscar elementos
    int buscar(T valor) const {
        Nodo<T>* actual = cabeza;
        int posicion = 0;

        while (actual != nullptr) {
            if (actual->getDato() == valor) {
                return posicion;
            }
            actual = actual->getSiguiente();
            posicion++;
        }

        return -1; // No encontrado
    }

    T obtenerElemento(int posicion) const {
        if (posicion < 0 || posicion >= tamano) {
            throw out_of_range("Posición fuera de rango");
        }

        Nodo<T>* actual = cabeza;
        for (int i = 0; i < posicion; i++) {
            actual = actual->getSiguiente();
        }

        return actual->getDato();
    }

    // Modificar elementos
    void modificarElemento(T valor, int posicion) {
        if (posicion < 0 || posicion >= tamano) {
            throw out_of_range("Posición fuera de rango");
        }

        Nodo<T>* actual = cabeza;
        for (int i = 0; i < posicion; i++) {
            actual = actual->getSiguiente();
        }

        actual->setDato(valor);
    }

    // Vaciar la lista
    void vaciar() {
        while (!estaVacia()) {
            eliminarAlInicio();
        }
    }

    // Mostrar la lista
    void mostrar() const {
        Nodo<T>* actual = cabeza;

        cout << "[";
        while (actual != nullptr) {
            cout << actual->getDato();
            if (actual->getSiguiente() != nullptr) {
                cout << ", ";
            }
            actual = actual->getSiguiente();
        }
        cout << "]" << endl;
    }

    // Sobrecarga del operador [] para acceso por índice
    T operator[](int indice) const {
        return obtenerElemento(indice);
    }
};