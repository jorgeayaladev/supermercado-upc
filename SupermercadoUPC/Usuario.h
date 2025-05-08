#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

template <typename S>
class Usuario {
private:
	S username;
	S password;
	S dni;
	S nombre;
	S email;
	S telefono;
	S direccion;
	S fechaNacimiento; // Fecha de nacimiento
	S imagen; // URL de la imagen del usuario
	S fechaRegistro; // Fecha de registro como usuario

public:
    // Constructor
	Usuario(const S& username, const S& password, const S& dni, const S& nombre, const S& email,
		const S& telefono, const S& direccion, const S& fechaNacimiento, const S& imagen,
		const S& fechaRegistro) {
		this->username = username;
		this->password = password;
		this->dni = dni;
		this->nombre = nombre;
		this->email = email;
		this->telefono = telefono;
		this->direccion = direccion;
		this->fechaNacimiento = fechaNacimiento;
		this->imagen = imagen;
		this->fechaRegistro = fechaRegistro;
	}
    ~Usuario() {}

    // Getters
    S getUsername() const { return username; }
    S getPassword() const { return password; }
	S getDni() const { return dni; }
	S getNombre() const { return nombre; }
	S getEmail() const { return email; }
	S getTelefono() const { return telefono; }
	S getDireccion() const { return direccion; }
	S getFechaNacimiento() const { return fechaNacimiento; }
	S getImagen() const { return imagen; }
	S getFechaRegistro() const { return fechaRegistro; }

    // Setters
	void setUsername(const S& newUsername) { username = newUsername; }
    void setPassword(const S& newPassword) { password = newPassword; }
	void setDni(const S& newDni) { dni = newDni; }
	void setNombre(const S& newNombre) { nombre = newNombre; }
	void setEmail(const S& newEmail) { email = newEmail; }
	void setTelefono(const S& newTelefono) { telefono = newTelefono; }
	void setDireccion(const S& newDireccion) { direccion = newDireccion; }
	void setFechaNacimiento(const S& newFechaNacimiento) { fechaNacimiento = newFechaNacimiento; }
	void setImagen(const S& newImagen) { imagen = newImagen; }
	void setFechaRegistro(const S& newFechaRegistro) { fechaRegistro = newFechaRegistro; }
};

#endif // USUARIO_H