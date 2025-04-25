#pragma once

// Clase Nodo para la lista enlazada simple
template <typename T>
class Nodo {
private:
	// Propiedades o atributos
	T dato;
	Nodo<T>* siguiente;

public:
	// Constructor
	Nodo(T valor) : dato(valor), siguiente(nullptr) {}

	// Getters y setters
	T getDato() const { return dato; }
	void setDato(T valor) { dato = valor; }
	Nodo<T>* getSiguiente() const { return siguiente; }
	void setSiguiente(Nodo<T>* nodo) { siguiente = nodo; }
};