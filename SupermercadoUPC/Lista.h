#ifndef LISTA_H
#define LISTA_H

#include "Nodo.h"
#include <functional>

using namespace std;

template <typename T>
class Lista {
private:
    Nodo<T>* cabeza;
    int tamanio;

public:
    Lista() : cabeza(nullptr), tamanio(0) {}
    ~Lista();

    void agregar(const T& elemento);
    bool eliminar(function<bool(const T&)> criterio);
    T* buscar(function<bool(const T&)> criterio);
    bool modificar(function<bool(const T&)> criterio, const T& nuevoElemento);

    int getTamanio() const;
    void mostrar(function<void(const T&)> mostrarElemento) const;

    bool estaVacia() const;
    void insertarAlInicio(const T& elemento);
    bool contiene(std::function<bool(const T&)> criterio) const;
    void limpiar();
    T* obtenerEnPosicion(int posicion);
    bool eliminarEnPosicion(int posicion);
    void invertir();
    Lista<T>* filtrar(std::function<bool(const T&)> criterio) const;
};

// Destructor
template <typename T>
Lista<T>::~Lista() {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        Nodo<T>* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
}

// Agrega al final
template <typename T>
void Lista<T>::agregar(const T& elemento) {
    Nodo<T>* nuevo = new Nodo<T>(elemento);
    if (!cabeza) {
        cabeza = nuevo;
    }
    else {
        Nodo<T>* actual = cabeza;
        while (actual->siguiente)
            actual = actual->siguiente;
        actual->siguiente = nuevo;
    }
    tamanio++;
}

// Elimina el primer nodo que cumple el criterio
template <typename T>
bool Lista<T>::eliminar(std::function<bool(const T&)> criterio) {
    Nodo<T>* actual = cabeza;
    Nodo<T>* anterior = nullptr;

    while (actual) {
        if (criterio(actual->dato)) {
            if (anterior)
                anterior->siguiente = actual->siguiente;
            else
                cabeza = actual->siguiente;
            delete actual;
            tamanio--;
            return true;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    return false;
}

// Busca el primer nodo que cumple el criterio
template <typename T>
T* Lista<T>::buscar(std::function<bool(const T&)> criterio) {
    Nodo<T>* actual = cabeza;
    while (actual) {
        if (criterio(actual->dato)) {
            return &(actual->dato);
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

// Modifica el primer nodo que cumple el criterio
template <typename T>
bool Lista<T>::modificar(function<bool(const T&)> criterio, const T& nuevoElemento) {
    Nodo<T>* actual = cabeza;
    while (actual) {
        if (criterio(actual->dato)) {
            actual->dato = nuevoElemento;
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

template <typename T>
int Lista<T>::getTamanio() const {
    return tamanio;
}

// Muestra los elementos según una función lambda pasada
template <typename T>
void Lista<T>::mostrar(function<void(const T&)> mostrarElemento) const {
    Nodo<T>* actual = cabeza;
    while (actual) {
        mostrarElemento(actual->dato);
        actual = actual->siguiente;
    }
}

// Verifica si la lista está vacía
template <typename T>
bool Lista<T>::estaVacia() const {
    return cabeza == nullptr;
}

// Inserta un elemento al inicio de la lista
template <typename T>
void Lista<T>::insertarAlInicio(const T& elemento) {
    Nodo<T>* nuevo = new Nodo<T>(elemento);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
    tamanio++;
}

// Verifica si la lista contiene un elemento que cumple el criterio
template <typename T>
bool Lista<T>::contiene(std::function<bool(const T&)> criterio) const {
    Nodo<T>* actual = cabeza;
    while (actual) {
        if (criterio(actual->dato)) return true;
        actual = actual->siguiente;
    }
    return false;
}

// Limpia la lista eliminando todos los nodos
template <typename T>
void Lista<T>::limpiar() {
    while (cabeza) {
        Nodo<T>* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
    tamanio = 0;
}

// Obtiene el elemento en la posición especificada
template <typename T>
T* Lista<T>::obtenerEnPosicion(int posicion) {
    if (posicion < 0 || posicion >= tamanio) return nullptr;
    Nodo<T>* actual = cabeza;
    for (int i = 0; i < posicion; ++i) {
        actual = actual->siguiente;
    }
    return &(actual->dato);
}

// Elimina el nodo en la posición especificada
template <typename T>
bool Lista<T>::eliminarEnPosicion(int posicion) {
    if (posicion < 0 || posicion >= tamanio) return false;

    Nodo<T>* actual = cabeza;
    Nodo<T>* anterior = nullptr;

    for (int i = 0; i < posicion; ++i) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (anterior)
        anterior->siguiente = actual->siguiente;
    else
        cabeza = actual->siguiente;

    delete actual;
    tamanio--;
    return true;
}

// Invierte la lista
template <typename T>
void Lista<T>::invertir() {
    Nodo<T>* prev = nullptr;
    Nodo<T>* actual = cabeza;
    Nodo<T>* siguiente = nullptr;

    while (actual) {
        siguiente = actual->siguiente;
        actual->siguiente = prev;
        prev = actual;
        actual = siguiente;
    }

    cabeza = prev;
}

// Filtra la lista según un criterio y devuelve una nueva lista
template <typename T>
Lista<T>* Lista<T>::filtrar(std::function<bool(const T&)> criterio) const {
    Lista<T>* nuevaLista = new Lista<T>();
    Nodo<T>* actual = cabeza;
    while (actual) {
        if (criterio(actual->dato)) {
            nuevaLista->agregar(actual->dato);
        }
        actual = actual->siguiente;
    }
    return nuevaLista;
}

#endif // LISTA_H
