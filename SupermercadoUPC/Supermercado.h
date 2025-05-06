#ifndef SUPERMERCADO_H
#define SUPERMERCADO_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "Lista.h"
#include "Cliente.h"
#include "Administrador.h"

template <typename S, typename F>
class Supermercado {
private:
    Lista<Administrador<S, F>> administradores;
    Lista<Cliente<S, F>> clientes;

public:
    void cargarClientes(const string& archivo) {
        ifstream file(archivo);
        string linea;
        while (getline(file, linea)) {
            stringstream ss(linea);
            S username, password, dni, nombre, email, telefono, direccion, fechaNacimiento, imagen, idCliente, tipoCliente, metodoPago;
            F puntosCMR, limiteCredito;
            getline(ss, username, '|');
            getline(ss, password, '|');
            getline(ss, dni, '|');
            getline(ss, nombre, '|');
            getline(ss, email, '|');
            getline(ss, telefono, '|');
            getline(ss, direccion, '|');
            getline(ss, fechaNacimiento, '|');
            getline(ss, imagen, '|');
            getline(ss, idCliente, '|');
            getline(ss, tipoCliente, '|');
            getline(ss, metodoPago, '|');
            ss >> puntosCMR;
            ss.ignore();
            ss >> limiteCredito;

            Cliente<S, F> cliente(username, password, dni, nombre, email, telefono, direccion,
                fechaNacimiento, imagen, "", idCliente, tipoCliente, metodoPago, puntosCMR, limiteCredito);
            clientes.agregarFinal(cliente);
        }
    }

    void cargarAdministradores(const string& archivo) {
        ifstream file(archivo);
        string linea;
        while (getline(file, linea)) {
            stringstream ss(linea);
            S username, password, dni, nombre, email, telefono, direccion, fechaNacimiento, imagen, idAdmin, nivelAcceso, departamento, horario;
            F salario;
            getline(ss, username, '|');
            getline(ss, password, '|');
            getline(ss, dni, '|');
            getline(ss, nombre, '|');
            getline(ss, email, '|');
            getline(ss, telefono, '|');
            getline(ss, direccion, '|');
            getline(ss, fechaNacimiento, '|');
            getline(ss, imagen, '|');
            getline(ss, idAdmin, '|');
            getline(ss, nivelAcceso, '|');
            getline(ss, departamento, '|');
            getline(ss, horario, '|');
            ss >> salario;

            Administrador<S, F> admin(username, password, dni, nombre, email, telefono, direccion,
				fechaNacimiento, imagen, "", idAdmin, nivelAcceso, departamento, horario, salario);
            administradores.agregarFinal(admin);
        }
    }

    void mostrarClientes() const {
        clientes.mostrar();
    }

    void mostrarAdministradores() const {
		administradores.mostrar();
    }
};

#endif // SUPERMERCADO_H