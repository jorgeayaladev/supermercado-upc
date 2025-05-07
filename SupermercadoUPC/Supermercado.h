#ifndef SUPERMERCADO_H
#define SUPERMERCADO_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
#include "Lista.h"
#include "Cliente.h"
#include "Administrador.h"

template <typename S, typename F>
class Supermercado {
private:
    Lista<Cliente<S, F>> clientes;
    Lista<Administrador<S, F>> administradores;

public:
    Supermercado() {
		this->cargarUsuarios({ "clientes.txt", "administradores.txt" });
    }
    ~Supermercado() {}

    // Métodos para cargar datos por defecto
    void cargarUsuarios(vector<S> archivos);

    // Métodos para mostrar datos
    void mostrarUsuarios(S tipo);

	// Métodos para agregar datos
	/*
	void agregarAlFichero(S archivoPath, vector<S> datos) {
		ofstream archivo(archivoPath, ios::app);
		if (!archivo.is_open()) {
			cerr << "Error al abrir el archivo: " << archivoPath << endl;
			return;
		}
		// Si no está vacío, salto de linea primero
		if (archivo.tellp() != 0) archivo << "\n";
		// Concatenar los datos con "|"
		for (int i = 0; i < datos.size(); ++i) {
			if (i != 0) archivo << "|";
			archivo << datos[i];
		}
		archivo.close();
	}
	*/

