#ifndef VENTA_VISTA_H
#define VENTA_VISTA_H

#include <string>
#include <iostream>
#include <iomanip>
#include "../modelos/Venta.h"
#include "../modelos/Carrito.h"
#include "../controladores/VentaController.h"
#include "../controladores/CarritoController.h"
#include "../controladores/ClienteController.h"
#include "../controladores/EmpleadoController.h"
#include "../utilidades/Utilidades.h"
#include "Menu.h"

class VentaVista {
private:
    VentaController& ventaController;
    CarritoController& carritoController;
    ClienteController& clienteController;
    EmpleadoController& empleadoController;

public:
    VentaVista(VentaController& _ventaController, 
               CarritoController& _carritoController,
               ClienteController& _clienteController,
               EmpleadoController& _empleadoController)
        : ventaController(_ventaController),
          carritoController(_carritoController),
          clienteController(_clienteController),
          empleadoController(_empleadoController) {}
    
    void mostrarMenu() {
        bool salir = false;
        
        while (!salir) {
            Menu menu("PROCESO DE VENTAS");
            menu.agregarOpcion("Realizar nueva venta");
            menu.agregarOpcion("Ver ventas del dia");
            menu.agregarOpcion("Buscar venta");
            menu.agregarOpcion("Cancelar venta");
            menu.agregarOpcion("Ver ventas por cliente");
            menu.agregarOpcion("Ver ventas por empleado");
            menu.agregarOpcion("Ver ventas por metodo de pago");
            menu.agregarOpcion("Volver al menu principal");
            
            int opcion = menu.mostrar();
            
            switch (opcion) {
                case 1:
                    realizarVenta();
                    break;
                case 2:
                    verVentasDelDia();
                    break;
                case 3:
                    buscarVenta();
                    break;
                case 4:
                    cancelarVenta();
                    break;
                case 5:
                    verVentasPorCliente();
                    break;
                case 6:
                    verVentasPorEmpleado();
                    break;
                case 7:
                    verVentasPorMetodoPago();
                    break;
                case 8:
                    salir = true;
                    break;
            }
        }
    }
    
    void realizarVenta() {
        Utilidades::limpiarPantalla();
        std::cout << "===== REALIZAR NUEVA VENTA =====" << std::endl;
        
        // Solicitar ID del cliente
        std::cout << "ID del cliente: ";
        std::string clienteId;
        std::getline(std::cin, clienteId);
        
        Cliente* cliente = clienteController.obtenerPorId(clienteId);
        if (!cliente) {
            Menu::mostrarError("Cliente no encontrado");
            return;
        }
        
        // Verificar si el cliente tiene un carrito activo
        Carrito* carrito = carritoController.obtenerCarritoActivoCliente(clienteId);
        if (!carrito) {
            carrito = carritoController.crear(clienteId);
            if (!carrito) {
                Menu::mostrarError("No se pudo crear el carrito");
                return;
            }
        }
        
        bool finalizarCompra = false;
        while (!finalizarCompra) {
            Menu menuCarrito("CARRITO DE COMPRA");
            menuCarrito.agregarOpcion("Agregar producto");
            menuCarrito.agregarOpcion("Eliminar producto");
            menuCarrito.agregarOpcion("Actualizar cantidad");
            menuCarrito.agregarOpcion("Ver carrito");
            menuCarrito.agregarOpcion("Aplicar descuento");
            menuCarrito.agregarOpcion("Finalizar compra");
            menuCarrito.agregarOpcion("Cancelar compra");
            
            int opcion = menuCarrito.mostrar();
            
            switch (opcion) {
                case 1:
                    agregarProductoCarrito(carrito);
                    break;
                case 2:
                    eliminarProductoCarrito(carrito);
                    break;
                case 3:
                    actualizarCantidadCarrito(carrito);
                    break;
                case 4:
                    verCarrito(carrito);
                    break;
                case 5:
                    aplicarDescuento(carrito);
                    break;
                case 6:
                    if (finalizarCompra = procesarVenta(carrito)) {
                        Menu::mostrarExito("Venta realizada correctamente");
                    }
                    break;
                case 7:
                    if (Menu::confirmar("¿Esta seguro de que desea cancelar la compra?")) {
                        carritoController.cancelar(carrito->getId());
                        finalizarCompra = true;
                        Menu::mostrarInfo("Compra cancelada");
                    }
                    break;
            }
        }
    }
    
