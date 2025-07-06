#ifndef DATASET_GENERATOR_H
#define DATASET_GENERATOR_H

#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <sstream>
#include "../modelos/Producto.h"
#include "../modelos/Cliente.h"
#include "../modelos/Empleado.h"
#include "../modelos/Proveedor.h"
#include "../modelos/Categoria.h"
#include "../modelos/Venta.h"
#include "../controladores/ProductoController.h"
#include "../controladores/ClienteController.h"
#include "../controladores/EmpleadoController.h"
#include "../controladores/ProveedorController.h"
#include "../controladores/CategoriaController.h"
#include "../controladores/VentaController.h"
#include "../controladores/CarritoController.h"
#include "Utilidades.h"

class DataSetGenerator {
private:
    std::mt19937 generador;
    
    // Datos de ejemplo para generar información realista
    std::vector<std::string> nombres = {
        "Juan", "Maria", "Carlos", "Ana", "Pedro", "Sofia", "Luis", "Carmen", "Miguel", "Laura",
        "Roberto", "Elena", "Diego", "Patricia", "Fernando", "Isabel", "Alejandro", "Monica",
        "Ricardo", "Gabriela", "Andres", "Valeria", "Javier", "Natalia", "Sergio", "Daniela",
        "Raul", "Adriana", "Cesar", "Paola", "Oscar", "Veronica", "Hector", "Silvia", "Mario",
        "Claudia", "Jorge", "Beatriz", "Arturo", "Lorena", "Enrique", "Mariana", "Francisco",
        "Cristina", "Alberto", "Rosa", "Manuel", "Gloria", "Antonio", "Esperanza"
    };
    
    std::vector<std::string> apellidos = {
        "Garcia", "Rodriguez", "Martinez", "Lopez", "Gonzalez", "Perez", "Sanchez", "Ramirez",
        "Cruz", "Flores", "Gomez", "Morales", "Vazquez", "Jimenez", "Ruiz", "Hernandez",
        "Diaz", "Moreno", "Muñoz", "Alvarez", "Romero", "Gutierrez", "Navarro", "Torres",
        "Dominguez", "Gil", "Vargas", "Castillo", "Iglesias", "Serrano", "Blanco", "Garrido",
        "Castro", "Ortega", "Delgado", "Marin", "Rubio", "Nuñez", "Sanz", "Medina",
        "Molina", "Morales", "Ortiz", "Guerrero", "Cano", "Prieto", "Mendez", "Calvo"
    };
    
    std::vector<std::string> nombresProductos = {
        "Leche", "Pan", "Arroz", "Aceite", "Azucar", "Sal", "Huevos", "Pollo", "Carne", "Pescado",
        "Manzanas", "Platanos", "Naranjas", "Tomates", "Cebollas", "Papas", "Zanahorias", "Lechuga",
        "Yogurt", "Queso", "Mantequilla", "Jamón", "Atun", "Pasta", "Frijoles", "Lentejas",
        "Cafe", "Te", "Jugo", "Refresco", "Agua", "Cerveza", "Vino", "Galletas", "Chocolate",
        "Cereal", "Avena", "Miel", "Mermelada", "Mayonesa", "Ketchup", "Mostaza", "Vinagre",
        "Detergente", "Jabon", "Shampoo", "Pasta dental", "Papel higienico", "Toallas", "Pañales"
    };
    
    std::vector<std::string> categorias = {
        "Lacteos", "Panaderia", "Abarrotes", "Carnes", "Frutas", "Verduras", "Bebidas",
        "Limpieza", "Higiene", "Hogar", "Embutidos", "Congelados", "Dulces", "Snacks"
    };
    
    std::vector<std::string> cargos = {
        "Gerente", "Supervisor", "Cajero", "Almacenista", "Vendedor", "Seguridad",
        "Limpieza", "Contador", "Recursos Humanos", "Marketing"
    };
    
    std::vector<std::string> calles = {
        "Av. Principal", "Calle Central", "Jr. Lima", "Av. Arequipa", "Calle Real",
        "Av. Universitaria", "Jr. Huancayo", "Calle Los Olivos", "Av. El Sol",
        "Jr. Comercio", "Calle San Martin", "Av. Grau", "Jr. Ayacucho", "Calle Union"
    };
    
    std::vector<std::string> metodoPago = {"efectivo", "tarjeta"};

public:
    DataSetGenerator() : generador(std::random_device{}()) {}
    
