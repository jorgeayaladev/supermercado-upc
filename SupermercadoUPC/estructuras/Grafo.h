#ifndef GRAFO_H
#define GRAFO_H

#include "Vertice.h"
#include "Arco.h"
#include "TablaHash.h"
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits>
#include <functional>
#include <iostream>

template <typename T>
class Grafo {
private:
    std::vector<Vertice<T>*> vertices;
    std::vector<Arco<T>*> arcos;
    TablaHash<std::string, Vertice<T>*> indiceVertices;
    bool dirigido;
    
    void reiniciarEstadoVertices() {
        for (Vertice<T>* vertice : vertices) {
            vertice->reiniciarEstado();
        }
    }

public:
    Grafo(bool _dirigido = true) : dirigido(_dirigido) {}
    
    ~Grafo() {
        limpiar();
    }
    
    // Manejo de vértices
    Vertice<T>* agregarVertice(const T& dato, const std::string& id) {
        if (indiceVertices.contiene(id)) {
            return nullptr; // Ya existe un vértice con ese ID
        }
        
        Vertice<T>* nuevoVertice = new Vertice<T>(dato, id);
        vertices.push_back(nuevoVertice);
        indiceVertices.insertar(id, nuevoVertice);
        
        return nuevoVertice;
    }
    
    bool eliminarVertice(const std::string& id) {
        Vertice<T>** verticePtr = indiceVertices.buscar(id);
        if (!verticePtr) {
            return false;
        }
        
        Vertice<T>* vertice = *verticePtr;
        
        // Eliminar todos los arcos conectados a este vértice
        std::vector<Arco<T>*> arcosAEliminar;
        
        for (Arco<T>* arco : arcos) {
            if (arco->incidenteA(vertice)) {
                arcosAEliminar.push_back(arco);
            }
        }
        
        for (Arco<T>* arco : arcosAEliminar) {
            eliminarArco(arco);
        }
        
        // Eliminar vértice de la lista
        vertices.erase(std::remove(vertices.begin(), vertices.end(), vertice), vertices.end());
        indiceVertices.eliminar(id);
        
        delete vertice;
        return true;
    }
    
    Vertice<T>* obtenerVertice(const std::string& id) {
        Vertice<T>** verticePtr = indiceVertices.buscar(id);
        return verticePtr ? *verticePtr : nullptr;
    }
    
    // Manejo de arcos
    Arco<T>* agregarArco(const std::string& idOrigen, const std::string& idDestino, 
                         double peso = 1.0, const std::string& etiqueta = "") {
        Vertice<T>* origen = obtenerVertice(idOrigen);
        Vertice<T>* destino = obtenerVertice(idDestino);
        
        if (!origen || !destino) {
            return nullptr;
        }
        
        // Verificar si ya existe un arco entre estos vértices
        for (Arco<T>* arco : arcos) {
            if (arco->conecta(origen, destino)) {
                return nullptr; // Ya existe
            }
        }
        
        Arco<T>* nuevoArco = new Arco<T>(origen, destino, peso, etiqueta, dirigido);
        arcos.push_back(nuevoArco);
        
        origen->agregarArcoSaliente(nuevoArco);
        destino->agregarArcoEntrante(nuevoArco);
        
        // Si no es dirigido, agregar el arco en ambas direcciones
        if (!dirigido) {
            origen->agregarArcoEntrante(nuevoArco);
            destino->agregarArcoSaliente(nuevoArco);
        }
        
        return nuevoArco;
    }
    
    bool eliminarArco(Arco<T>* arco) {
        auto it = std::find(arcos.begin(), arcos.end(), arco);
        if (it == arcos.end()) {
            return false;
        }
        
        // Eliminar referencias del arco en los vértices
        arco->getOrigen()->eliminarArcoSaliente(arco);
        arco->getDestino()->eliminarArcoEntrante(arco);
        
        if (!dirigido) {
            arco->getOrigen()->eliminarArcoEntrante(arco);
            arco->getDestino()->eliminarArcoSaliente(arco);
        }
        
        arcos.erase(it);
        delete arco;
        return true;
    }
    
    bool eliminarArco(const std::string& idOrigen, const std::string& idDestino) {
        Vertice<T>* origen = obtenerVertice(idOrigen);
        Vertice<T>* destino = obtenerVertice(idDestino);
        
        if (!origen || !destino) {
            return false;
        }
        
        for (Arco<T>* arco : arcos) {
            if (arco->conecta(origen, destino)) {
                return eliminarArco(arco);
            }
        }
        
        return false;
    }
    
