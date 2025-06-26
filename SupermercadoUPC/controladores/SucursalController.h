#ifndef SUCURSAL_CONTROLLER_H
#define SUCURSAL_CONTROLLER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>
#include "../modelos/Sucursal.h"
#include "../estructuras/Lista.h"
#include "../estructuras/TablaHash.h"
#include "../estructuras/ArbolBinario.h"
#include "../estructuras/ABBalanceado.h"
#include "../estructuras/Grafo.h"
#include "../utilidades/Utilidades.h"
#include "../utilidades/Ordenamiento.h"

class SucursalController {
private:
    Lista<Sucursal> sucursales;
    TablaHash<std::string, Sucursal*> indiceSucursales; // Índice por ID
    ArbolBinario<Sucursal> arbolSucursales; // Ordenado por nombre
    ABBalanceado<Sucursal> arbolBalanceado; // Árbol balanceado por ventas
    Grafo<Sucursal> redSucursales; // Red de sucursales conectadas
    const std::string archivoSucursales = "datos/sucursales.txt";

public:
    // Constructor
    SucursalController() {
        cargarSucursales();
        construirIndices();
        construirRedSucursales();
    }
    
    // Métodos CRUD
    
    // Crear una nueva sucursal
    bool crear(const Sucursal& sucursal) {
        // Verificar si ya existe una sucursal con el mismo ID
        if (indiceSucursales.contiene(sucursal.getId())) {
            return false;
        }
        
        sucursales.insertarFinal(sucursal);
        
        // Actualizar índices
        Sucursal* ultimaSucursal = &(sucursales.obtener(sucursales.getTamano() - 1));
        indiceSucursales.insertar(sucursal.getId(), ultimaSucursal);
        arbolSucursales.insertar(sucursal);
        
        // Para el árbol balanceado, creamos una copia con índice de ventas
        Sucursal sucursalParaArbol = sucursal;
        arbolBalanceado.insertar(sucursalParaArbol);
        
        // Agregar al grafo
        redSucursales.agregarVertice(sucursal, sucursal.getId());
        
        guardarSucursales();
        return true;
    }
    
    // Obtener una sucursal por ID usando tabla hash
    Sucursal* obtenerPorId(const std::string& id) {
        Sucursal** sucursalPtr = indiceSucursales.buscar(id);
        return sucursalPtr ? *sucursalPtr : nullptr;
    }
    
    // Buscar sucursal por nombre usando árbol binario
    Sucursal* buscarPorNombre(const std::string& nombre) {
        Sucursal sucursalBusqueda;
        sucursalBusqueda.setNombre(nombre);
        
        Sucursal* encontrada = arbolSucursales.buscarReferencia(sucursalBusqueda);
        return encontrada;
    }
    
    // Obtener sucursales ordenadas por nombre
    std::vector<Sucursal> obtenerOrdenadasPorNombre() {
        return arbolSucursales.obtenerElementosOrdenados();
    }
    
    // Obtener sucursales en rango de ventas usando árbol balanceado
    std::vector<Sucursal> obtenerPorRangoVentas(double ventasMin, double ventasMax) {
        Sucursal sucursalMin, sucursalMax;
        sucursalMin.setVentasMensuales(ventasMin);
        sucursalMax.setVentasMensuales(ventasMax);
        
        return arbolBalanceado.buscarEnRango(sucursalMin, sucursalMax);
    }
    
    // Conectar sucursales en la red (grafo)
    bool conectarSucursales(const std::string& idOrigen, const std::string& idDestino, 
                           double distancia = 1.0, const std::string& tipoConexion = "carretera") {
        return redSucursales.agregarArco(idOrigen, idDestino, distancia, tipoConexion) != nullptr;
    }
    
    // Encontrar ruta más corta entre sucursales
    std::vector<std::string> encontrarRutaMasCorta(const std::string& idOrigen, const std::string& idDestino) {
        std::vector<Vertice<Sucursal>*> camino = redSucursales.caminoMasCorto(idOrigen, idDestino);
        
        std::vector<std::string> rutaIds;
        for (Vertice<Sucursal>* vertice : camino) {
            rutaIds.push_back(vertice->getId());
        }
        
        return rutaIds;
    }
    
    // Obtener sucursales conectadas a una sucursal específica
    std::vector<std::string> obtenerSucursalesConectadas(const std::string& idSucursal) {
        std::vector<std::string> conectadas;
        
        auto agregarConectada = [&conectadas](Vertice<Sucursal>* vertice) {
            conectadas.push_back(vertice->getId());
        };
        
        redSucursales.recorridoBFS(idSucursal, agregarConectada);
        
        return conectadas;
    }
    
    // Actualizar una sucursal existente
    bool actualizar(const Sucursal& sucursal) {
        bool encontrado = false;
        
        auto actualizarSucursal = [&sucursal, &encontrado, this](Sucursal& s) {
            if (s.getId() == sucursal.getId()) {
                s = sucursal;
                encontrado = true;
                
                // Actualizar en tabla hash
                this->indiceSucursales.insertar(sucursal.getId(), &s);
            }
        };
        
        sucursales.forEach(actualizarSucursal);
        
        if (encontrado) {
            // Reconstruir árboles con datos actualizados
            reconstruirArboles();
            guardarSucursales();
        }
        
        return encontrado;
    }
    
    // Eliminar una sucursal (marcándola como inactiva)
    bool eliminar(const std::string& id) {
        bool encontrado = false;
        
        auto eliminarSucursal = [&id, &encontrado](Sucursal& s) {
            if (s.getId() == id) {
                s.setActiva(false);
                encontrado = true;
            }
        };
        
        sucursales.forEach(eliminarSucursal);
        
        if (encontrado) {
            // Eliminar del grafo
            redSucursales.eliminarVertice(id);
            reconstruirArboles();
            guardarSucursales();
        }
        
        return encontrado;
    }
    
