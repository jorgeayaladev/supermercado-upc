#ifndef ARBOL_BINARIO_H
#define ARBOL_BINARIO_H

#include <functional>
#include <queue>
#include <vector>
#include <iostream>

template <typename T>
class NodoArbol {
private:
    T dato;
    NodoArbol<T>* izquierdo;
    NodoArbol<T>* derecho;

public:
    NodoArbol(const T& _dato) : dato(_dato), izquierdo(nullptr), derecho(nullptr) {}
    
    T& getDato() { return dato; }
    const T& getDato() const { return dato; }
    void setDato(const T& _dato) { dato = _dato; }
    
    NodoArbol<T>* getIzquierdo() const { return izquierdo; }
    void setIzquierdo(NodoArbol<T>* _izquierdo) { izquierdo = _izquierdo; }
    
    NodoArbol<T>* getDerecho() const { return derecho; }
    void setDerecho(NodoArbol<T>* _derecho) { derecho = _derecho; }
    
    bool esHoja() const {
        return izquierdo == nullptr && derecho == nullptr;
    }
};

template <typename T>
class ArbolBinario {
private:
    NodoArbol<T>* raiz = nullptr;
    int tamano;
    
    void insertarRecursivo(NodoArbol<T>* nodo, const T& dato) {
        if (nodo == nullptr) {
            nodo = new NodoArbol<T>(dato);
            tamano++;
        } else if (dato < nodo->getDato()) {
            insertarRecursivo(nodo->getIzquierdo(), dato);
        } else if (dato > nodo->getDato()) {
            insertarRecursivo(nodo->getDerecho(), dato);
        }
        // Si dato == nodo->getDato(), no insertamos (no duplicados)
    }
    
    NodoArbol<T>* buscarRecursivo(NodoArbol<T>* nodo, const T& dato) const {
        if (nodo == nullptr || nodo->getDato() == dato) {
            return nodo;
        }
        
        if (dato < nodo->getDato()) {
            return buscarRecursivo(nodo->getIzquierdo(), dato);
        } else {
            return buscarRecursivo(nodo->getDerecho(), dato);
        }
    }
    
    NodoArbol<T>* eliminarRecursivo(NodoArbol<T>* nodo, const T& dato) {
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
            
            if (nodo->getIzquierdo() == nullptr) {
                NodoArbol<T>* temp = nodo->getDerecho();
                delete nodo;
                return temp;
            } else if (nodo->getDerecho() == nullptr) {
                NodoArbol<T>* temp = nodo->getIzquierdo();
                delete nodo;
                return temp;
            }
            
            // Nodo con dos hijos: obtener el sucesor inorden
            NodoArbol<T>* temp = encontrarMinimo(nodo->getDerecho());
            nodo->setDato(temp->getDato());
            nodo->setDerecho(eliminarRecursivo(nodo->getDerecho(), temp->getDato()));
        }
        
        return nodo;
    }
    
    NodoArbol<T>* encontrarMinimo(NodoArbol<T>* nodo) const {
        while (nodo->getIzquierdo() != nullptr) {
            nodo = nodo->getIzquierdo();
        }
        return nodo;
    }
    
    NodoArbol<T>* encontrarMaximo(NodoArbol<T>* nodo) const {
        while (nodo->getDerecho() != nullptr) {
            nodo = nodo->getDerecho();
        }
        return nodo;
    }
    
    void inordenRecursivo(NodoArbol<T>* nodo, std::function<void(const T&)> funcion) const {
        if (nodo != nullptr) {
            inordenRecursivo(nodo->getIzquierdo(), funcion);
            funcion(nodo->getDato());
            inordenRecursivo(nodo->getDerecho(), funcion);
        }
    }
    
    void preordenRecursivo(NodoArbol<T>* nodo, std::function<void(const T&)> funcion) const {
        if (nodo != nullptr) {
            funcion(nodo->getDato());
            preordenRecursivo(nodo->getIzquierdo(), funcion);
            preordenRecursivo(nodo->getDerecho(), funcion);
        }
    }
    
    void postordenRecursivo(NodoArbol<T>* nodo, std::function<void(const T&)> funcion) const {
        if (nodo != nullptr) {
            postordenRecursivo(nodo->getIzquierdo(), funcion);
            postordenRecursivo(nodo->getDerecho(), funcion);
            funcion(nodo->getDato());
        }
    }
    
    void destruirArbol(NodoArbol<T>* nodo) {
        if (nodo != nullptr) {
            destruirArbol(nodo->getIzquierdo());
            destruirArbol(nodo->getDerecho());
            delete nodo;
        }
    }
    
    int alturaRecursiva(NodoArbol<T>* nodo) const {
        if (nodo == nullptr) {
            return -1;
        }
        
        int alturaIzq = alturaRecursiva(nodo->getIzquierdo());
        int alturaDer = alturaRecursiva(nodo->getDerecho());
        
        return 1 + std::max(alturaIzq, alturaDer);
    }

public:
    ArbolBinario() : raiz(nullptr), tamano(0) {}
    
    ~ArbolBinario() {
        destruirArbol(raiz);
    }
    
    void insertar(const T& dato) {
        insertarRecursivo(raiz, dato);
    }
    
    bool buscar(const T& dato) const {
        return buscarRecursivo(raiz, dato) != nullptr;
    }
    
    T* buscarReferencia(const T& dato) {
        NodoArbol<T>* nodo = buscarRecursivo(raiz, dato);
        return nodo ? &(nodo->getDato()) : nullptr;
    }
    
    bool eliminar(const T& dato) {
        int tamanoAnterior = tamano;
        raiz = eliminarRecursivo(raiz, dato);
        return tamano < tamanoAnterior;
    }
    
    bool estaVacio() const {
        return raiz == nullptr;
    }
    
    int getTamano() const {
        return tamano;
    }
    
    int getAltura() const {
        return alturaRecursiva(raiz);
    }
    
    T obtenerMinimo() const {
        if (raiz == nullptr) {
            throw std::runtime_error("Arbol vacio");
        }
        return encontrarMinimo(raiz)->getDato();
    }
    
    T obtenerMaximo() const {
        if (raiz == nullptr) {
            throw std::runtime_error("Arbol vacio");
        }
        return encontrarMaximo(raiz)->getDato();
    }
    
    void recorridoInorden(std::function<void(const T&)> funcion) const {
        inordenRecursivo(raiz, funcion);
    }
    
    void recorridoPreorden(std::function<void(const T&)> funcion) const {
        preordenRecursivo(raiz, funcion);
    }
    
    void recorridoPostorden(std::function<void(const T&)> funcion) const {
        postordenRecursivo(raiz, funcion);
    }
    
    void recorridoPorNiveles(std::function<void(const T&)> funcion) const {
        if (raiz == nullptr) return;
        
        std::queue<NodoArbol<T>*> cola;
        cola.push(raiz);
        
        while (!cola.empty()) {
            NodoArbol<T>* actual = cola.front();
            cola.pop();
            
            funcion(actual->getDato());
            
            if (actual->getIzquierdo() != nullptr) {
                cola.push(actual->getIzquierdo());
            }
            if (actual->getDerecho() != nullptr) {
                cola.push(actual->getDerecho());
            }
        }
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
    
    // Buscar elementos en un rango
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