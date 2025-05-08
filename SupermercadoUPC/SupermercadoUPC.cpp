#include <iostream>
#include <string>
#include <windows.h>

#include "Supermercado.h"

Supermercado<string, float> supermercado;

// Otros métodos de vista
void static regresionGenerica(string mensaje, int tiempo) {
	std::cout << mensaje;
	for (int i = tiempo; i > 0; i--) {
		std::cout << i << " ";
		Sleep(1000);
	}
	std::cout << std::endl;
}
void static regresando(int tiempo) {
	std::cout << "|| Opcion invalida, regresando en ";
	for (int i = tiempo; i > 0; i--) {
		std::cout << i << " ";
		Sleep(1000);
	}
	std::cout << std::endl;
}

// Acciones de administrador
// 1.1.1. Menu de gestion de usuarios (Falta)
void static menuGestionUsuarios() {
	int opcion;
	do {
		system("cls");
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| MENU DE GESTION DE USUARIOS:                    ||" << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| Que desea hacer?                                ||" << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| 1) Ver todos los usuarios                       ||" << std::endl;
		std::cout << "|| 2) Agregar un nuevo usuario                     ||" << std::endl;
		std::cout << "|| 3) Editar un usuario                            ||" << std::endl;
		std::cout << "|| 4) Eliminar un usuario                          ||" << std::endl;
		std::cout << "|| 5) Volver al menu principal                     ||" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Ingrese su opcion: "; std::cin >> opcion; std::cin.ignore();
		switch (opcion) {
		case 1: break; // Implementar ver todos los usuarios
		case 2: break; // Implementar agregar un nuevo usuario
		case 3: break; // Implementar editar un usuario
		case 4: break; // Implementar eliminar un usuario
		case 5: return; // Volver al menu principal
		default:
			std::cout << "||=================================================||" << std::endl;
			regresando(3);
			break;
		}
	} while (opcion != 6);
}
// 1.1.2. Menu de gestion de productos (Falta)
void static menuGestionProductos() {
	int opcion;
	do {
		system("cls");
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| MENU DE GESTION DE PRODUCTOS:                   ||" << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| Que desea hacer?                                ||" << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| 1) Ver todos los productos                      ||" << std::endl;
		std::cout << "|| 2) Agregar un nuevo producto                    ||" << std::endl;
		std::cout << "|| 3) Editar un producto                           ||" << std::endl;
		std::cout << "|| 4) Eliminar un producto                         ||" << std::endl;
		std::cout << "|| 5) Volver al menu principal                     ||" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Ingrese su opcion: "; std::cin >> opcion; std::cin.ignore();
		switch (opcion) {
		case 1: break; // Implementar ver todos los productos
		case 2: break; // Implementar agregar un nuevo producto
		case 3: break; // Implementar editar un producto
		case 4: break; // Implementar eliminar un producto
		case 5: return; // Volver al menu principal
		default:
			std::cout << "||=================================================||" << std::endl;
			regresando(3);
			break;
		}
	} while (opcion != 6);
}
// 1.1.3. Menu de gestion de pedidos (Falta)
void static menuGestionPedidos() {
	int opcion;
	do {
		system("cls");
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| MENU DE GESTION DE PEDIDOS:                     ||" << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| Que desea hacer?                                ||" << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| 1) Ver todos los pedidos                        ||" << std::endl;
		std::cout << "|| 2) Agregar un nuevo pedido                      ||" << std::endl;
		std::cout << "|| 3) Editar un pedido                             ||" << std::endl;
		std::cout << "|| 4) Eliminar un pedido                           ||" << std::endl;
		std::cout << "|| 5) Volver al menu principal                     ||" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Ingrese su opcion: "; std::cin >> opcion; std::cin.ignore();
		switch (opcion) {
		case 1: break; // Implementar ver todos los pedidos
		case 2: break; // Implementar agregar un nuevo pedido
		case 3: break; // Implementar editar un pedido
		case 4: break; // Implementar eliminar un pedido
		case 5: return; // Volver al menu principal
		default:
			std::cout << "||=================================================||" << std::endl;
			regresando(3);
			break;
		}
	} while (opcion != 6);
}
// 1.1.4. Menu de gestion de proveedores (Falta)
void static menuGestionProveedores() {
	int opcion;
	do {
		system("cls");
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| MENU DE GESTION DE PROVEEDORES:                 ||" << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| Que desea hacer?                                ||" << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| 1) Ver todos los proveedores                    ||" << std::endl;
		std::cout << "|| 2) Agregar un nuevo proveedor                   ||" << std::endl;
		std::cout << "|| 3) Editar un proveedor                          ||" << std::endl;
		std::cout << "|| 4) Eliminar un proveedor                        ||" << std::endl;
		std::cout << "|| 5) Volver al menu principal                     ||" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Ingrese su opcion: "; std::cin >> opcion; std::cin.ignore();
		switch (opcion) {
		case 1: break; // Implementar ver todos los proveedores
		case 2: break; // Implementar agregar un nuevo proveedor
		case 3: break; // Implementar editar un proveedor
		case 4: break; // Implementar eliminar un proveedor
		case 5: return; // Volver al menu principal
		default:
			std::cout << "||=================================================||" << std::endl;
			regresando(3);
			break;
		}
	} while (opcion != 6);
}
// 1.1.5. Menu de gestion de promociones (Falta)
void static menuGestionPromociones() {
	int opcion;
	do {
		system("cls");
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| MENU DE GESTION DE PROMOCIONES:                 ||" << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| Que desea hacer?                                ||" << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| 1) Ver todas las promociones                    ||" << std::endl;
		std::cout << "|| 2) Agregar una nueva promocion                  ||" << std::endl;
		std::cout << "|| 3) Editar una promocion                         ||" << std::endl;
		std::cout << "|| 4) Eliminar una promocion                       ||" << std::endl;
		std::cout << "|| 5) Volver al menu principal                     ||" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Ingrese su opcion: "; std::cin >> opcion; std::cin.ignore();
		switch (opcion) {
		case 1: break; // Implementar ver todas las promociones
		case 2: break; // Implementar agregar una nueva promocion
		case 3: break; // Implementar editar una promocion
		case 4: break; // Implementar eliminar una promocion
		case 5: return; // Volver al menu principal
		default:
			std::cout << "||=================================================||" << std::endl;
			regresando(3);
			break;
		}
	} while (opcion != 6);
}
// 1.1.6. Gestionar perfil de administrador (Falta)
void static gestionarPerfilAdministrador() {
	Administrador<string, float> administrador = supermercado.getAdminActivo();
	int opcion;
	do {
		system("cls");
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| GESTIONANDO MI PERFIL:                          ||" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Que desea hacer?                                ||" << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| 1) Ver mi perfil                                ||" << std::endl;
		std::cout << "|| 2) Modificar mi perfil                          ||" << std::endl;
		std::cout << "|| 3) Regresar al menu principal                   ||" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Ingrese su opcion: "; std::cin >> opcion; std::cin.ignore();
		switch (opcion) {
		case 1:
			system("cls");
			std::cout << "||=================================================||" << std::endl;
			std::cout << "|| MI PERFIL DE ADMINISTRADOR (ID: " << administrador.getIdAdministrador() << ")" << std::endl;
			std::cout << "||=================================================||" << endl;
			std::cout << "|| Usuario: " << administrador.getUsername() << std::endl;
			std::cout << "|| Contrasena: " << administrador.getPassword() << std::endl;
			std::cout << "|| DNI: " << administrador.getDni() << std::endl;
			std::cout << "|| Nombre: " << administrador.getNombre() << std::endl;
			std::cout << "|| Email: " << administrador.getEmail() << std::endl;
			std::cout << "|| Telefono: " << administrador.getTelefono() << std::endl;
			std::cout << "|| Direccion: " << administrador.getDireccion() << std::endl;
			std::cout << "|| Fecha de Nacimiento: " << administrador.getFechaNacimiento() << std::endl;
			std::cout << "|| Imagen: " << administrador.getImagen() << std::endl;
			std::cout << "|| Fecha de Registro: " << administrador.getFechaRegistro() << std::endl;
			std::cout << "|| Departamento: " << administrador.getDepartamento() << std::endl;
			std::cout << "|| Nivel de Acceso: " << administrador.getNivelAcceso() << std::endl;
			std::cout << "|| Horario: " << administrador.getHorario() << std::endl;
			std::cout << "|| Salario: S/." << administrador.getSalario() << std::endl;
			std::cout << "||-------------------------------------------------||" << std::endl;
			std::cout << "|| Desea verlo de manera más interactiva? (S/N): "; char ver; cin >> ver; cin.ignore();
			std::cout << "||=================================================||" << std::endl;
			if (ver == 'S' || ver == 's') {
				std::cout << "|| Interaccion activada." << std::endl;
				std::cout << "||=================================================||" << std::endl;
				regresando(3);
			}
			else {
				std::cout << "|| Interaccion desactivada." << std::endl;
				std::cout << "||=================================================||" << std::endl;
				regresando(3);
			}
			break;
		case 2:
			system("cls");
			supermercado.modificarCuentaUsuario("Administrador");
			std::cout << "||=================================================||" << std::endl;
			std::cout << "|| Cambio realizado exitosamente :D !              ||" << std::endl;
			std::cout << "||=================================================||" << std::endl;
			regresando(3);
			break;
		case 3: return; // Volver al menu principal
		default:
			std::cout << "||=================================================||" << endl;
			regresando(3);
			break;
		}
	} while (opcion != 3);
}