    // Obtener todas las sucursales
    Lista<Sucursal>& obtenerTodas() {
        return sucursales;
    }
    
    // Obtener sucursales activas
    Lista<Sucursal> obtenerActivas() {
        auto filtrarActivas = [](const Sucursal& s) {
            return s.isActiva();
        };
        
        return sucursales.filtrar(filtrarActivas);
    }
    
    // Análisis de red de sucursales
    void analizarRedSucursales() {
        std::cout << "=== ANALISIS DE RED DE SUCURSALES ===" << std::endl;
        std::cout << "Numero de sucursales: " << redSucursales.getNumVertices() << std::endl;
        std::cout << "Numero de conexiones: " << redSucursales.getNumArcos() << std::endl;
        
        // Verificar si la red está conectada
        auto componentes = redSucursales.obtenerComponentesConexas();
        std::cout << "Componentes conexas: " << componentes.size() << std::endl;
        
        if (componentes.size() == 1) {
            std::cout << "La red esta completamente conectada." << std::endl;
        } else {
            std::cout << "La red tiene " << componentes.size() << " grupos separados." << std::endl;
        }
        
        // Mostrar información del grafo
        redSucursales.mostrarGrafo();
    }
    
    // Estadísticas usando las diferentes estructuras
    void mostrarEstadisticas() {
        std::cout << "=== ESTADISTICAS DE SUCURSALES ===" << std::endl;
        
        // Usando tabla hash para acceso rápido
        std::cout << "Total de sucursales en indice: " << indiceSucursales.getTamano() << std::endl;
        std::cout << "Factor de carga de tabla hash: " << indiceSucursales.obtenerFactorCarga() << std::endl;
        
        // Usando árbol binario para orden
        std::cout << "Altura del arbol de nombres: " << arbolSucursales.getAltura() << std::endl;
        std::cout << "Elementos en arbol: " << arbolSucursales.getTamano() << std::endl;
        
        // Usando árbol balanceado
        std::cout << "Altura del arbol balanceado: " << arbolBalanceado.getAltura() << std::endl;
        std::cout << "Esta balanceado: " << (arbolBalanceado.estaBalanceado() ? "Si" : "No") << std::endl;
        
        // Estadísticas de ventas
        if (!sucursales.estaVacia()) {
            double totalVentas = 0;
            int sucursalesActivas = 0;
            
            auto calcularEstadisticas = [&totalVentas, &sucursalesActivas](const Sucursal& s) {
                if (s.isActiva()) {
                    totalVentas += s.getVentasMensuales();
                    sucursalesActivas++;
                }
            };
            
            sucursales.forEach(calcularEstadisticas);
            
            std::cout << "Sucursales activas: " << sucursalesActivas << std::endl;
            std::cout << "Ventas totales mensuales: $" << totalVentas << std::endl;
            if (sucursalesActivas > 0) {
                std::cout << "Promedio de ventas por sucursal: $" << (totalVentas / sucursalesActivas) << std::endl;
            }
        }
    }
    
    // Cargar sucursales desde archivo
    void cargarSucursales() {
        std::ifstream archivo(archivoSucursales);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo de sucursales. Se creará uno nuevo al guardar." << std::endl;
            return;
        }
        
        std::string linea;
        while (std::getline(archivo, linea)) {
            if (!linea.empty()) {
                Sucursal sucursal = Sucursal::desdeCSV(linea);
                sucursales.insertarFinal(sucursal);
            }
        }
        
        archivo.close();
    }
    
    // Guardar sucursales en archivo
    void guardarSucursales() {
        // Crear el directorio si no existe
        system("mkdir -p datos");
        
        std::ofstream archivo(archivoSucursales);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para guardar las sucursales." << std::endl;
            return;
        }
        
        auto guardarSucursal = [&archivo](const Sucursal& s) {
            archivo << s.aCSV() << std::endl;
        };
        
        sucursales.forEach(guardarSucursal);
        
        archivo.close();
    }

private:
    // Construir índices después de cargar datos
    void construirIndices() {
        indiceSucursales.limpiar();
        arbolSucursales.limpiar();
        arbolBalanceado.limpiar();
        
        auto construirIndice = [this](Sucursal& s) {
            if (s.isActiva()) {
                this->indiceSucursales.insertar(s.getId(), &s);
                this->arbolSucursales.insertar(s);
                this->arbolBalanceado.insertar(s);
            }
        };
        
        sucursales.forEach(construirIndice);
    }
    
    // Reconstruir árboles cuando hay cambios
    void reconstruirArboles() {
        arbolSucursales.limpiar();
        arbolBalanceado.limpiar();
        
        auto reconstruir = [this](const Sucursal& s) {
            if (s.isActiva()) {
                this->arbolSucursales.insertar(s);
                this->arbolBalanceado.insertar(s);
            }
        };
        
        sucursales.forEach(reconstruir);
    }
    
    // Construir red de sucursales (grafo)
    void construirRedSucursales() {
        redSucursales.limpiar();
        
        // Agregar todas las sucursales como vértices
        auto agregarVertice = [this](const Sucursal& s) {
            if (s.isActiva()) {
                this->redSucursales.agregarVertice(s, s.getId());
            }
        };
        
        sucursales.forEach(agregarVertice);
        
        // Aquí podrías agregar conexiones predefinidas entre sucursales
        // Por ejemplo, conectar sucursales cercanas geográficamente
    }
};

#endif