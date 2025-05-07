#include <iostream>

#include "Supermercado.h"

using namespace std;

// Hola Erick :D, en este avance he implementado la clase Supermercado con las dos listas tanto 
// de administradores como de clientes, además de los métodos para cargar los datos desde 
// archivos y mostrarlos en consola.
// He usado la clase Cliente que me dejaste para agregarle los atributos adicionales a esa clase :D
// El día miercoles vamos a presentar nuestro avance al profesor de 4pm a 6pm.
// el día de mañana continuaré con el avance de las demás clases faltantes.

int main() {
    Supermercado<string, float> supermercado;

    cout << "|| ========================================== ||" << endl;
    cout << "||               ADMINISTRADORES              ||" << endl;
    cout << "|| ========================================== ||" << endl;
    supermercado.mostrarUsuarios("A");
    cout << endl;

    cout << "|| ========================================== ||" << endl;
    cout << "||                  CLIENTES                  ||" << endl;
    cout << "|| ========================================== ||" << endl;
    supermercado.mostrarUsuarios("C");
    cout << endl;

	supermercado.registrarCliente();
    cout << endl;

    supermercado.mostrarUsuarios("C");

    return 0;
}
