#ifndef TABLA_HASH_H
#define TABLA_HASH_H

#include <vector>
#include <functional>
#include <string>
#include "Lista.h"

template <typename K, typename V>
class TablaHash {
private:
    struct ParClaveValor {
        K clave;
        V valor;
        
        ParClaveValor(const K& _clave, const V& _valor) : clave(_clave), valor(_valor) {}
        
        bool operator==(const ParClaveValor& otro) const {
            return clave == otro.clave;
        }
    };
    
    std::vector<Lista<ParClaveValor>> tabla;
    int capacidad;
    int tamano;
    double factorCarga;
    
    // Función hash para strings
    int hash(const std::string& clave) const {
        int hashValue = 0;
        for (char c : clave) {
            hashValue = (hashValue * 31 + c) % capacidad;
        }
        return hashValue < 0 ? hashValue + capacidad : hashValue;
    }
    
    // Función hash genérica
    template<typename T>
    int hash(const T& clave) const {
        return std::hash<T>{}(clave) % capacidad;
    }
    
    // Redimensionar la tabla cuando el factor de carga es alto
    void redimensionar() {
        if ((double)tamano / capacidad > factorCarga) {
            std::vector<Lista<ParClaveValor>> tablaAntigua = tabla;
            int capacidadAntigua = capacidad;
            
            capacidad *= 2;
            tamano = 0;
            tabla.clear();
            tabla.resize(capacidad);
            
            // Reinsertar todos los elementos
            for (int i = 0; i < capacidadAntigua; i++) {
                auto insertarElemento = [this](const ParClaveValor& par) {
                    this->insertar(par.clave, par.valor);
                };
                tablaAntigua[i].forEach(insertarElemento);
            }
        }
    }

public:
    TablaHash(int _capacidad = 16, double _factorCarga = 0.75) 
        : capacidad(_capacidad), tamano(0), factorCarga(_factorCarga) {
        tabla.resize(capacidad);
    }
    
    void insertar(const K& clave, const V& valor) {
        int indice = hash(clave);
        
        // Buscar si la clave ya existe
        auto buscarClave = [&clave](const ParClaveValor& par) {
            return par.clave == clave;
        };
        
        ParClaveValor* existente = tabla[indice].buscar(buscarClave);
        
        if (existente) {
            // Actualizar valor existente
            existente->valor = valor;
        } else {
            // Insertar nuevo par clave-valor
            tabla[indice].insertarFinal(ParClaveValor(clave, valor));
            tamano++;
            redimensionar();
        }
    }
    
    V* buscar(const K& clave) {
        int indice = hash(clave);
        
        auto buscarClave = [&clave](const ParClaveValor& par) {
            return par.clave == clave;
        };
        
        ParClaveValor* encontrado = tabla[indice].buscar(buscarClave);
        return encontrado ? &(encontrado->valor) : nullptr;
    }
    
    bool eliminar(const K& clave) {
        int indice = hash(clave);
        Lista<ParClaveValor> nuevaLista;
        bool eliminado = false;
        
        auto filtrarElemento = [&clave, &eliminado](const ParClaveValor& par) {
            if (par.clave == clave) {
                eliminado = true;
                return false;
            }
            return true;
        };
        
        nuevaLista = tabla[indice].filtrar(filtrarElemento);
        tabla[indice] = nuevaLista;
        
        if (eliminado) {
            tamano--;
        }
        
        return eliminado;
    }
    
    bool contiene(const K& clave) {
        return buscar(clave) != nullptr;
    }
    
    int getTamano() const {
        return tamano;
    }
    
    bool estaVacia() const {
        return tamano == 0;
    }
    
    void aplicarFuncion(std::function<void(const K&, const V&)> funcion) {
        for (int i = 0; i < capacidad; i++) {
            auto aplicarAElemento = [&funcion](const ParClaveValor& par) {
                funcion(par.clave, par.valor);
            };
            tabla[i].forEach(aplicarAElemento);
        }
    }
    
    std::vector<K> obtenerClaves() {
        std::vector<K> claves;
        
        auto agregarClave = [&claves](const K& clave, const V& valor) {
            claves.push_back(clave);
        };
        
        aplicarFuncion(agregarClave);
        return claves;
    }
    
    std::vector<V> obtenerValores() {
        std::vector<V> valores;
        
        auto agregarValor = [&valores](const K& clave, const V& valor) {
            valores.push_back(valor);
        };
        
        aplicarFuncion(agregarValor);
        return valores;
    }
    
    void limpiar() {
        for (int i = 0; i < capacidad; i++) {
            tabla[i].vaciar();
        }
        tamano = 0;
    }
    
    double obtenerFactorCarga() const {
        return (double)tamano / capacidad;
    }
};

#endif