    void verVentasDelDia() {
        Utilidades::limpiarPantalla();
        std::cout << "===== VENTAS DEL DIA =====" << std::endl;
        
        std::string fechaActual = Utilidades::obtenerFechaActual();
        Lista<Venta> ventas = ventaController.obtenerPorFecha(fechaActual);
        
        if (ventas.estaVacia()) {
            Menu::mostrarInfo("No hay ventas registradas hoy");
            return;
        }
        
        mostrarTablaVentas(ventas);
        
        Utilidades::pausar();
    }
    
    void buscarVenta() {
        Utilidades::limpiarPantalla();
        std::cout << "===== BUSCAR VENTA =====" << std::endl;
        
        std::cout << "Ingrese ID de la venta: ";
        std::string id;
        std::getline(std::cin, id);
        
        Venta* venta = ventaController.obtenerPorId(id);
        
        if (!venta) {
            Menu::mostrarError("No se encontro la venta");
            return;
        }
        
        venta->mostrar();
        
        Utilidades::pausar();
    }
    
    void cancelarVenta() {
        Utilidades::limpiarPantalla();
        std::cout << "===== CANCELAR VENTA =====" << std::endl;
        
        std::cout << "Ingrese ID de la venta a cancelar: ";
        std::string id;
        std::getline(std::cin, id);
        
        Venta* venta = ventaController.obtenerPorId(id);
        
        if (!venta) {
            Menu::mostrarError("No se encontro la venta");
            return;
        }
        
        std::cout << "\nVenta encontrada:" << std::endl;
        venta->mostrar();
        
        if (!Menu::confirmar("\n¿Esta seguro de que desea cancelar esta venta?")) {
            return;
        }
        
        if (ventaController.cancelar(id)) {
            Menu::mostrarExito("Venta cancelada correctamente");
        } else {
            Menu::mostrarError("No se pudo cancelar la venta");
        }
    }
    
    void verVentasPorCliente() {
        Utilidades::limpiarPantalla();
        std::cout << "===== VENTAS POR CLIENTE =====" << std::endl;
        
        std::cout << "Ingrese ID del cliente: ";
        std::string clienteId;
        std::getline(std::cin, clienteId);
        
        Cliente* cliente = clienteController.obtenerPorId(clienteId);
        if (!cliente) {
            Menu::mostrarError("Cliente no encontrado");
            return;
        }
        
        Lista<Venta> ventas = ventaController.obtenerPorCliente(clienteId);
        
        if (ventas.estaVacia()) {
            Menu::mostrarInfo("No hay ventas registradas para este cliente");
            return;
        }
        
        std::cout << "\nVentas del cliente " << cliente->getNombreCompleto() << ":" << std::endl;
        mostrarTablaVentas(ventas);
        
        Utilidades::pausar();
    }
    
    void verVentasPorEmpleado() {
        Utilidades::limpiarPantalla();
        std::cout << "===== VENTAS POR EMPLEADO =====" << std::endl;
        
        std::cout << "Ingrese ID del empleado: ";
        std::string empleadoId;
        std::getline(std::cin, empleadoId);
        
        Empleado* empleado = empleadoController.obtenerPorId(empleadoId);
        if (!empleado) {
            Menu::mostrarError("Empleado no encontrado");
            return;
        }
        
        Lista<Venta> ventas = ventaController.obtenerPorEmpleado(empleadoId);
        
        if (ventas.estaVacia()) {
            Menu::mostrarInfo("No hay ventas registradas para este empleado");
            return;
        }
        
        std::cout << "\nVentas del empleado " << empleado->getNombreCompleto() << ":" << std::endl;
        mostrarTablaVentas(ventas);
        
        Utilidades::pausar();
    }
    
