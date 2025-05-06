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
	Cliente(){
	this->nombre = "";
	this->apellido = "";
	this->codigoCliente = "";
	this->CMR = "";
	}
	Cliente(T nombre, T apellido, T codigoCLiente, T CMR);
	~Cliente(){}
	//Set
	void setNombre(T pnombre);
	void setApellido(T papellido);
	void setCodigoCliente(T pcodigoCliente);
	void setCMR(T pCMR);
	//GET
	T getNombre();
	T getApellido();
	T getCodigoCliente();
	T getCMR();

	//Metodos para el clientes
	void MostrarCLiente() {
		cout << endl;
		cout << "-----------DATOS DEL CLIENTE-----------" << endl;
		cout << "Nombre: " << this->nombre << endl;
		cout << "Apellido: " << this->apellido << endl;
		cout << "Codigo de Cliente: " << this->codigoCliente << endl;
		cout << "Tiene tarjeta CMR (S:si o N:no): " << this->CMR << endl;
		cout << endl;
	}
};

//Implementacion
template<typename T>
Cliente<T>::Cliente(T nombre, T apellido, T codigoCLiente, T CMR) {
	this->nombre = pnombre;
	this->apellido = papellido;
	this->codigoCLiente = pcodigoCliente;
	this->CMR= pCMR;
}
//MetodosSETTER/GETTER
//SET
template<typename T>
void Cliente<T>::setNombre(T pnombre);
template<typename T>
void Cliente<T>::setApellido(T papellido);
template<typename T>
void Cliente<T>::setCodigoCliente(T pcodigoCLiente);
template<typename T>
void Cliente<T>::setCMR(T pCMR);
//XXXXXXXXXXXXXXXXXXXXXXXXXXX--Luego lo termino, ya comenzará mi siguiente clase:c, masomenos tenia planeado hacer el del cliente porque creo que seria
//buena idea implementar si esque el cliente cuenta con tarjeta CMR para descuento en algunos productos. Ya que estamos haciendo sobre Tottus :D
//y el codigo del cliente, como si se tratase del DNI, Cambiare eso del Codigo del cliente por DNI mejor 
//Más ratito lo termino, espero tengas un buen día y te deseo lo mejor <3