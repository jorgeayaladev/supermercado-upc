// Librerías principales
#include <iostream>
#include <string>
#include <vector>
#include <functional>

// Archivos de cabecera personalizados
// Estructuras
#include "estructuras/Nodo.h"
#include "estructuras/Lista.h"
#include "estructuras/Pila.h"
#include "estructuras/Cola.h"
#include "estructuras/TablaHash.h"
#include "estructuras/ArbolBinario.h"
#include "estructuras/ABBalanceado.h"
#include "estructuras/Vertice.h"
#include "estructuras/Arco.h"
#include "estructuras/Grafo.h"
// Utilidades
#include "utilidades/Utilidades.h"
#include "utilidades/Ordenamiento.h"
#include "utilidades/DataSetGenerator.h"

// Patrón MVC
// Modelos
#include "modelos/Producto.h"
#include "modelos/ProductoIndexado.h"
#include "modelos/Categoria.h"
#include "modelos/Cliente.h"
#include "modelos/Empleado.h"
#include "modelos/Proveedor.h"
#include "modelos/ItemCarrito.h"
#include "modelos/Carrito.h"
#include "modelos/Venta.h"
#include "modelos/Reporte.h"
#include "modelos/Usuario.h"
#include "modelos/Sucursal.h"
// Controladores
#include "controladores/ProductoController.h"
#include "controladores/CategoriaController.h"
#include "controladores/ClienteController.h"
#include "controladores/EmpleadoController.h"
#include "controladores/ProveedorController.h"
#include "controladores/CarritoController.h"
#include "controladores/VentaController.h"
#include "controladores/ReporteController.h"
#include "controladores/UsuarioController.h"
#include "controladores/SucursalController.h"
// Vistas
#include "vistas/Menu.h"
#include "vistas/ProductoVista.h"
#include "vistas/EmpleadoVista.h"
#include "vistas/ProveedorVista.h"
#include "vistas/ReporteVista.h"
#include "vistas/VentaVista.h"
#include "vistas/CategoriaVista.h"
#include "vistas/ClienteVista.h"
#include "vistas/LoginVista.h"
#include "vistas/SucursalVista.h"
#include "vistas/DataSetVista.h"

// Lambda para mostrar un banner de bienvenida
auto mostrarBanner = []() {
    Utilidades::limpiarPantalla();
    std::cout << "\033[1;36m";
    std::cout << "||===========================================================================================||" << std::endl;
    std::cout << "||    _________                                                                  .___        ||" << std::endl;
    std::cout << "||   /   _____/__ ________   ___________  _____   ___________   ____ _____     __| _/____    ||" << std::endl;
    std::cout << "||   \\_____  \\|  |  \\____ \\_/ __ \\_  __ \\/     \\_/ __ \\_  __ \\_/ ___\\\\__  \\   / __ |/  _ \\   ||" << std::endl;
    std::cout << "||   /        \\  |  /  |_> >  ___/|  | \\/  Y Y  \\  ___/|  | \\/\\  \\___ / __ \\_/ /_/ (  <_> )  ||" << std::endl;
    std::cout << "||  /_______  /____/|   __/ \\___  >__|  |__|_|  /\\___  >__|    \\___  >____  /\\____ |\\____/   ||" << std::endl;
    std::cout << "||          \\/      |__|        \\/            \\/     \\/            \\/     \\/      \\/         ||" << std::endl;
    std::cout << "||   ____ ______________________                                                             ||" << std::endl;
    std::cout << "||  |    |   \\______   \\_   ___ \\                                                            ||" << std::endl;
    std::cout << "||  |    |   /|     ___/    \\  \\/                                                            ||" << std::endl;
    std::cout << "||  |    |  / |    |   \\     \\____                                                           ||" << std::endl;
    std::cout << "||  |______/  |____|    \\______  /                                                           ||" << std::endl;
    std::cout << "||                             \\/                                                            ||" << std::endl;
    std::cout << "||===========================================================================================||" << std::endl;
    std::cout << "||                                                                                           ||" << std::endl;
    std::cout << "||      Bienvenido a Supermercado UPC!, aplicacion de consola realizada por el Grupo 2       ||" << std::endl;
    std::cout << "||                                                                                           ||" << std::endl;
    std::cout << "||===========================================================================================||" << std::endl;
    std::cout << "\033[0m";
    };

