#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo {
private:
	T dato;
	Nodo<T>* siguiente;

public:
	Nodo(const T& dato) : dato(dato), siguiente(nullptr) {}

	void setDato(const T& valor) { dato = valor; }
	T getDato() const { return dato; }

	void setSiguiente(Nodo<T>* nodo) { siguiente = nodo; }
	Nodo<T>* getSiguiente() const { return siguiente; }
};

#endif // NODO_H