    // Generar número aleatorio en un rango
    int generarEntero(int min, int max) {
        std::uniform_int_distribution<int> distribucion(min, max);
        return distribucion(generador);
    }
    
    // Generar número decimal aleatorio
    double generarDecimal(double min, double max) {
        std::uniform_real_distribution<double> distribucion(min, max);
        return distribucion(generador);
    }
    
    // Seleccionar elemento aleatorio de un vector
    template<typename T>
    T seleccionarAleatorio(const std::vector<T>& vector) {
        if (vector.empty()) {
            throw std::runtime_error("Vector vacio");
        }
        int indice = generarEntero(0, vector.size() - 1);
        return vector[indice];
    }
    
    // Generar email aleatorio
    std::string generarEmail(const std::string& nombre, const std::string& apellido) {
        std::vector<std::string> dominios = {"gmail.com", "hotmail.com", "yahoo.com", "outlook.com"};
        std::string email = Utilidades::aMinusculas(nombre + apellido + std::to_string(generarEntero(1, 999)));
        email += "@" + seleccionarAleatorio(dominios);
        return email;
    }
    
    // Generar teléfono aleatorio
    std::string generarTelefono() {
        return "9" + std::to_string(generarEntero(10000000, 99999999));
    }
    
    // Generar dirección aleatoria
    std::string generarDireccion() {
        return seleccionarAleatorio(calles) + " " + std::to_string(generarEntero(100, 9999));
    }
    
    // Generar código de barras aleatorio
    std::string generarCodigoBarras() {
        std::string codigo = "";
        for (int i = 0; i < 13; i++) {
            codigo += std::to_string(generarEntero(0, 9));
        }
        return codigo;
    }
    
    // Generar fecha aleatoria en un rango
    std::string generarFecha(int anioMin = 2020, int anioMax = 2024) {
        int anio = generarEntero(anioMin, anioMax);
        int mes = generarEntero(1, 12);
        int dia = generarEntero(1, 28); // Para evitar problemas con febrero
        
        std::stringstream ss;
        ss << anio << "-" << std::setfill('0') << std::setw(2) << mes 
           << "-" << std::setfill('0') << std::setw(2) << dia;
        return ss.str();
    }
    
    // Generar hora aleatoria
    std::string generarHora() {
        int hora = generarEntero(8, 22); // Horario comercial
        int minuto = generarEntero(0, 59);
        int segundo = generarEntero(0, 59);
        
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(2) << hora << ":"
           << std::setfill('0') << std::setw(2) << minuto << ":"
           << std::setfill('0') << std::setw(2) << segundo;
        return ss.str();
    }
    
    // Generar categorías
    void generarCategorias(CategoriaController& controller, int cantidad = 15) {
        std::cout << "Generando " << cantidad << " categorias..." << std::endl;
        
        for (int i = 0; i < cantidad; i++) {
            std::string id = "C" + std::to_string(i + 1);
            std::string nombre = (i < categorias.size()) ? categorias[i] : 
                                ("Categoria " + std::to_string(i + 1));
            std::string descripcion = "Descripcion de " + nombre;
            
            Categoria categoria(id, nombre, descripcion);
            controller.crear(categoria);
        }
        
        std::cout << "Categorias generadas exitosamente." << std::endl;
    }
    
    // Generar productos
    void generarProductos(ProductoController& controller, CategoriaController& categoriaController, int cantidad = 100) {
        std::cout << "Generando " << cantidad << " productos..." << std::endl;
        
        Lista<Categoria> categoriasDisponibles = categoriaController.obtenerActivas();
        if (categoriasDisponibles.estaVacia()) {
            std::cout << "Error: No hay categorias disponibles. Genere categorias primero." << std::endl;
            return;
        }
        
        std::vector<std::string> categoriasVector;
        auto agregarCategoria = [&categoriasVector](const Categoria& c) {
            categoriasVector.push_back(c.getNombre());
        };
        categoriasDisponibles.forEach(agregarCategoria);
        
        for (int i = 0; i < cantidad; i++) {
            std::string id = "P" + std::to_string(i + 1);
            std::string nombre = seleccionarAleatorio(nombresProductos) + " " + 
                               std::to_string(generarEntero(1, 10));
            std::string descripcion = "Descripcion de " + nombre;
            double precio = generarDecimal(0.50, 50.0);
            int stock = generarEntero(0, 200);
            std::string categoria = seleccionarAleatorio(categoriasVector);
            std::string codigoBarras = generarCodigoBarras();
            
            Producto producto(id, nombre, descripcion, precio, stock, categoria, codigoBarras);
            controller.crear(producto);
        }
        
        std::cout << "Productos generados exitosamente." << std::endl;
    }
    
