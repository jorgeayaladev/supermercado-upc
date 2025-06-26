#ifndef VERTICE_H
#define VERTICE_H

#include <string>
#include <vector>
#include <functional>

template <typename T>
class Arco; // Forward declaration

template <typename T>
class Vertice {
private:
    T dato;
    std::string id;
    std::vector<Arco<T>*> arcosEntrantes;
    std::vector<Arco<T>*> arcosSalientes;
    bool visitado;
    double distancia; // Para algoritmos de caminos más cortos
    Vertice<T>* predecesor; // Para reconstruir caminos

public:
    Vertice(const T& _dato, const std::string& _id) 
        : dato(_dato), id(_id), visitado(false), distancia(std::numeric_limits<double>::infinity()), predecesor(nullptr) {}
    
    // Getters y setters
    T& getDato() { return dato; }
    const T& getDato() const { return dato; }
    void setDato(const T& _dato) { dato = _dato; }
    
    std::string getId() const { return id; }
    void setId(const std::string& _id) { id = _id; }
    
    bool isVisitado() const { return visitado; }
    void setVisitado(bool _visitado) { visitado = _visitado; }
    
    double getDistancia() const { return distancia; }
    void setDistancia(double _distancia) { distancia = _distancia; }
    
    Vertice<T>* getPredecesor() const { return predecesor; }
    void setPredecesor(Vertice<T>* _predecesor) { predecesor = _predecesor; }
    
    // Manejo de arcos
    void agregarArcoEntrante(Arco<T>* arco) {
        arcosEntrantes.push_back(arco);
    }
    
    void agregarArcoSaliente(Arco<T>* arco) {
        arcosSalientes.push_back(arco);
    }
    
    void eliminarArcoEntrante(Arco<T>* arco) {
        arcosEntrantes.erase(
            std::remove(arcosEntrantes.begin(), arcosEntrantes.end(), arco),
            arcosEntrantes.end()
        );
    }
    
    void eliminarArcoSaliente(Arco<T>* arco) {
        arcosSalientes.erase(
            std::remove(arcosSalientes.begin(), arcosSalientes.end(), arco),
            arcosSalientes.end()
        );
    }
    
    const std::vector<Arco<T>*>& getArcosEntrantes() const {
        return arcosEntrantes;
    }
    
    const std::vector<Arco<T>*>& getArcosSalientes() const {
        return arcosSalientes;
    }
    
    // Métodos de utilidad
    int getGradoEntrante() const {
        return arcosEntrantes.size();
    }
    
    int getGradoSaliente() const {
        return arcosSalientes.size();
    }
    
    int getGrado() const {
        return getGradoEntrante() + getGradoSaliente();
    }
    
    std::vector<Vertice<T>*> getVecinos() const {
        std::vector<Vertice<T>*> vecinos;
        
        for (Arco<T>* arco : arcosSalientes) {
            vecinos.push_back(arco->getDestino());
        }
        
        return vecinos;
    }
    
    bool esAdyacenteA(Vertice<T>* otroVertice) const {
        for (Arco<T>* arco : arcosSalientes) {
            if (arco->getDestino() == otroVertice) {
                return true;
            }
        }
        return false;
    }
    
    Arco<T>* obtenerArcoHacia(Vertice<T>* destino) const {
        for (Arco<T>* arco : arcosSalientes) {
            if (arco->getDestino() == destino) {
                return arco;
            }
        }
        return nullptr;
    }
    
    void aplicarFuncionAVecinos(std::function<void(Vertice<T>*)> funcion) {
        for (Arco<T>* arco : arcosSalientes) {
            funcion(arco->getDestino());
        }
    }
    
    void reiniciarEstado() {
        visitado = false;
        distancia = std::numeric_limits<double>::infinity();
        predecesor = nullptr;
    }
    
    // Sobrecarga de operadores
    bool operator==(const Vertice<T>& otro) const {
        return id == otro.id;
    }
    
    bool operator!=(const Vertice<T>& otro) const {
        return !(*this == otro);
    }
    
    bool operator<(const Vertice<T>& otro) const {
        return distancia < otro.distancia;
    }
    
    bool operator>(const Vertice<T>& otro) const {
        return distancia > otro.distancia;
    }
};

#endif