// Acciones de cliente
// 1.1.12. Gestionar perfil de cliente (Falta)
void static gestionarPerfilCliente() {
	Cliente<string, float> cliente = supermercado.getClienteActivo();
	int opcion;
	do {
		system("cls");
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| GESTIONANDO MI PERFIL:                          ||" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Que desea hacer?                                ||" << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| 1) Ver mi perfil                                ||" << std::endl;
		std::cout << "|| 2) Modificar mi perfil                          ||" << std::endl;
		std::cout << "|| 3) Regresar al menu principal                   ||" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Ingrese su opcion: "; std::cin >> opcion; std::cin.ignore();
		switch (opcion) {
		case 1:
			system("cls");
			std::cout << "||=================================================||" << std::endl;
			std::cout << "|| MI PERFIL DE CLIENTE (ID: " << cliente.getIdCliente() << ")" << std::endl;
			std::cout << "||=================================================||" << std::endl;
			std::cout << "|| Usuario: " << cliente.getUsername() << std::endl;
			std::cout << "|| Contrasena: " << cliente.getPassword() << std::endl;
			std::cout << "|| DNI: " << cliente.getDni() << std::endl;
			std::cout << "|| Nombre: " << cliente.getNombre() << std::endl;
			std::cout << "|| Email: " << cliente.getEmail() << std::endl;
			std::cout << "|| Telefono: " << cliente.getTelefono() << std::endl;
			std::cout << "|| Direccion: " << cliente.getDireccion() << std::endl;
			std::cout << "|| Fecha de Nacimiento: " << cliente.getFechaNacimiento() << std::endl;
			std::cout << "|| Tipo de Cliente: " << cliente.getTipoCliente() << std::endl;
			std::cout << "|| Metodo de Pago: " << cliente.getMetodoPago() << std::endl;
			std::cout << "|| Puntos CMR: " << cliente.getPuntosCMR() << std::endl;
			std::cout << "|| Limite de Credito: S/." << cliente.getLimiteCredito() << std::endl;
			std::cout << "|| Imagen: " << cliente.getImagen() << std::endl;
			std::cout << "|| Fecha de Registro: " << cliente.getFechaRegistro() << std::endl;
			std::cout << "||-------------------------------------------------||" << std::endl;
			std::cout << "|| Desea verlo de manera más interactiva? (S/N):"; char ver; cin >> ver; cin.ignore();
			std::cout << "||=================================================||" << std::endl;
			if (ver == 'S' || ver == 's') {
				std::cout << "|| Interaccion activada." << std::endl;
				std::cout << "||=================================================||" << std::endl;
				regresando(3);
			}
			else {
				std::cout << "|| Interaccion desactivada." << std::endl;
				std::cout << "||=================================================||" << std::endl;
				regresando(3);
			}
			break;
		case 2:
			system("cls");
			supermercado.modificarCuentaUsuario("Cliente");
			std::cout << "||=================================================||" << std::endl;
			std::cout << "|| Cambio realizado exitosamente :D !              ||" << std::endl;
			std::cout << "||=================================================||" << std::endl;
			regresando(3);
			break;
		case 3: return; // Volver al menu principal
		default:
			std::cout << "||=================================================||" << endl;
			regresando(3);
			break;
		}
	} while (opcion != 3);
}