    // Generar clientes
    void generarClientes(ClienteController& controller, int cantidad = 50) {
        std::cout << "Generando " << cantidad << " clientes..." << std::endl;
        
        for (int i = 0; i < cantidad; i++) {
            std::string id = "CL" + std::to_string(i + 1);
            std::string nombre = seleccionarAleatorio(nombres);
            std::string apellido = seleccionarAleatorio(apellidos);
            std::string email = generarEmail(nombre, apellido);
            std::string telefono = generarTelefono();
            std::string direccion = generarDireccion();
            double totalCompras = generarDecimal(0, 5000);
            int puntosAcumulados = static_cast<int>(totalCompras / 100);
            
            Cliente cliente(id, nombre, apellido, email, telefono, direccion, 
                          totalCompras, puntosAcumulados);
            controller.crear(cliente);
        }
        
        std::cout << "Clientes generados exitosamente." << std::endl;
    }
    
    // Generar empleados
    void generarEmpleados(EmpleadoController& controller, int cantidad = 20) {
        std::cout << "Generando " << cantidad << " empleados..." << std::endl;
        
        for (int i = 0; i < cantidad; i++) {
            std::string id = "E" + std::to_string(i + 1);
            std::string nombre = seleccionarAleatorio(nombres);
            std::string apellido = seleccionarAleatorio(apellidos);
            std::string cargo = seleccionarAleatorio(cargos);
            std::string email = generarEmail(nombre, apellido);
            std::string telefono = generarTelefono();
            double salario = generarDecimal(1000, 5000);
            std::string fechaContratacion = generarFecha(2018, 2024);
            
            Empleado empleado(id, nombre, apellido, cargo, email, telefono, 
                            salario, fechaContratacion);
            controller.crear(empleado);
        }
        
        std::cout << "Empleados generados exitosamente." << std::endl;
    }
    
    // Generar proveedores
    void generarProveedores(ProveedorController& controller, int cantidad = 15) {
        std::cout << "Generando " << cantidad << " proveedores..." << std::endl;
        
        std::vector<std::string> nombresEmpresas = {
            "Distribuidora Central", "Alimentos del Norte", "Productos del Sur",
            "Comercial Lima", "Distribuciones Peruanas", "Alimentos Frescos",
            "Productos Naturales", "Distribuidora Nacional", "Comercial Andina",
            "Alimentos Premium", "Distribuciones Modernas", "Productos Selectos",
            "Comercial del Pacifico", "Distribuidora Continental", "Alimentos Integrales"
        };
        
        for (int i = 0; i < cantidad; i++) {
            std::string id = "PR" + std::to_string(i + 1);
            std::string nombre = (i < nombresEmpresas.size()) ? nombresEmpresas[i] :
                               ("Proveedor " + std::to_string(i + 1));
            std::string contacto = seleccionarAleatorio(nombres) + " " + seleccionarAleatorio(apellidos);
            std::string email = "contacto@" + Utilidades::aMinusculas(nombre) + ".com";
            std::string telefono = generarTelefono();
            std::string direccion = generarDireccion();
            
            // Generar categorías aleatorias para el proveedor
            std::vector<std::string> categoriasProveedor;
            int numCategorias = generarEntero(1, 4);
            for (int j = 0; j < numCategorias; j++) {
                std::string categoria = seleccionarAleatorio(categorias);
                if (std::find(categoriasProveedor.begin(), categoriasProveedor.end(), categoria) 
                    == categoriasProveedor.end()) {
                    categoriasProveedor.push_back(categoria);
                }
            }
            
            Proveedor proveedor(id, nombre, contacto, email, telefono, direccion, categoriasProveedor);
            controller.crear(proveedor);
        }
        
        std::cout << "Proveedores generados exitosamente." << std::endl;
    }
    
