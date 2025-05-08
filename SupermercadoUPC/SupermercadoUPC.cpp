#include <iostream>
#include <string>
#include <windows.h>

#include "Supermercado.h"

using namespace std;

Supermercado<string, float> supermercado;

void static regresando(int tiempo) {
	cout << "|| Opcion invalida, regresando en ";
	for (int i = tiempo; i > 0; i--) {
		cout << i << " ";
		Sleep(1000);
	}
	cout << endl;
}

// Falta
void static menuIniciarSesion() {
	string usuario;
	system("cls");
	cout << "||=================================================||" << endl;
	cout << "|| INICIAR SESION:                                 ||" << endl;
	cout << "||-------------------------------------------------||" << endl;
	cout << "|| Ingrese sus credenciales:                       ||" << endl;
	cout << "||-------------------------------------------------||" << endl;
	usuario = supermercado.iniciarSesion();
	cout << "||-------------------------------------------------||" << endl;
	switch (usuario[0]) {
	case 'A': 
		cout << "Hola administrador: " << usuario << endl;
		system("pause>0");
		break;
	case 'C': 
		cout << "Hola cliente: " << usuario << endl;
		system("pause>0");
		break;
	default: 
		cout << "Hola desconocido: " << usuario << endl;
		system("pause>0");
		break;
	}
	cout << "||=================================================||" << endl;
}

// Listo
void static menuCrearCuenta() {
	int opcion;
	do {
		system("cls");
		cout << "||=================================================||" << endl;
		cout << "|| CREAR UNA NUEVA CUENTA:                         ||" << endl;
		cout << "||-------------------------------------------------||" << endl;
		cout << "|| Que desea hacer?                                ||" << endl;
		cout << "||-------------------------------------------------||" << endl;
		cout << "|| 1) Crear cuenta como cliente                    ||" << endl;
		cout << "|| 2) Volver al menu principal                     ||" << endl;
		cout << "||=================================================||" << endl;
		cout << "|| Ingrese su opcion: "; cin >> opcion; cin.ignore();
		switch (opcion) {
		case 1: 
			cout << "||=================================================||" << endl;
			supermercado.crearCuentaCliente(); 
			cout << "||=================================================||" << endl;
			cout << "|| Cuenta creada exitosamente :D !                 ||" << endl;
			cout << "||=================================================||" << endl;
			regresando(3);
			break;
		case 2: return;
		default:
			cout << "||=================================================||" << endl;
			regresando(3);
			break;
		}
	} while (opcion != 3);
}

// Falta
void static menuExplorarCatalogo() {
	int opcion;
	do {
		system("cls");
		cout << "||=================================================||" << endl;
		cout << "|| CATALOGO DE PRODUCTOS:                          ||" << endl;
		cout << "||-------------------------------------------------||" << endl;
		cout << "|| Que desea hacer?                                ||" << endl;
		cout << "||-------------------------------------------------||" << endl;
		cout << "|| 1) Ver productos por categoria                  ||" << endl;
		cout << "|| 2) Buscar productos por nombre                  ||" << endl;
		cout << "|| 3) Volver al menu principal                     ||" << endl;
		cout << "||=================================================||" << endl;
		cout << "|| Ingrese su opcion: "; cin >> opcion; cin.ignore();
		switch (opcion) {
		case 1: break; // Implementar ver productos por categoria
		case 2: break; // Implementar buscar productos por nombre
		case 3: return; // Volver al menu principal
		default:
			break;
		}
	} while (opcion != 4);
}

// Listo
void static menuPrincipal() {
	int opcion;
	do {
		system("cls");
		cout << "||=================================================||" << endl;
		cout << "||========= BIENVENIDO A SUPERMERCADO UPC =========||" << endl;
		cout << "||=================================================||" << endl;
		cout << "|| Que desea hacer?                                ||" << endl;
		cout << "||-------------------------------------------------||" << endl;
		cout << "|| 1) Iniciar sesion                               ||" << endl;
		cout << "|| 2) Crearme una nueva cuenta como cliente        ||" << endl;
		cout << "|| 3) Explorar el catalogo de productos            ||" << endl;
		cout << "|| 4) Salir                                        ||" << endl;
		cout << "||=================================================||" << endl;
		cout << "|| Ingrese su opcion: "; cin >> opcion; cin.ignore();

		switch (opcion) {
		case 1: menuIniciarSesion(); break;
		case 2: menuCrearCuenta(); break;
		case 3: menuExplorarCatalogo(); break;
		case 4:
			cout << "||=================================================||" << endl;
			cout << "||               Saliendo en 3, 2, 1               ||" << endl;
			cout << "||=================================================||" << endl;
			Sleep(2000);
			cout << "||                  Hasta luego!                   ||" << endl;
			cout << "||=================================================||" << endl;
			Sleep(2000);
			return;
		default:
			cout << "||=================================================||" << endl;
			regresando(3);
			break;
		}
	} while (opcion != 4);
}

int main() {
	menuPrincipal();

    return 0;
}

/*
cout << "|| ========================================== ||" << endl;
cout << "||               ADMINISTRADORES              ||" << endl;
cout << "|| ========================================== ||" << endl;
supermercado.mostrarUsuarios("A");
cout << endl;

cout << "|| ========================================== ||" << endl;
cout << "||                  CLIENTES                  ||" << endl;
cout << "|| ========================================== ||" << endl;
supermercado.mostrarUsuarios("C");
cout << endl;

supermercado.crearCuentaCliente();
cout << endl;
*/