// Lambda para mostrar detalles del sistema
auto mostrarDetallesSistema = []() {
    Utilidades::limpiarPantalla();
    std::cout << "|| ================================================= ||" << std::endl;
    std::cout << "||              INFORMACION DEL SISTEMA              ||" << std::endl;
    std::cout << "|| ================================================= ||" << std::endl;
    std::cout << "|| Nombre: Sistema de Gestion de Supermercado        ||" << std::endl;
    std::cout << "|| Version: 2.0.0                                    ||" << std::endl;
    std::cout << "|| Fecha: " << Utilidades::obtenerFechaActual() << std::endl;
    std::cout << "|| Desarrollado por: Grupo 2                         ||" << std::endl;
    std::cout << "|| ------------------------------------------------- ||" << std::endl;
    std::cout << "|| Integrantes:                                      ||" << std::endl;
    std::cout << "|| ------------------------------------------------- ||" << std::endl;
    std::cout << "||   - Ayala Fernandez, Jorge Brayan                 ||" << std::endl;
    std::cout << "||   - Alarcon Castellanos, Ericks Santiago          ||" << std::endl;
    std::cout << "||   - Chaca Gonzales, Miguel Sebastian              ||" << std::endl;
    std::cout << "|| ================================================= ||" << std::endl;
    std::cout << std::endl;
    std::cout << "|| ================================================= ||" << std::endl;
    std::cout << "|| Este sistema incluye los siguientes modulos:      ||" << std::endl;
    std::cout << "|| ------------------------------------------------- ||" << std::endl;
    std::cout << "||    - Gestion de productos e inventario            ||" << std::endl;
    std::cout << "||    - Gestion de categorias                        ||" << std::endl;
    std::cout << "||    - Gestion de clientes                          ||" << std::endl;
    std::cout << "||    - Gestion de empleados                         ||" << std::endl;
    std::cout << "||    - Gestion de proveedores                       ||" << std::endl;
    std::cout << "||    - Gestion de sucursales                        ||" << std::endl;
    std::cout << "||    - Proceso de ventas                            ||" << std::endl;
    std::cout << "||    - Reportes y estadisticas                      ||" << std::endl;
    std::cout << "||    - Generador de datasets                        ||" << std::endl;
    std::cout << "|| ================================================= ||" << std::endl;
    std::cout << std::endl;
    std::cout << "|| ================================================= ||" << std::endl;
    std::cout << "|| Estructuras de datos implementadas:               ||" << std::endl;
    std::cout << "|| ------------------------------------------------- ||" << std::endl;
    std::cout << "||    - Listas enlazadas                             ||" << std::endl;
    std::cout << "||    - Pilas                                        ||" << std::endl;
    std::cout << "||    - Colas                                        ||" << std::endl;
    std::cout << "||    - Tablas Hash                                  ||" << std::endl;
    std::cout << "||    - Arboles Binarios de Busqueda                 ||" << std::endl;
    std::cout << "||    - Arboles Binarios Balanceados (AVL)           ||" << std::endl;
    std::cout << "||    - Grafos                                       ||" << std::endl;
    std::cout << "|| ================================================= ||" << std::endl;
    Utilidades::pausar();
    };

// Lambda para validar una entrada numérica
auto validarNumero = [](const std::string& input) -> bool {
    return !input.empty() && std::all_of(input.begin(), input.end(), ::isdigit);
    };

