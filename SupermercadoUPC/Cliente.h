#ifndef CLIENTE_H
#define CLIENTE_H

#include "Usuario.h"

template <typename S, typename F>
class Cliente : public Usuario<S> {
private:
    S idCliente;
    S tipoCliente; // "Regular", "Premium", "VIP"
    S metodoPago; // "Efectivo", "Tarjeta", "Yape", "Plin"
	F puntosCMR; // Puntos acumulados en la tarjeta CMR
    F limiteCredito; // Límite de crédito si aplica

public:
    // Constructor
    Cliente(
        const S& username, const S& password, const S& dni, const S& nombre, const S& email, const S& telefono, 
		const S& direccion, const S& fechaNacimiento, const S& imagen, const S& fechaRegistro,
        const S& idCliente, const S& tipoCliente = "Regular", const S& metodoPago = "Efectivo", 
        const F& puntosCMR = 0, const F& limiteCredito = 0
	) : Usuario<S>(username, password, dni, nombre, email, telefono, direccion, fechaNacimiento, imagen, fechaRegistro) {
		this->idCliente = idCliente;
		this->tipoCliente = tipoCliente;
		this->metodoPago = metodoPago;
		this->puntosCMR = puntosCMR;
		this->limiteCredito = limiteCredito;
    }
    ~Cliente() {}

    // Getters
	S getIdCliente() const { return idCliente; }
	S getTipoCliente() const { return tipoCliente; }
	S getMetodoPago() const { return metodoPago; }
	F getPuntosCMR() const { return puntosCMR; }
	F getLimiteCredito() const { return limiteCredito; }

    // Setters
	void setIdCliente(const S& newIdCliente) { idCliente = newIdCliente; }
	void setTipoCliente(const S& newTipoCliente) { tipoCliente = newTipoCliente; }
	void setMetodoPago(const S& newMetodoPago) { metodoPago = newMetodoPago; }
	void setPuntosCMR(const F& newPuntosCMR) { puntosCMR = newPuntosCMR; }
    void setLimiteCredito(const F& newLimiteCredito) { limiteCredito = newLimiteCredito; }
};

// Sobrecarga del operador << para imprimir el objeto Cliente
template <typename S, typename F>
ostream& operator<<(ostream& os, const Cliente<S, F>& cliente) {
    os  << "|| ID: " << cliente.getIdCliente() << "\n"
        << "|| Usuario: " << cliente.getUsername() << "\n"
	    << "|| Contrasena: " << cliente.getPassword() << "\n"
	    << "|| DNI: " << cliente.getDni() << "\n"
        << "|| Nombre: " << cliente.getNombre() << "\n" 
        << "|| Email: " << cliente.getEmail() << "\n"
        << "|| Telefono: " << cliente.getTelefono() << "\n"
		<< "|| Direccion: " << cliente.getDireccion() << "\n"
		<< "|| Fecha de Nacimiento: " << cliente.getFechaNacimiento() << "\n"
		<< "|| Imagen: " << cliente.getImagen() << "\n"
		<< "|| Fecha de Registro: " << cliente.getFechaRegistro() << "\n"
		<< "|| Tipo de Cliente: " << cliente.getTipoCliente() << "\n"
		<< "|| Metodo de Pago: " << cliente.getMetodoPago() << "\n"
		<< "|| Puntos CMR: " << cliente.getPuntosCMR() << "\n"
		<< "|| Limite de Credito: " << cliente.getLimiteCredito() << "\n"
        << "|| ========================================== ||";
    return os;
}

#endif // CLIENTE_H