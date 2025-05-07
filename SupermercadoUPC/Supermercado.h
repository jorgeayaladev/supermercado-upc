#ifndef SUPERMERCADO_H
#define SUPERMERCADO_H

#include <iostream>
#include <fstream>
#include <sstream>
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

    // Métodos de carga de datos por defecto
    void cargarUsuarios(vector<S> archivos);

	// Métodos para registrar usuarios
	void registrarCliente() {
		// Implementar el registro de un nuevo cliente
	}

	// Métodos para mostrar los datos
    void mostrarClientes() const { clientes.mostrar(); }
    void mostrarAdministradores() const { administradores.mostrar(); }
};

// Métodos de carga de datos por defecto
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
				clientes.agregarFinal(cliente);
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
                administradores.agregarFinal(admin);
            }
        }
	}
}

#endif // SUPERMERCADO_H