    // Algoritmos de recorrido
    void recorridoDFS(const std::string& idInicio, std::function<void(Vertice<T>*)> funcion) {
        Vertice<T>* inicio = obtenerVertice(idInicio);
        if (!inicio) return;
        
        reiniciarEstadoVertices();
        dfsRecursivo(inicio, funcion);
    }
    
    void recorridoBFS(const std::string& idInicio, std::function<void(Vertice<T>*)> funcion) {
        Vertice<T>* inicio = obtenerVertice(idInicio);
        if (!inicio) return;
        
        reiniciarEstadoVertices();
        
        std::queue<Vertice<T>*> cola;
        inicio->setVisitado(true);
        cola.push(inicio);
        
        while (!cola.empty()) {
            Vertice<T>* actual = cola.front();
            cola.pop();
            
            funcion(actual);
            
            for (Vertice<T>* vecino : actual->getVecinos()) {
                if (!vecino->isVisitado()) {
                    vecino->setVisitado(true);
                    cola.push(vecino);
                }
            }
        }
    }
    
    // Algoritmo de Dijkstra para caminos más cortos
    std::vector<Vertice<T>*> caminoMasCorto(const std::string& idOrigen, const std::string& idDestino) {
        Vertice<T>* origen = obtenerVertice(idOrigen);
        Vertice<T>* destino = obtenerVertice(idDestino);
        
        if (!origen || !destino) {
            return std::vector<Vertice<T>*>();
        }
        
        reiniciarEstadoVertices();
        
        // Inicializar distancias
        origen->setDistancia(0);
        
        // Cola de prioridad (min-heap)
        auto comparador = [](Vertice<T>* a, Vertice<T>* b) {
            return a->getDistancia() > b->getDistancia();
        };
        
        std::priority_queue<Vertice<T>*, std::vector<Vertice<T>*>, decltype(comparador)> cola(comparador);
        
        for (Vertice<T>* vertice : vertices) {
            cola.push(vertice);
        }
        
        while (!cola.empty()) {
            Vertice<T>* actual = cola.top();
            cola.pop();
            
            if (actual->isVisitado()) continue;
            actual->setVisitado(true);
            
            if (actual == destino) break;
            
            for (Arco<T>* arco : actual->getArcosSalientes()) {
                Vertice<T>* vecino = arco->getDestino();
                double nuevaDistancia = actual->getDistancia() + arco->getPeso();
                
                if (nuevaDistancia < vecino->getDistancia()) {
                    vecino->setDistancia(nuevaDistancia);
                    vecino->setPredecesor(actual);
                }
            }
        }
        
        // Reconstruir camino
        std::vector<Vertice<T>*> camino;
        Vertice<T>* actual = destino;
        
        while (actual != nullptr) {
            camino.push_back(actual);
            actual = actual->getPredecesor();
        }
        
        std::reverse(camino.begin(), camino.end());
        
        // Verificar si se encontró un camino válido
        if (camino.empty() || camino[0] != origen) {
            return std::vector<Vertice<T>*>();
        }
        
        return camino;
    }
    