// Lambda para formatear texto a mayúsculas
auto formatearMayusculas = [](std::string texto) -> std::string {
    std::transform(texto.begin(), texto.end(), texto.begin(), ::toupper);
    return texto;
    };

// Lambda para formatear texto a minúsculas
auto formatearMinusculas = [](std::string texto) -> std::string {
    std::transform(texto.begin(), texto.end(), texto.begin(), ::tolower);
    return texto;
    };

// Lambda para generar un ID único
auto generarIdUnico = []() -> std::string {
    return Utilidades::generarId();
    };

// Lambda para verificar si una cadena es un email válido
auto esEmailValido = [](const std::string& email) -> bool {
    // Verificación simple: debe contener @ y al menos un punto después
    size_t arrobaPos = email.find('@');
    if (arrobaPos == std::string::npos) return false;

    size_t puntoPos = email.find('.', arrobaPos);
    if (puntoPos == std::string::npos) return false;

    return puntoPos > arrobaPos && puntoPos < email.length() - 1;
    };

// Lambda para verificar si una cadena es un teléfono válido
auto esTelefonoValido = [](const std::string& telefono) -> bool {
    // Verificación simple: debe contener solo dígitos, guiones y espacios
    return std::all_of(telefono.begin(), telefono.end(), [](char c) {
        return std::isdigit(c) || c == '-' || c == ' ' || c == '+';
        });
    };

// Lambda para calcular descuento
auto calcularDescuento = [](double precio, double porcentaje) -> double {
    return precio * (porcentaje / 100.0);
    };

// Lambda para calcular precio con impuesto
auto calcularImpuesto = [](double precio, double porcentaje) -> double {
    return precio * (porcentaje / 100.0);
    };

// Lambda para mostrar un mensaje de confirmación
auto confirmarAccion = [](const std::string& mensaje) -> bool {
    return Menu::confirmar(mensaje);
    };

// Lambda para mostrar un mensaje de éxito
auto mostrarExito = [](const std::string& mensaje) {
    Menu::mostrarExito(mensaje);
    };

// Lambda para mostrar un mensaje de error
auto mostrarError = [](const std::string& mensaje) {
    Menu::mostrarError(mensaje);
    };

// Lambda para obtener una fecha formateada
auto obtenerFechaFormateada = []() -> std::string {
    return Utilidades::obtenerFechaActual();
    };

// Lambda para validar una fecha en formato YYYY-MM-DD
auto esFechaValida = [](const std::string& fecha) -> bool {
    if (fecha.length() != 10) return false;
    if (fecha[4] != '-' || fecha[7] != '-') return false;

    try {
        int anio = std::stoi(fecha.substr(0, 4));
        int mes = std::stoi(fecha.substr(5, 2));
        int dia = std::stoi(fecha.substr(8, 2));

        if (anio < 1900 || anio > 2100) return false;
        if (mes < 1 || mes > 12) return false;
        if (dia < 1 || dia > 31) return false;

        return true;
    }
    catch (...) {
        return false;
    }
    };

