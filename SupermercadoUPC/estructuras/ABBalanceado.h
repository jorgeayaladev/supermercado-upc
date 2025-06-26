#ifndef AB_BALANCEADO_H
#define AB_BALANCEADO_H

#include <functional>
#include <algorithm>
#include <vector>
#include <iostream>

template <typename T>
class NodoAVL {
private:
    T dato;
    NodoAVL<T>* izquierdo;
    NodoAVL<T>* derecho;
    int altura;

public:
    NodoAVL(const T& _dato) : dato(_dato), izquierdo(nullptr), derecho(nullptr), altura(1) {}
    
    T& getDato() { return dato; }
    const T& getDato() const { return dato; }
    void setDato(const T& _dato) { dato = _dato; }
    
    NodoAVL<T>* getIzquierdo() const { return izquierdo; }
    void setIzquierdo(NodoAVL<T>* _izquierdo) { izquierdo = _izquierdo; }
    
    NodoAVL<T>* getDerecho() const { return derecho; }
    void setDerecho(NodoAVL<T>* _derecho) { derecho = _derecho; }
    
    int getAltura() const { return altura; }
    void setAltura(int _altura) { altura = _altura; }
    
    bool esHoja() const {
        return izquierdo == nullptr && derecho == nullptr;
    }
};

template <typename T>
class ABBalanceado {
private:
    NodoAVL<T>* raiz;
    int tamano;
    
    int obtenerAltura(NodoAVL<T>* nodo) {
        return nodo ? nodo->getAltura() : 0;
    }
    
    int obtenerBalance(NodoAVL<T>* nodo) {
        return nodo ? obtenerAltura(nodo->getIzquierdo()) - obtenerAltura(nodo->getDerecho()) : 0;
    }
    
    void actualizarAltura(NodoAVL<T>* nodo) {
        if (nodo) {
            nodo->setAltura(1 + std::max(obtenerAltura(nodo->getIzquierdo()), 
                                        obtenerAltura(nodo->getDerecho())));
        }
    }
    
    NodoAVL<T>* rotarDerecha(NodoAVL<T>* y) {
        NodoAVL<T>* x = y->getIzquierdo();
        NodoAVL<T>* T2 = x->getDerecho();
        
        // Realizar rotación
        x->setDerecho(y);
        y->setIzquierdo(T2);
        
        // Actualizar alturas
        actualizarAltura(y);
        actualizarAltura(x);
        
        return x;
    }
    
    NodoAVL<T>* rotarIzquierda(NodoAVL<T>* x) {
        NodoAVL<T>* y = x->getDerecho();
        NodoAVL<T>* T2 = y->getIzquierdo();
        
        // Realizar rotación
        y->setIzquierdo(x);
        x->setDerecho(T2);
        
        // Actualizar alturas
        actualizarAltura(x);
        actualizarAltura(y);
        
        return y;
    }
    
    NodoAVL<T>* insertarRecursivo(NodoAVL<T>* nodo, const T& dato) {
        // 1. Inserción normal de BST
        if (nodo == nullptr) {
            tamano++;
            return new NodoAVL<T>(dato);
        }
        
        if (dato < nodo->getDato()) {
            nodo->setIzquierdo(insertarRecursivo(nodo->getIzquierdo(), dato));
        } else if (dato > nodo->getDato()) {
            nodo->setDerecho(insertarRecursivo(nodo->getDerecho(), dato));
        } else {
            // Datos iguales no se permiten
            return nodo;
        }
        
        // 2. Actualizar altura del nodo ancestro
        actualizarAltura(nodo);
        
        // 3. Obtener el factor de balance
        int balance = obtenerBalance(nodo);
        
        // 4. Si el nodo está desbalanceado, hay 4 casos
        
        // Caso Izquierda Izquierda
        if (balance > 1 && dato < nodo->getIzquierdo()->getDato()) {
            return rotarDerecha(nodo);
        }
        
        // Caso Derecha Derecha
        if (balance < -1 && dato > nodo->getDerecho()->getDato()) {
            return rotarIzquierda(nodo);
        }
        
        // Caso Izquierda Derecha
        if (balance > 1 && dato > nodo->getIzquierdo()->getDato()) {
            nodo->setIzquierdo(rotarIzquierda(nodo->getIzquierdo()));
            return rotarDerecha(nodo);
        }
        
        // Caso Derecha Izquierda
        if (balance < -1 && dato < nodo->getDerecho()->getDato()) {
            nodo->setDerecho(rotarDerecha(nodo->getDerecho()));
            return rotarIzquierda(nodo);
        }
        
        return nodo;
    }
    
    NodoAVL<T>* encontrarMinimo(NodoAVL<T>* nodo) {
        while (nodo->getIzquierdo() != nullptr) {
            nodo = nodo->getIzquierdo();
        }
        return nodo;
    }
    