    void verVentasPorMetodoPago() {
        Utilidades::limpiarPantalla();
        std::cout << "===== VENTAS POR METODO DE PAGO =====" << std::endl;
        
        Menu menuMetodoPago("Seleccione el metodo de pago");
        menuMetodoPago.agregarOpcion("Efectivo");
        menuMetodoPago.agregarOpcion("Tarjeta");
        menuMetodoPago.agregarOpcion("Volver");
        
        int opcion = menuMetodoPago.mostrar();
        
        std::string metodoPago;
        switch (opcion) {
            case 1:
                metodoPago = "efectivo";
                break;
            case 2:
                metodoPago = "tarjeta";
                break;
            default:
                return;
        }
        
        Lista<Venta> ventas = ventaController.obtenerPorMetodoPago(metodoPago);
        
        if (ventas.estaVacia()) {
            Menu::mostrarInfo("No hay ventas registradas con este metodo de pago");
            return;
        }
        
        std::cout << "\nVentas con metodo de pago '" << metodoPago << "':" << std::endl;
        mostrarTablaVentas(ventas);
        
        Utilidades::pausar();
    }

    void mostrarMenuCliente(const std::string& clienteId) {
        bool salir = false;

        while (!salir) {
            Menu menu("PROCESO DE COMPRA");
            menu.agregarOpcion("Ver carrito actual");
            menu.agregarOpcion("Agregar producto al carrito");
            menu.agregarOpcion("Eliminar producto del carrito");
            menu.agregarOpcion("Actualizar cantidad de producto");
            menu.agregarOpcion("Finalizar compra");
            menu.agregarOpcion("Volver al menu principal");

            int opcion = menu.mostrar();

            Carrito* carrito = carritoController.obtenerCarritoActivoCliente(clienteId);
            if (!carrito && opcion != 6) {
                carrito = carritoController.crear(clienteId);
            }

            switch (opcion) {
            case 1:
                if (carrito) {
                    verCarrito(carrito);
                }
                break;
            case 2:
                if (carrito) {
                    agregarProductoCarrito(carrito);
                }
                break;
            case 3:
                if (carrito) {
                    eliminarProductoCarrito(carrito);
                }
                break;
            case 4:
                if (carrito) {
                    actualizarCantidadCarrito(carrito);
                }
                break;
            case 5:
                if (carrito && procesarVenta(carrito)) {
                    Menu::mostrarExito("Compra realizada con exito");
                    salir = true;
                }
                break;
            case 6:
                salir = true;
                break;
            }
        }
    }
    
private:
    void agregarProductoCarrito(Carrito* carrito) {
        std::cout << "\nIngrese ID del producto: ";
        std::string productoId;
        std::getline(std::cin, productoId);
        
        std::cout << "Ingrese cantidad: ";
        std::string cantidadStr;
        std::getline(std::cin, cantidadStr);
        
        int cantidad;
        try {
            cantidad = std::stoi(cantidadStr);
            if (cantidad <= 0) {
                throw std::invalid_argument("La cantidad debe ser mayor que cero");
            }
        } catch (...) {
            Menu::mostrarError("Cantidad invalida");
            return;
        }
        
        if (carritoController.agregarProducto(carrito->getId(), productoId, cantidad)) {
            Menu::mostrarExito("Producto agregado al carrito");
        } else {
            Menu::mostrarError("No se pudo agregar el producto");
        }
    }
    
    void eliminarProductoCarrito(Carrito* carrito) {
        std::cout << "\nIngrese ID del producto a eliminar: ";
        std::string productoId;
        std::getline(std::cin, productoId);
        
        if (carritoController.eliminarProducto(carrito->getId(), productoId)) {
            Menu::mostrarExito("Producto eliminado del carrito");
        } else {
            Menu::mostrarError("No se pudo eliminar el producto");
        }
    }
    