// 1.1. Menu iniciar sesión y dashboards (Falta para cliente)
void static dashboardAdministrador() {
	Administrador<string, float> administrador = supermercado.getAdminActivo();
	int opcion;
	do {
		system("cls");
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Hola " << administrador.getNombre() << "..." << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| BIENVENIDO A TU DASHBOARD DE ADMINISTRADOR!     ||" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Que desea hacer?                                ||" << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| 1) Ir al menu de gestion de usuarios            ||" << std::endl;
		std::cout << "|| 2) Ir al menu de gestion de productos           ||" << std::endl;
		std::cout << "|| 3) Ir al menu de gestion de pedidos             ||" << std::endl;
		std::cout << "|| 4) Ir al menu de gestion de proveedores         ||" << std::endl;
		std::cout << "|| 5) Gestionar mi perfil de administrador         ||" << std::endl;
		std::cout << "|| 6) Volver al menu principal                     ||" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Ingrese su opcion: "; std::cin >> opcion; std::cin.ignore();
		switch (opcion) {
		case 1: menuGestionUsuarios(); break;
		case 2: menuGestionProductos(); break;
		case 3: menuGestionPedidos(); break;
		case 4: menuGestionProveedores(); break;
		case 5: gestionarPerfilAdministrador(); break;
		case 6: return; // Volver al menu principal
		default:
			std::cout << "||=================================================||" << std::endl;
			regresando(3);
			break;
		}
	} while (opcion != 6);
}
void static dashboardCliente() {
	Cliente<string, float> cliente = supermercado.getClienteActivo();
	int opcion;
	do {
		system("cls");
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Hola " << cliente.getNombre() << "..." << endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| BIENVENIDO A TU DASHBOARD DE CLIENTE!           ||" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Que desea hacer?                                ||" << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| 1) Ir al catalogo de productos                  ||" << std::endl;
		std::cout << "|| 2) Ir a mi carrito                              ||" << std::endl;
		std::cout << "|| 3) Ver mis de pedidos                           ||" << std::endl;
		std::cout << "|| 4) Ver promociones disponibles                  ||" << std::endl;
		std::cout << "|| 5) Gestionar mi perfil de cliente               ||" << std::endl;
		std::cout << "|| 6) Volver al menu principal                     ||" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Ingrese su opcion: "; std::cin >> opcion; std::cin.ignore();
		switch (opcion) {
		case 1: break; // Implementar ir al catalogo de productos
		case 2: break; // Implementar ir a mi carrito
		case 3: break; // Implementar ver mis de pedidos
		case 4: break; // Implementar ver promociones disponibles
		case 5: gestionarPerfilCliente(); break;
		case 6: return; // Volver al menu principal
		default:
			std::cout << "||=================================================||" << std::endl;
			regresando(3);
			break;
		}
	} while (opcion != 6);
}
void static menuIniciarSesion() {
	string idUsuario;
	system("cls");
	std::cout << "||=================================================||" << std::endl;
	std::cout << "|| INICIAR SESION:                                 ||" << std::endl;
	std::cout << "||-------------------------------------------------||" << std::endl;
	std::cout << "|| Ingrese sus credenciales:                       ||" << std::endl;
	std::cout << "||-------------------------------------------------||" << std::endl;
	idUsuario = supermercado.iniciarSesion();
	std::cout << "||=================================================||" << std::endl;
	switch (idUsuario[0]) {
	case 'A':
		std::cout << "|| Autenticacion exitosa administrador!" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		regresionGenerica("|| Redirigiendo a su dashboard en ", 3);
		dashboardAdministrador();
		break;
	case 'C': 
		std::cout << "|| Autenticacion exitosa cliente!" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		regresionGenerica("|| Redirigiendo a su dashboard en ", 3);
		dashboardCliente();
		break;
	default: 
		std::cout << "|| Credenciales incorrectas!" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		regresando(3);
		break;
	}
	return;
}

