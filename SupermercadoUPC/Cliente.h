#pragma once
#include <iostream>

using namespace std;
template <typename T>
class Cliente{
private: //Atributos o propiedades
	T nombre;
	T apellido;
	T codigoCliente;
	T CMR;
	//Fui a almorzar
public:
	Cliente(){
	this->nombre = "";
	this->apellido = "";
	this->codigoCliente = "";
	this->CMR = "";
	}
	Cliente(T nombre, T apellido, T codigoCLiente, T CMR);
	~Cliente(){}
	//METODOS SETTER Y GETTER
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
		cout << "¿Tiene tarjeta CMR? (S o N): " << this->CMR << endl;
		cout << endl;
	}
};

//Implementacion
template<typename T>
Cliente<T>::Cliente(T pnombre, T papellido, T pcodigoCLiente, T pCMR) {
	this->nombre = pnombre;
	this->apellido = papellido;
	this->codigoCLiente = pcodigoCLiente;
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
//GET
template<typename T>
T Cliente<T>::getNombre() { return this - nombre; }
template<typename T>
T Cliente<T>::getApellido() { return this - apellido; }
template<typename T>
T Cliente<T>::getCodigoCliente() { return this - codigoCliente; }
template<typename T>
T Cliente<T>::getCMR() { return this - CMR; }



//XXXXXXXXXXXXXXXXXXXXXXXXXXX--Luego lo termino, ya comenzará mi siguiente clase:c, masomenos tenia planeado hacer el del cliente porque creo que seria
//buena idea implementar si esque el cliente cuenta con tarjeta CMR para descuento en algunos productos. Ya que estamos haciendo sobre Tottus :D
//y el codigo del cliente, como si se tratase del DNI, Cambiare eso del Codigo del cliente por DNI mejor 
//Más ratito lo termino, espero tengas un buen día y te deseo lo mejor <3