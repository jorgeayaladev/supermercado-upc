#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <iostream>
#include <iomanip>
#include "Usuario.h"

using namespace std;

template <typename S, typename F>
class Administrador : public Usuario<S> {
private:
    S idAdministrador;
    S departamento; // Ej: "Recursos Humanos", "Finanzas"
    S nivelAcceso; // Ej: "alto", "medio", "bajo"
    S horario; // Ej: "Mañana", "Tarde", "Noche"
    F salario;

public:
    // Constructor
    Administrador(
        const S& username, const S& password, const S& dni, const S& nombre, const S& email, const S& telefono, 
        const S& direccion, const S& fechaNacimiento, const S& imagen, const S& fechaRegistro,
        const S& idAdministrador, const S& nivelAcceso, const S& departamento, const S& horario, const F& salario
    ) : Usuario<S>(username, password, dni, nombre, email, telefono, direccion, fechaNacimiento, imagen, fechaRegistro) {
        this->idAdministrador = idAdministrador;
		this->departamento = departamento;
		this->nivelAcceso = nivelAcceso;
        this->horario = horario;
        this->salario = salario;
    }
    ~Administrador() {}

    // Getters
    S getIdAdministrador() const { return idAdministrador; }
    S getDepartamento() const { return departamento; }
    S getNivelAcceso() const { return nivelAcceso; }
    S getHorario() const { return horario; }
    F getSalario() const { return salario; }

    // Setters
    void setIdAdministrador(const S& newIdAdministrador) { idAdministrador = newIdAdministrador; }
    void setDepartamento(const S& newDepartamento) { departamento = newDepartamento; }
    void setNivelAcceso(const S& newNivelAcceso) { nivelAcceso = newNivelAcceso; }
    void setHorario(const S& newHorario) { horario = newHorario; }
    void setSalario(const F& newSalario) { salario = newSalario; }
};

// Sobrecarga del operador << para imprimir el objeto Administrador
/*
template <typename S, typename F>
ostream& operator<<(ostream& os, const Administrador<S, F>& admin) {
	os  << "|| ID: " << admin.getIdAdministrador() << "\n"
		<< "|| Usuario: " << admin.getUsername() << "\n"
		<< "|| Contrasena: " << admin.getPassword() << "\n"
		<< "|| DNI: " << admin.getDni() << "\n"
		<< "|| Nombre: " << admin.getNombre() << "\n"
		<< "|| Email: " << admin.getEmail() << "\n"
		<< "|| Telefono: " << admin.getTelefono() << "\n"
		<< "|| Direccion: " << admin.getDireccion() << "\n"
		<< "|| Fecha de Nacimiento: " << admin.getFechaNacimiento() << "\n"
		<< "|| Imagen: " << admin.getImagen() << "\n"
		<< "|| Fecha de Registro: " << admin.getFechaRegistro() << "\n"
		<< "|| Departamento: " << admin.getDepartamento() << "\n"
		<< "|| Nivel de Acceso: " << admin.getNivelAcceso() << "\n"
		<< "|| Horario: " << admin.getHorario() << "\n"
		<< "|| Salario: S/." << admin.getSalario() << "\n"
        << "|| ========================================== ||";
    return os;
}*/
template <typename S, typename F>
ostream& operator<<(ostream& os, const Administrador<S, F>& admin) {
	os  << "|| ID: " << admin.getIdAdministrador() << "\n"
		<< "|| Usuario: " << admin.getUsername() << "\n"
		<< "|| Contrasena: " << admin.getPassword() << "\n"
		<< "|| DNI: " << admin.getDni() << "\n"
		<< "|| Nombre: " << admin.getNombre() << "\n"
		<< "|| Email: " << admin.getEmail() << "\n"
		<< "|| Telefono: " << admin.getTelefono() << "\n"
		<< "|| Direccion: " << admin.getDireccion() << "\n"
		<< "|| Fecha de Nacimiento: " << admin.getFechaNacimiento() << "\n"
		<< "|| Imagen: " << admin.getImagen() << "\n"
		<< "|| Fecha de Registro: " << admin.getFechaRegistro() << "\n"
		<< "|| Departamento: " << admin.getDepartamento() << "\n"
		<< "|| Nivel de Acceso: " << admin.getNivelAcceso() << "\n"
		<< "|| Horario: " << admin.getHorario() << "\n"
		<< "|| Salario: S/." << admin.getSalario() << "\n"
        << "|| ========================================== ||";
    return os;
}

#endif // ADMINISTRADOR_H