	// Métodos para registrar usuarios
	void registrarCliente() {
		// Implementar el registro de un nuevo cliente
		string username, password, dni, nombre, email, telefono, direccion, fechaNacimiento, imagen, idCliente;

		// Validar Nombre
		bool vNombre = false;
		regex patronNombre("^[a-zA-Z ]{3,}$");
		do {
			cout << "Ingrese su nombre: "; getline(cin, nombre);
			if (!regex_match(nombre, patronNombre))
				cout << "Nombre invalido. Debe tener al menos 3 letras sin tildes." << endl;
			else vNombre = true;
		} while (!vNombre);
		
        // Validar DNI
		bool vDni = false;
        regex patronDni("^[0-9]{8}$");
        do {
			cout << "Ingrese su DNI: "; getline(cin, dni);
            if (!regex_match(dni, patronDni))
                cout << "DNI invalido. Debe tener exactamente 8 digitos numericos." << endl;
			else if (
                clientes.contiene([dni](const Cliente<S, F>& cliente) { return cliente.getDni() == dni; }) ||
				administradores.contiene([dni](const Administrador<S, F>& admin) { return admin.getDni() == dni; })
                )
				cout << "DNI invalido. Ya esta registrado en el sistema." << endl;
			else vDni = true;
		} while (!vDni);

		// Validar email
		bool vEmail = false;
		regex patronEmail("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
		do {
			cout << "Ingrese su email: "; getline(cin, email);
			if (!regex_match(email, patronEmail))
				cout << "Email invalido. Formato correcto: (ej. ejemplo123@gmail.com)" << endl;
			else if (
				clientes.contiene([email](const Cliente<S, F>& cliente) { return cliente.getEmail() == email; }) ||
				administradores.contiene([email](const Administrador<S, F>& admin) { return admin.getEmail() == email; })
				)
				cout << "Email invalido. Ya esta registrado en el sistema." << endl;
			else vEmail = true;
		} while (!vEmail);

		// Validar telefono
		bool vTelefono = false;
		regex patronTelefono("^[0-9]{9}$");
		do {
			cout << "Ingrese su telefono: "; getline(cin, telefono);
			if (!regex_match(telefono, patronTelefono))
				cout << "Telefono invalido. Debe tener exactamente 9 digitos numericos." << endl;
			else if (
				clientes.contiene([telefono](const Cliente<S, F>& cliente) { return cliente.getTelefono() == telefono; }) ||
				administradores.contiene([telefono](const Administrador<S, F>& admin) { return admin.getTelefono() == telefono; })
				)
				cout << "Telefono invalido. Ya esta registrado en el sistema." << endl;
			else vTelefono = true;
		} while (!vTelefono);

		cout << "Ingrese su direccion: "; getline(cin, direccion);

		// Validar fecha de nacimiento (DD-MM-AAAA)
		bool vFecha = false;
		regex patronFecha("^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-[0-9]{4}$");
		do {
			cout << "Ingrese su fecha de nacimiento (DD-MM-AAAA): "; getline(cin, fechaNacimiento);
			if (!regex_match(fechaNacimiento, patronFecha))
				cout << "Fecha invalida. Formato correcto: (ej. 02-09-1939)" << endl;
			else vFecha = true;
		} while (!vFecha);

		username = nombre.substr(0, 1) + dni;
		password = "@" + nombre.substr(0, 3) + dni.substr(0, 3);
		imagen = username + ".png";
		idCliente = "C00" + to_string(clientes.getTamanio() + 1);

		Cliente<S, F> cliente(username, password, dni, nombre, email, telefono, direccion, fechaNacimiento, imagen, "", idCliente);
		clientes.agregar(cliente);
		/*
		vector<S> datos = {
			cliente.getUsername(), cliente.getPassword(), cliente.getDni(), cliente.getNombre(),
			cliente.getEmail(), cliente.getTelefono(), cliente.getDireccion(), cliente.getFechaNacimiento(),
			cliente.getImagen(), cliente.getFechaRegistro(), cliente.getIdCliente(),
			cliente.getTipoCliente(), cliente.getMetodoPago(), to_string(cliente.getPuntosCMR()),
			to_string(cliente.getLimiteCredito())
		};
		*/
	}
};

// Métodos para cargar datos por defecto
template <typename S, typename F>
void Supermercado<S, F>::cargarUsuarios(vector<S> archivos) {
	for (const auto& archivo : archivos) {
        ifstream file(archivo);
        string linea;

        while (getline(file, linea)) {
            stringstream ss(linea);
            string username, password, dni, nombre, email, telefono, direccion, fechaNacimiento, imagen;
            getline(ss, username, '|');
            getline(ss, password, '|');
            getline(ss, dni, '|');
            getline(ss, nombre, '|');
            getline(ss, email, '|');
            getline(ss, telefono, '|');
            getline(ss, direccion, '|');
            getline(ss, fechaNacimiento, '|');
			getline(ss, imagen, '|');

			// Dependiendo del archivo, se cargan diferentes atributos
			if (archivo == "clientes.txt") {
				string idCliente, tipoCliente, metodoPago;
				float puntosCMR, limiteCredito;
				getline(ss, idCliente, '|');
				getline(ss, tipoCliente, '|');
				getline(ss, metodoPago, '|');
				ss >> puntosCMR;
				ss.ignore();
				ss >> limiteCredito;
				Cliente<S, F> cliente(
					username, password, dni, nombre, email, telefono, direccion,
					fechaNacimiento, imagen, "", idCliente, tipoCliente,
					metodoPago, puntosCMR, limiteCredito
				);
				clientes.agregar(cliente);
			}
            else if (archivo == "administradores.txt") {
                string idAdmin, nivelAcceso, departamento, horario;
                float salario;
                getline(ss, idAdmin, '|');
                getline(ss, nivelAcceso, '|');
                getline(ss, departamento, '|');
                getline(ss, horario, '|');
                ss >> salario;
                Administrador<S, F> admin(
                    username, password, dni, nombre, email,
                    telefono, direccion, fechaNacimiento,
                    imagen, "", idAdmin, nivelAcceso,
                    departamento, horario, salario
                );
                administradores.agregar(admin);
            }
        }
	}
}

// Métodos para agregar datos

// Métodos para mostrar datos
template <typename S, typename F>
void Supermercado<S, F>::mostrarUsuarios(S tipo) {
    if (tipo == "C")
        clientes.mostrar([](const Cliente<S, F>& cliente) { cout << cliente << endl; });
    else if (tipo == "A")
        administradores.mostrar([](const Administrador<S, F>& admin) { cout << admin << endl; });
    else cout << "Tipo de usuario no válido." << endl;
}

// Métodos para buscar datos

#endif // SUPERMERCADO_H