int main() {
    // Crear instancias de controladores
    ProductoController productoController;
    CategoriaController categoriaController;
    ClienteController clienteController;
    EmpleadoController empleadoController;
    ProveedorController proveedorController;
    CarritoController carritoController(productoController);
    VentaController ventaController(productoController, clienteController);
    ReporteController reporteController(productoController, clienteController, ventaController);
    UsuarioController usuarioController;
    SucursalController sucursalController;
    DataSetGenerator dataSetGenerator;

    // Crear vistas
    ProductoVista productoVista(productoController, categoriaController);
    CategoriaVista categoriaVista(categoriaController, productoController);
    ClienteVista clienteVista(clienteController);
    EmpleadoVista empleadoVista(empleadoController);
    ProveedorVista proveedorVista(proveedorController);
    VentaVista ventaVista(ventaController, carritoController, clienteController, empleadoController);
    ReporteVista reporteVista(reporteController);
    LoginVista loginVista(usuarioController);
    SucursalVista sucursalVista(sucursalController);
    DataSetVista dataSetVista(dataSetGenerator, productoController, categoriaController,
                             clienteController, empleadoController, proveedorController,
                             ventaController, carritoController);

    // Pruebas
    // ventaVista.mostrarMenuCliente("CL001");

    // Mostrar animación de carga inicial
    std::cout << "\033[1;36m";
    Utilidades::mostrarCarga("|| => Iniciando en");
    std::cout << "\033[0m";

    // Mostrar banner de bienvenida
    mostrarBanner();
    Utilidades::pausar();

    // Login
    bool loginExitoso = false;
    do {
        loginExitoso = loginVista.mostrarLogin();
    } while (!loginExitoso);

    // Menú principal
    bool salir = false;
    while (!salir) {
        Menu menuPrincipal("MENU PRINCIPAL");

        if (usuarioController.esAdministrador()) {
            menuPrincipal.agregarOpcion("Gestionar Productos"); // Perfecto
            menuPrincipal.agregarOpcion("Gestionar Categorias"); // Perfecto
            menuPrincipal.agregarOpcion("Gestionar Clientes"); // Perfecto
            menuPrincipal.agregarOpcion("Gestionar Empleados"); // Perfecto
            menuPrincipal.agregarOpcion("Gestionar Proveedores"); // Perfecto
            menuPrincipal.agregarOpcion("Gestionar Sucursales"); // Falta
            menuPrincipal.agregarOpcion("Reportes y Estadisticas"); // Falta
            menuPrincipal.agregarOpcion("Generador de DataSet"); // Falta
            menuPrincipal.agregarOpcion("Informacion del Sistema"); // Perfecto
        }
        else if (usuarioController.esCliente()) {
            menuPrincipal.agregarOpcion("Ver Productos"); // Perfecto
            menuPrincipal.agregarOpcion("Ver Categorias"); // Perfecto
            menuPrincipal.agregarOpcion("Proceso de Compras"); // Perfecto
            menuPrincipal.agregarOpcion("Mi Perfil"); // Perfecto
        }

        menuPrincipal.agregarOpcion("Cerrar Sesion");

        int opcion = menuPrincipal.mostrar();

        if (usuarioController.esAdministrador()) {
            switch (opcion) {
            case 1: productoVista.mostrarMenu(); break;
            case 2: categoriaVista.mostrarMenu(); break;
            case 3: clienteVista.mostrarMenu(); break;
            case 4: empleadoVista.mostrarMenu(); break;
            case 5: proveedorVista.mostrarMenu(); break;
            case 6: sucursalVista.mostrarMenu(); break;
            case 7: reporteVista.mostrarMenu(); break;
            case 8: dataSetVista.mostrarMenu(); break;
            case 9: mostrarDetallesSistema(); break;
            case 10:
                if (Menu::confirmar("Esta seguro de que desea cerrar sesion?")) {
                    usuarioController.logout();
                    do {
                        loginExitoso = loginVista.mostrarLogin();
                    } while (!loginExitoso);
                }
                break;
            }
        }
        else if (usuarioController.esCliente()) {
            switch (opcion) {
            case 1: productoVista.mostrarCatalogo(); break;
            case 2: categoriaVista.mostrarCatalogo(); break;
            case 3:
                ventaVista.mostrarMenuCliente(usuarioController.getUsuarioActual()->getId());
                break;
            case 4:
                clienteVista.mostrarPerfil(usuarioController.getUsuarioActual()->getId());
                break;
            case 5:
                if (Menu::confirmar("Esta seguro de que desea cerrar sesion?")) {
                    usuarioController.logout();
                    do {
                        loginExitoso = loginVista.mostrarLogin();
                    } while (!loginExitoso);
                }
                break;
            }
        }
    }

    return 0;
}