    // Detección de ciclos (para grafos dirigidos)
    bool tieneCiclos() {
        if (!dirigido) {
            return tieneCiclosNoDigirido();
        }
        
        reiniciarEstadoVertices();
        
        // Estados: 0 = no visitado, 1 = en proceso, 2 = completado
        std::vector<int> estado(vertices.size(), 0);
        TablaHash<std::string, int> indiceEstado;
        
        for (int i = 0; i < vertices.size(); i++) {
            indiceEstado.insertar(vertices[i]->getId(), i);
        }
        
        for (Vertice<T>* vertice : vertices) {
            int* indicePtr = indiceEstado.buscar(vertice->getId());
            int indice = indicePtr ? *indicePtr : -1;
            
            if (indice >= 0 && estado[indice] == 0) {
                if (dfsDeteccionCiclos(vertice, estado, indiceEstado)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
    // Ordenamiento topológico
    std::vector<Vertice<T>*> ordenamientoTopologico() {
        if (!dirigido || tieneCiclos()) {
            return std::vector<Vertice<T>*>(); // No es posible
        }
        
        std::vector<Vertice<T>*> resultado;
        std::stack<Vertice<T>*> pila;
        reiniciarEstadoVertices();
        
        for (Vertice<T>* vertice : vertices) {
            if (!vertice->isVisitado()) {
                dfsTopologico(vertice, pila);
            }
        }
        
        while (!pila.empty()) {
            resultado.push_back(pila.top());
            pila.pop();
        }
        
        return resultado;
    }
    
    // Información del grafo
    int getNumVertices() const {
        return (int) vertices.size();
    }
    
    int getNumArcos() const {
        return (int) arcos.size();
    }
    
    bool esDirigido() const {
        return dirigido;
    }
    
    bool estaVacio() const {
        return vertices.empty();
    }
    
    std::vector<Vertice<T>*> getVertices() const {
        return vertices;
    }
    
    std::vector<Arco<T>*> getArcos() const {
        return arcos;
    }
    
    // Componentes conexas (para grafos no dirigidos)
    std::vector<std::vector<Vertice<T>*>> obtenerComponentesConexas() {
        if (dirigido) {
            return std::vector<std::vector<Vertice<T>*>>(); // No aplicable
        }
        
        std::vector<std::vector<Vertice<T>*>> componentes;
        reiniciarEstadoVertices();
        
        for (Vertice<T>* vertice : vertices) {
            if (!vertice->isVisitado()) {
                std::vector<Vertice<T>*> componente;
                
                auto agregarAComponente = [&componente](Vertice<T>* v) {
                    componente.push_back(v);
                };
                
                dfsRecursivo(vertice, agregarAComponente);
                componentes.push_back(componente);
            }
        }
        
        return componentes;
    }
    
    void limpiar() {
        for (Arco<T>* arco : arcos) {
            delete arco;
        }
        arcos.clear();
        
        for (Vertice<T>* vertice : vertices) {
            delete vertice;
        }
        vertices.clear();
        
        indiceVertices.limpiar();
    }
    
    void mostrarGrafo() {
        std::cout << "Grafo " << (dirigido ? "dirigido" : "no dirigido") << std::endl;
        std::cout << "Vertices: " << getNumVertices() << ", Arcos: " << getNumArcos() << std::endl;
        
        std::cout << "\nVertices:" << std::endl;
        for (Vertice<T>* vertice : vertices) {
            std::cout << "  " << vertice->getId() << " (grado: " << vertice->getGrado() << ")" << std::endl;
        }
        
        std::cout << "\nArcos:" << std::endl;
        for (Arco<T>* arco : arcos) {
            std::cout << "  " << arco->toString() << std::endl;
        }
    }

private:
    void dfsRecursivo(Vertice<T>* vertice, std::function<void(Vertice<T>*)> funcion) {
        vertice->setVisitado(true);
        funcion(vertice);
        
        for (Vertice<T>* vecino : vertice->getVecinos()) {
            if (!vecino->isVisitado()) {
                dfsRecursivo(vecino, funcion);
            }
        }
    }
    
    bool dfsDeteccionCiclos(Vertice<T>* vertice, std::vector<int>& estado, TablaHash<std::string, int>& indiceEstado) {
        int* indicePtr = indiceEstado.buscar(vertice->getId());
        int indice = indicePtr ? *indicePtr : -1;
        
        if (indice < 0) return false;
        
        estado[indice] = 1; // En proceso
        
        for (Vertice<T>* vecino : vertice->getVecinos()) {
            int* indiceVecinoPtr = indiceEstado.buscar(vecino->getId());
            int indiceVecino = indiceVecinoPtr ? *indiceVecinoPtr : -1;
            
            if (indiceVecino >= 0) {
                if (estado[indiceVecino] == 1) {
                    return true; // Ciclo detectado
                }
                if (estado[indiceVecino] == 0 && dfsDeteccionCiclos(vecino, estado, indiceEstado)) {
                    return true;
                }
            }
        }
        
        estado[indice] = 2; // Completado
        return false;
    }
    
    bool tieneCiclosNoDigirido() {
        reiniciarEstadoVertices();
        
        for (Vertice<T>* vertice : vertices) {
            if (!vertice->isVisitado()) {
                if (dfsDeteccionCiclosNoDigirido(vertice, nullptr)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
    bool dfsDeteccionCiclosNoDigirido(Vertice<T>* vertice, Vertice<T>* padre) {
        vertice->setVisitado(true);
        
        for (Vertice<T>* vecino : vertice->getVecinos()) {
            if (!vecino->isVisitado()) {
                if (dfsDeteccionCiclosNoDigirido(vecino, vertice)) {
                    return true;
                }
            } else if (vecino != padre) {
                return true; // Ciclo detectado
            }
        }
        
        return false;
    }
    
    void dfsTopologico(Vertice<T>* vertice, std::stack<Vertice<T>*>& pila) {
        vertice->setVisitado(true);
        
        for (Vertice<T>* vecino : vertice->getVecinos()) {
            if (!vecino->isVisitado()) {
                dfsTopologico(vecino, pila);
            }
        }
        
        pila.push(vertice);
    }
};

#endif