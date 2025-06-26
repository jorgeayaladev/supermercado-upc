#ifndef ARCO_H
#define ARCO_H

#include "Vertice.h"
#include <string>
#include <limits>

template <typename T>
class Arco {
private:
    Vertice<T>* origen;
    Vertice<T>* destino;
    double peso;
    std::string etiqueta;
    bool dirigido;

public:
    Arco(Vertice<T>* _origen, Vertice<T>* _destino, double _peso = 1.0, 
         const std::string& _etiqueta = "", bool _dirigido = true)
        : origen(_origen), destino(_destino), peso(_peso), etiqueta(_etiqueta), dirigido(_dirigido) {}
    
    // Getters y setters
    Vertice<T>* getOrigen() const { return origen; }
    void setOrigen(Vertice<T>* _origen) { origen = _origen; }
    
    Vertice<T>* getDestino() const { return destino; }
    void setDestino(Vertice<T>* _destino) { destino = _destino; }
    
    double getPeso() const { return peso; }
    void setPeso(double _peso) { peso = _peso; }
    
    std::string getEtiqueta() const { return etiqueta; }
    void setEtiqueta(const std::string& _etiqueta) { etiqueta = _etiqueta; }
    
    bool esDirigido() const { return dirigido; }
    void setDirigido(bool _dirigido) { dirigido = _dirigido; }
    
    // Métodos de utilidad
    Vertice<T>* getOtroVertice(Vertice<T>* vertice) const {
        if (vertice == origen) {
            return destino;
        } else if (vertice == destino && !dirigido) {
            return origen;
        }
        return nullptr;
    }
    
    bool conecta(Vertice<T>* v1, Vertice<T>* v2) const {
        if (dirigido) {
            return (origen == v1 && destino == v2);
        } else {
            return (origen == v1 && destino == v2) || (origen == v2 && destino == v1);
        }
    }
    
    bool incidenteA(Vertice<T>* vertice) const {
        return origen == vertice || destino == vertice;
    }
    
    std::string toString() const {
        std::string resultado = origen->getId();
        if (dirigido) {
            resultado += " -> ";
        } else {
            resultado += " -- ";
        }
        resultado += destino->getId();
        
        if (peso != 1.0) {
            resultado += " (peso: " + std::to_string(peso) + ")";
        }
        
        if (!etiqueta.empty()) {
            resultado += " [" + etiqueta + "]";
        }
        
        return resultado;
    }
    
    // Sobrecarga de operadores
    bool operator==(const Arco<T>& otro) const {
        if (dirigido) {
            return origen == otro.origen && destino == otro.destino;
        } else {
            return (origen == otro.origen && destino == otro.destino) ||
                   (origen == otro.destino && destino == otro.origen);
        }
    }
    
    bool operator!=(const Arco<T>& otro) const {
        return !(*this == otro);
    }
    
    bool operator<(const Arco<T>& otro) const {
        return peso < otro.peso;
    }
    
    bool operator>(const Arco<T>& otro) const {
        return peso > otro.peso;
    }
};

#endif