// 1.2. Menu crear cuenta (Listo)
void static menuCrearCuenta() {
	int opcion;
	do {
		system("cls");
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| CREAR UNA NUEVA CUENTA:                         ||" << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| Que desea hacer?                                ||" << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| 1) Crear cuenta como cliente                    ||" << std::endl;
		std::cout << "|| 2) Volver al menu principal                     ||" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Ingrese su opcion: "; std::cin >> opcion; std::cin.ignore();
		switch (opcion) {
		case 1: 
			std::cout << "||=================================================||" << std::endl;
			supermercado.crearCuentaCliente(); 
			std::cout << "||=================================================||" << std::endl;
			std::cout << "|| Cuenta creada exitosamente :D !                 ||" << std::endl;
			std::cout << "||=================================================||" << std::endl;
			regresando(3);
			break;
		case 2: return;
		default:
			std::cout << "||=================================================||" << std::endl;
			regresando(3);
			break;
		}
	} while (opcion != 3);
}

// 1.3. Menu explorar catalogo (Falta)
void static menuExplorarCatalogo() {
	int opcion;
	do {
		system("cls");
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| CATALOGO DE PRODUCTOS:                          ||" << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| Que desea hacer?                                ||" << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| 1) Ver productos por categoria                  ||" << std::endl;
		std::cout << "|| 2) Buscar productos por nombre                  ||" << std::endl;
		std::cout << "|| 3) Volver al menu principal                     ||" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Ingrese su opcion: "; std::cin >> opcion; std::cin.ignore();
		switch (opcion) {
		case 1: break; // Implementar ver productos por categoria
		case 2: break; // Implementar buscar productos por nombre
		case 3: return; // Volver al menu principal
		default:
			break;
		}
	} while (opcion != 4);
}