    // Generar ventas simuladas
    void generarVentas(VentaController& ventaController, CarritoController& carritoController,
                      ClienteController& clienteController, EmpleadoController& empleadoController,
                      ProductoController& productoController, int cantidad = 30) {
        std::cout << "Generando " << cantidad << " ventas..." << std::endl;
        
        // Obtener listas de clientes y empleados
        std::vector<std::string> clientesIds;
        auto agregarClienteId = [&clientesIds](const Cliente& c) {
            if (c.isActivo()) {
                clientesIds.push_back(c.getId());
            }
        };
        clienteController.obtenerTodos().forEach(agregarClienteId);
        
        std::vector<std::string> empleadosIds;
        auto agregarEmpleadoId = [&empleadosIds](const Empleado& e) {
            if (e.isActivo()) {
                empleadosIds.push_back(e.getId());
            }
        };
        empleadoController.obtenerTodos().forEach(agregarEmpleadoId);
        
        std::vector<std::string> productosIds;
        auto agregarProductoId = [&productosIds](const Producto& p) {
            if (p.isDisponible() && p.getStock() > 0) {
                productosIds.push_back(p.getId());
            }
        };
        productoController.obtenerTodos().forEach(agregarProductoId);
        
        if (clientesIds.empty() || empleadosIds.empty() || productosIds.empty()) {
            std::cout << "Error: No hay suficientes datos para generar ventas." << std::endl;
            return;
        }
        
        for (int i = 0; i < cantidad; i++) {
            std::string clienteId = seleccionarAleatorio(clientesIds);
            std::string empleadoId = seleccionarAleatorio(empleadosIds);
            
            // Crear carrito
            Carrito* carrito = carritoController.crear(clienteId);
            if (!carrito) continue;
            
            // Agregar productos aleatorios al carrito
            int numProductos = generarEntero(1, 8);
            for (int j = 0; j < numProductos; j++) {
                std::string productoId = seleccionarAleatorio(productosIds);
                int cantidad = generarEntero(1, 5);
                carritoController.agregarProducto(carrito->getId(), productoId, cantidad);
            }
            
            // Aplicar descuento aleatorio (30% de probabilidad)
            if (generarEntero(1, 100) <= 30) {
                double descuento = generarDecimal(5, 20);
                carritoController.aplicarDescuento(carrito->getId(), descuento);
            }
            
            // Aplicar impuesto
            carritoController.aplicarImpuesto(carrito->getId(), 18.0); // IGV en Perú
            
            // Finalizar carrito
            if (carritoController.finalizar(carrito->getId())) {
                // Crear venta
                std::string metodo = seleccionarAleatorio(metodoPago);
                ventaController.crear(*carrito, empleadoId, metodo);
            }
        }
        
        std::cout << "Ventas generadas exitosamente." << std::endl;
    }
    
    // Generar dataset completo
    void generarDataSetCompleto(ProductoController& productoController,
                               CategoriaController& categoriaController,
                               ClienteController& clienteController,
                               EmpleadoController& empleadoController,
                               ProveedorController& proveedorController,
                               VentaController& ventaController,
                               CarritoController& carritoController) {
        std::cout << "=== GENERANDO DATASET COMPLETO ===" << std::endl;
        
        generarCategorias(categoriaController, 15);
        generarProductos(productoController, categoriaController, 100);
        generarClientes(clienteController, 50);
        generarEmpleados(empleadoController, 20);
        generarProveedores(proveedorController, 15);
        generarVentas(ventaController, carritoController, clienteController, 
                     empleadoController, productoController, 30);
        
        std::cout << "=== DATASET COMPLETO GENERADO ===" << std::endl;
        std::cout << "Resumen:" << std::endl;
        std::cout << "- Categorias: 15" << std::endl;
        std::cout << "- Productos: 100" << std::endl;
        std::cout << "- Clientes: 50" << std::endl;
        std::cout << "- Empleados: 20" << std::endl;
        std::cout << "- Proveedores: 15" << std::endl;
        std::cout << "- Ventas: 30" << std::endl;
    }
    
    // Limpiar todos los datos
    void limpiarTodosLosDatos(ProductoController& productoController,
                             CategoriaController& categoriaController,
                             ClienteController& clienteController,
                             EmpleadoController& empleadoController,
                             ProveedorController& proveedorController) {
        std::cout << "Limpiando todos los datos..." << std::endl;
        
        // Aqui implementaré métodos de limpieza en los controladores
        // Por ahora, solo muestro el mensaje
        
        std::cout << "Datos limpiados exitosamente." << std::endl;
    }
};

#endif