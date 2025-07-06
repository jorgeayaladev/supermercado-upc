#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <regex>
#include <limits>
#include <random>
#include <ctime>
#include <iomanip>

class Utilidades {
public:
    // Limpia la pantalla de consola
    static void limpiarPantalla() { system("cls"); }
    
    // Pausa la ejecución y espera a que el usuario presione una tecla
    static void pausar() {
        std::cout << std::endl << "Presione Enter para continuar...";
        system("pause>0");
    }
    
    // Muestra un mensaje de carga con animación
    static void mostrarCarga(const std::string& mensaje, int duracion = 3) {
        std::cout << mensaje << " ";
        for (int i = duracion; i > 0; i--) {
            std::cout << i << " ";
            std::cout.flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        std::cout << std::endl;
    }
    
    // Genera una línea de caracteres para separación visual
    static std::string generarLinea(char caracter = '-', int longitud = 50) {
        return std::string(longitud, caracter);
    }
    
    // Centra un texto en un espacio determinado
    static std::string centrarTexto(const std::string& texto, int espacio) {
        size_t padding = (espacio - texto.length()) / 2;
        return std::string(padding, ' ') + texto + std::string(padding, ' ');
    }
    
    // Valida si una cadena contiene solo dígitos
    static bool esNumerico(const std::string& texto) {
        return std::regex_match(texto, std::regex("^[0-9]+$"));
    }
    
    // Valida si una cadena contiene solo letras
    static bool esAlfabetico(const std::string& texto) {
        return std::regex_match(texto, std::regex("^[a-zA-Z ]+$"));
    }
    
    // Convierte una cadena a minúsculas
    static std::string aMinusculas(std::string texto) {
        std::transform(texto.begin(), texto.end(), texto.begin(), 
            [](unsigned char c) { return std::tolower(c); });
        return texto;
    }
    
    // Convierte una cadena a mayúsculas
    static std::string aMayusculas(std::string texto) {
        std::transform(texto.begin(), texto.end(), texto.begin(), 
            [](unsigned char c) { return std::toupper(c); });
        return texto;
    }
    
    // Genera un ID único basado en timestamp
    static std::string generarId() {
        auto ahora = std::chrono::system_clock::now();
        auto milisegundos = std::chrono::duration_cast<std::chrono::milliseconds>(
            ahora.time_since_epoch()).count();
        return std::to_string(milisegundos);
    }
    
    // Formatea un precio con dos decimales
    static std::string formatearPrecio(double precio) {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << precio;
        return ss.str();
    }
    
    // Obtiene la fecha actual en formato YYYY-MM-DD
    static std::string obtenerFechaActual() {
        auto t = std::time(nullptr);
        std::tm tm;
        localtime_s(&tm, &t);
        std::stringstream ss;
        ss << std::put_time(&tm, "%Y-%m-%d");
        return ss.str();
    }
    
    // Obtiene la hora actual en formato HH:MM:SS
    static std::string obtenerHoraActual() {
        auto t = std::time(nullptr);
        std::tm tm;
        localtime_s(&tm, &t);
        std::stringstream ss;
        ss << std::put_time(&tm, "%H:%M:%S");
        return ss.str();
    }
    
    // Genera un número aleatorio entre min y max
    static int generarAleatorio(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);
        return distrib(gen);
    }
    
    // Trunca un texto si es demasiado largo
    static std::string truncarTexto(const std::string& texto, int maxLongitud) {
        if (texto.length() <= maxLongitud) {
            return texto;
        }
        return texto.substr(0, maxLongitud - 3) + "...";
    }
};

#endif