// 1. Menu principal (Listo)
void static menuPrincipal() {
	int opcion;
	do {
		system("cls");
		std::cout << "||=================================================||" << std::endl;
		std::cout << "||========= BIENVENIDO A SUPERMERCADO UPC =========||" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Que desea hacer?                                ||" << std::endl;
		std::cout << "||-------------------------------------------------||" << std::endl;
		std::cout << "|| 1) Iniciar sesion                               ||" << std::endl;
		std::cout << "|| 2) Crearme una nueva cuenta como cliente        ||" << std::endl;
		std::cout << "|| 3) Explorar el catalogo de productos            ||" << std::endl;
		std::cout << "|| 4) Salir                                        ||" << std::endl;
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Ingrese su opcion: "; std::cin >> opcion; std::cin.ignore();

		switch (opcion) {
		case 1: menuIniciarSesion(); break;
		case 2: menuCrearCuenta(); break;
		case 3: menuExplorarCatalogo(); break;
		case 4:
			std::cout << "||=================================================||" << std::endl;
			std::cout << "||               Saliendo en 3, 2, 1               ||" << std::endl;
			std::cout << "||=================================================||" << std::endl;
			Sleep(2000);
			std::cout << "||                  Hasta luego!                   ||" << std::endl;
			std::cout << "||=================================================||" << std::endl;
			Sleep(2000);
			return;
		default:
			std::cout << "||=================================================||" << std::endl;
			regresando(3);
			break;
		}
	} while (opcion != 4);
}

int main() {
	menuPrincipal();

    return 0;
}