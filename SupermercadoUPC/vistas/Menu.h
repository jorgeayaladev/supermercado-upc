#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <functional>
#include "../utilidades/Utilidades.h"

class Menu {
private:
    std::string titulo;
    std::vector<std::string> opciones;
    char bordeHorizontal;
    char bordeVertical;
    char bordeEsquina;
    int ancho;
    std::string colorTitulo;
    std::string colorBorde;
    std::string colorBase;

public:
    // Constructor
    Menu(const std::string& _titulo = "", int _ancho = 60) 
        : titulo(_titulo), ancho(_ancho), bordeHorizontal('='), bordeVertical('|'), 
          bordeEsquina('+'), colorTitulo("\033[1;36m"), colorBorde("\033[1;33m"), 
          colorBase("\033[0m") {}
    
    // Añadir una opción al menú
    void agregarOpcion(const std::string& opcion) {
        opciones.push_back(opcion);
    }
    
    // Establecer el título del menú
    void setTitulo(const std::string& _titulo) {
        titulo = _titulo;
    }
    
    // Establecer el ancho del menú
    void setAncho(int _ancho) {
        ancho = _ancho;
    }
    
    // Establecer caracteres de borde
    void setBorde(char _horizontal, char _vertical, char _esquina) {
        bordeHorizontal = _horizontal;
        bordeVertical = _vertical;
        bordeEsquina = _esquina;
    }
    
    // Mostrar el menú y obtener la selección del usuario
    int mostrar() const {
        Utilidades::limpiarPantalla();
        
        // Dibujar borde superior
        std::cout << colorBorde << "||==========================================================||" << colorBase << std::endl;
        
        // Mostrar título centrado
        if (!titulo.empty()) {
            std::string tituloAlineado = Utilidades::centrarTexto(titulo, ancho - 4);
            std::cout << colorBorde << "||" << colorBase << " " << colorTitulo << tituloAlineado << colorBase << " " << colorBorde << "||" << colorBase << std::endl;
            std::cout << colorBorde << "||==========================================================||" << colorBase << std::endl;
            std::cout << colorBorde << "||" << std::string(ancho - 2, ' ') << "||" << colorBase << std::endl;
        }
        
        // Mostrar opciones
        for (size_t i = 0; i < opciones.size(); i++) {
            std::cout << colorBorde << "||" << colorBase << " " << std::left << std::setw(3) << (i + 1) << " "
                      << std::left << std::setw(ancho - 8) << opciones[i]
                      << " " << colorBorde << "||" << colorBase << std::endl;
        }
        
        // Dibujar borde inferior
        std::cout << colorBorde << "||==========================================================||" << colorBase << std::endl;
        
        // Solicitar selección
        int seleccion = 0;
        do {
            std::cout << "\nSeleccione una opcion (1-" << opciones.size() << "): ";
            std::string entrada;
            std::getline(std::cin, entrada);
            
            if (Utilidades::esNumerico(entrada)) {
                seleccion = std::stoi(entrada);
            }
            
            if (seleccion < 1 || seleccion > static_cast<int>(opciones.size())) {
                std::cout << "Opcion invalida. Intente de nuevo." << std::endl;
                seleccion = 0;
            }
        } while (seleccion == 0);
        
        return seleccion;
    }
    
    // Mostrar mensaje de confirmación y obtener respuesta (S/N)
    static bool confirmar(const std::string& mensaje) {
        std::cout << "\n" << mensaje << " (S/N): ";
        std::string respuesta;
        std::getline(std::cin, respuesta);
        
        return (Utilidades::aMinusculas(respuesta) == "s" || 
                Utilidades::aMinusculas(respuesta) == "si" || 
                Utilidades::aMinusculas(respuesta) == "y" || 
                Utilidades::aMinusculas(respuesta) == "yes");
    }
    
    // Mostrar un mensaje y esperar a que el usuario presione Enter
    static void mostrarMensaje(const std::string& mensaje) {
        std::cout << "\n" << mensaje << std::endl;
        Utilidades::pausar();
    }
    
    // Mostrar un mensaje de error y esperar a que el usuario presione Enter
    static void mostrarError(const std::string& mensaje) {
        std::cout << "\n\033[1;31mError: " << mensaje << "\033[0m" << std::endl;
        Utilidades::pausar();
    }
    
    // Mostrar un mensaje de éxito y esperar a que el usuario presione Enter
    static void mostrarExito(const std::string& mensaje) {
        std::cout << "\n\033[1;32mExito: " << mensaje << "\033[0m" << std::endl;
        Utilidades::pausar();
    }
    
    // Mostrar un mensaje de información y esperar a que el usuario presione Enter
    static void mostrarInfo(const std::string& mensaje) {
        std::cout << "\n\033[1;34mInfo: " << mensaje << "\033[0m" << std::endl;
        Utilidades::pausar();
    }
};

#endif