    void actualizarCantidadCarrito(Carrito* carrito) {
        std::cout << "\nIngrese ID del producto: ";
        std::string productoId;
        std::getline(std::cin, productoId);
        
        std::cout << "Ingrese nueva cantidad: ";
        std::string cantidadStr;
        std::getline(std::cin, cantidadStr);
        
        int cantidad;
        try {
            cantidad = std::stoi(cantidadStr);
            if (cantidad < 0) {
                throw std::invalid_argument("La cantidad no puede ser negativa");
            }
        } catch (...) {
            Menu::mostrarError("Cantidad invalida");
            return;
        }
        
        if (carritoController.actualizarCantidad(carrito->getId(), productoId, cantidad)) {
            Menu::mostrarExito("Cantidad actualizada");
        } else {
            Menu::mostrarError("No se pudo actualizar la cantidad");
        }
    }
    
    void verCarrito(Carrito* carrito) {
        Utilidades::limpiarPantalla();
        carrito->mostrar();
        Utilidades::pausar();
    }
    
    void aplicarDescuento(Carrito* carrito) {
        std::cout << "\nIngrese porcentaje de descuento: ";
        std::string descuentoStr;
        std::getline(std::cin, descuentoStr);
        
        double descuento;
        try {
            descuento = std::stod(descuentoStr);
            if (descuento < 0 || descuento > 100) {
                throw std::invalid_argument("El descuento debe estar entre 0 y 100");
            }
        } catch (...) {
            Menu::mostrarError("Descuento invalido");
            return;
        }
        
        if (carritoController.aplicarDescuento(carrito->getId(), descuento)) {
            Menu::mostrarExito("Descuento aplicado");
        } else {
            Menu::mostrarError("No se pudo aplicar el descuento");
        }
    }
    
    bool procesarVenta(Carrito* carrito) {
        if (carrito->getCantidadItems() == 0) {
            Menu::mostrarError("El carrito esta vacio");
            return false;
        }
        
        // Solicitar ID del empleado
        std::cout << "\nID del empleado que procesa la venta: ";
        std::string empleadoId;
        std::getline(std::cin, empleadoId);
        
        Empleado* empleado = empleadoController.obtenerPorId(empleadoId);
        if (!empleado) {
            Menu::mostrarError("Empleado no encontrado");
            return false;
        }
        
        // Seleccionar método de pago
        Menu menuPago("METODO DE PAGO");
        menuPago.agregarOpcion("Efectivo");
        menuPago.agregarOpcion("Tarjeta");
        menuPago.agregarOpcion("Cancelar");
        
        int opcion = menuPago.mostrar();
        
        std::string metodoPago;
        switch (opcion) {
            case 1:
                metodoPago = "efectivo";
                break;
            case 2:
                metodoPago = "tarjeta";
                break;
            default:
                return false;
        }
        
        // Finalizar el carrito
        if (!carritoController.finalizar(carrito->getId())) {
            Menu::mostrarError("No se pudo finalizar el carrito");
            return false;
        }
        
        // Crear la venta
        if (!ventaController.crear(*carrito, empleadoId, metodoPago)) {
            Menu::mostrarError("No se pudo procesar la venta");
            return false;
        }
        
        return true;
    }
    
    void mostrarTablaVentas(Lista<Venta>& ventas) {
        std::cout << Utilidades::generarLinea('-', 80) << std::endl;
        std::cout << std::left << std::setw(10) << "ID"
                  << std::left << std::setw(12) << "Fecha"
                  << std::left << std::setw(8) << "Hora"
                  << std::left << std::setw(10) << "Cliente"
                  << std::right << std::setw(12) << "Total"
                  << std::left << std::setw(15) << "Metodo Pago"
                  << std::left << std::setw(10) << "Estado" << std::endl;
        std::cout << Utilidades::generarLinea('-', 80) << std::endl;
        
        auto mostrarVenta = [](const Venta& v) {
            std::cout << v.obtenerFilaTabla() << std::endl;
        };
        
        ventas.forEach(mostrarVenta);
    }
};

#endif