    NodoAVL<T>* eliminarRecursivo(NodoAVL<T>* nodo, const T& dato) {
        // 1. Eliminación normal de BST
        if (nodo == nullptr) {
            return nodo;
        }
        
        if (dato < nodo->getDato()) {
            nodo->setIzquierdo(eliminarRecursivo(nodo->getIzquierdo(), dato));
        } else if (dato > nodo->getDato()) {
            nodo->setDerecho(eliminarRecursivo(nodo->getDerecho(), dato));
        } else {
            // Nodo a eliminar encontrado
            tamano--;
            
            if (nodo->getIzquierdo() == nullptr || nodo->getDerecho() == nullptr) {
                NodoAVL<T>* temp = nodo->getIzquierdo() ? nodo->getIzquierdo() : nodo->getDerecho();
                
                if (temp == nullptr) {
                    temp = nodo;
                    nodo = nullptr;
                } else {
                    *nodo = *temp;
                }
                delete temp;
            } else {
                NodoAVL<T>* temp = encontrarMinimo(nodo->getDerecho());
                nodo->setDato(temp->getDato());
                nodo->setDerecho(eliminarRecursivo(nodo->getDerecho(), temp->getDato()));
            }
        }
        
        if (nodo == nullptr) {
            return nodo;
        }
        
        // 2. Actualizar altura
        actualizarAltura(nodo);
        
        // 3. Obtener factor de balance
        int balance = obtenerBalance(nodo);
        
        // 4. Si está desbalanceado, hay 4 casos
        
        // Caso Izquierda Izquierda
        if (balance > 1 && obtenerBalance(nodo->getIzquierdo()) >= 0) {
            return rotarDerecha(nodo);
        }
        
        // Caso Izquierda Derecha
        if (balance > 1 && obtenerBalance(nodo->getIzquierdo()) < 0) {
            nodo->setIzquierdo(rotarIzquierda(nodo->getIzquierdo()));
            return rotarDerecha(nodo);
        }
        
        // Caso Derecha Derecha
        if (balance < -1 && obtenerBalance(nodo->getDerecho()) <= 0) {
            return rotarIzquierda(nodo);
        }
        
        // Caso Derecha Izquierda
        if (balance < -1 && obtenerBalance(nodo->getDerecho()) > 0) {
            nodo->setDerecho(rotarDerecha(nodo->getDerecho()));
            return rotarIzquierda(nodo);
        }
        
        return nodo;
    }
    
    NodoAVL<T>* buscarRecursivo(NodoAVL<T>* nodo, const T& dato) const {
        if (nodo == nullptr || nodo->getDato() == dato) {
            return nodo;
        }
        
        if (dato < nodo->getDato()) {
            return buscarRecursivo(nodo->getIzquierdo(), dato);
        } else {
            return buscarRecursivo(nodo->getDerecho(), dato);
        }
    }
    
    void inordenRecursivo(NodoAVL<T>* nodo, std::function<void(const T&)> funcion) const {
        if (nodo != nullptr) {
            inordenRecursivo(nodo->getIzquierdo(), funcion);
            funcion(nodo->getDato());
            inordenRecursivo(nodo->getDerecho(), funcion);
        }
    }
    
    void destruirArbol(NodoAVL<T>* nodo) {
        if (nodo != nullptr) {
            destruirArbol(nodo->getIzquierdo());
            destruirArbol(nodo->getDerecho());
            delete nodo;
        }
    }

public:
    ABBalanceado() : raiz(nullptr), tamano(0) {}
    
    ~ABBalanceado() {
        destruirArbol(raiz);
    }
    
    void insertar(const T& dato) {
        raiz = insertarRecursivo(raiz, dato);
    }
    
    bool eliminar(const T& dato) {
        int tamanoAnterior = tamano;
        raiz = eliminarRecursivo(raiz, dato);
        return tamano < tamanoAnterior;
    }
    
    bool buscar(const T& dato) const {
        return buscarRecursivo(raiz, dato) != nullptr;
    }
    
    T* buscarReferencia(const T& dato) {
        NodoAVL<T>* nodo = buscarRecursivo(raiz, dato);
        return nodo ? &(nodo->getDato()) : nullptr;
    }
    
    bool estaVacio() const {
        return raiz == nullptr;
    }
    
    int getTamano() const {
        return tamano;
    }
    
    int getAltura() const {
        return obtenerAltura(raiz);
    }
    
    bool estaBalanceado() const {
        return abs(obtenerBalance(raiz)) <= 1;
    }
    
    void recorridoInorden(std::function<void(const T&)> funcion) const {
        inordenRecursivo(raiz, funcion);
    }
    
    std::vector<T> obtenerElementosOrdenados() const {
        std::vector<T> elementos;
        
        auto agregarElemento = [&elementos](const T& dato) {
            elementos.push_back(dato);
        };
        
        recorridoInorden(agregarElemento);
        return elementos;
    }
    
    void limpiar() {
        destruirArbol(raiz);
        raiz = nullptr;
        tamano = 0;
    }
    
    std::vector<T> buscarEnRango(const T& minimo, const T& maximo) const {
        std::vector<T> resultado;
        
        auto verificarRango = [&resultado, &minimo, &maximo](const T& dato) {
            if (dato >= minimo && dato <= maximo) {
                resultado.push_back(dato);
            }
        };
        
        recorridoInorden(verificarRango);
        return resultado;
    }
};

#endif