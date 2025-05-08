#ifndef SUPERMERCADO_H
#define SUPERMERCADO_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
#include <ctime>
#include "Lista.h"
#include "Cliente.h"
#include "Administrador.h"

template <typename S, typename F>
class Supermercado {
private:
	// Usuario activo
	Cliente<string, float> clienteActivo;
	Administrador<string, float> adminActivo;
	// Listas de usuarios
    Lista<Cliente<S, F>> clientes;
    Lista<Administrador<S, F>> administradores;

public:
	Supermercado() {
		// Cargar datos por defecto
		this->cargarUsuarios({ "clientes.txt", "administradores.txt" });
    }
    ~Supermercado() {}

	// Getters
	Cliente<S, F> getClienteActivo() { return clienteActivo; }
	Administrador<S, F> getAdminActivo() { return adminActivo; }
	Lista<Cliente<S, F>> getClientes() { return clientes; }
	Lista<Administrador<S, F>> getAdministradores() { return administradores; }
	// Setters
	void setClienteActivo(Cliente<S, F> cliente) { clienteActivo = cliente; }
	void setAdminActivo(Administrador<S, F> admin) { adminActivo = admin; }

    // Métodos para cargar datos por defecto
    void cargarUsuarios(vector<S> archivos);

	// Métodos de vista general
	S iniciarSesion();
	void crearCuentaCliente();
	void modificarCuentaUsuario(S tipoUsuario);

    // Métodos para mostrar datos
    void mostrarUsuarios(S tipo);

	// Métodos CRUD de datos al fichero
	void agregarAlFichero(S archivoPath, vector<S> datos);

	// Otros métodos
	string obtenerFechaHoraActual();
};

// Métodos para cargar datos por defecto
template <typename S, typename F>
void Supermercado<S, F>::cargarUsuarios(vector<S> archivos) {
	for (const auto& archivo : archivos) {
        ifstream file(archivo);
        string linea;

        while (getline(file, linea)) {
            stringstream ss(linea);
            string username, password, dni, nombre, email, telefono, direccion, fechaNacimiento, imagen, fechaRegistro;
            getline(ss, username, '|');
            getline(ss, password, '|');
            getline(ss, dni, '|');
            getline(ss, nombre, '|');
            getline(ss, email, '|');
            getline(ss, telefono, '|');
            getline(ss, direccion, '|');
            getline(ss, fechaNacimiento, '|');
			getline(ss, imagen, '|');
			getline(ss, fechaRegistro, '|');

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
					username, password, dni, nombre, email, telefono, 
					direccion, fechaNacimiento, imagen, fechaRegistro, 
					idCliente, tipoCliente, metodoPago, puntosCMR, limiteCredito
				);
				clientes.agregar(cliente);
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
                    username, password, dni, nombre, email, telefono,
					direccion, fechaNacimiento, imagen, fechaRegistro, 
					idAdmin, nivelAcceso, departamento, horario, salario
                );
                administradores.agregar(admin);
            }
        }
	}
}

// Métodos CRUD de datos al fichero
template <typename S, typename F>
void Supermercado<S, F>::agregarAlFichero(S archivoPath, vector<S> datos) {
	ofstream archivo(archivoPath, ios::app);
	if (!archivo.is_open()) {
		cerr << "Error al abrir el archivo: " << archivoPath << endl;
		return;
	}

	archivo << "\n";
	// Concatenar los datos con "|"
	for (int i = 0; i < datos.size(); ++i) {
		if (i != 0) archivo << "|";
		archivo << datos[i];
	}
	archivo.close();
}
// Falta para modificar una linea de dato en el fichero

// Métodos para mostrar datos
template <typename S, typename F>
void Supermercado<S, F>::mostrarUsuarios(S tipo) {
    if (tipo == "C")
        clientes.mostrar([](const Cliente<S, F>& cliente) { cout << cliente << endl; });
    else if (tipo == "A")
        administradores.mostrar([](const Administrador<S, F>& admin) { cout << admin << endl; });
    else cout << "Tipo de usuario no válido." << endl;
}


// Inicio de sesión
template <typename S, typename F>
S Supermercado<S, F>::iniciarSesion() {
	string username, password;
	cout << "|| Username: "; getline(cin, username);
	cout << "|| Password: "; getline(cin, password);

	auto administrador = administradores.buscar([username, password](const Administrador<S, F>& admin) {
		return (admin.getUsername() == username && admin.getPassword() == password);
		});
	// Si el administrador existe, se obtiene su ID
	if (administrador != nullptr) {
		this->adminActivo = *administrador;
		return administrador->getIdAdministrador(); 
	}

	auto cliente = clientes.buscar([username, password](const Cliente<S, F>& cliente) {
		return (cliente.getUsername() == username && cliente.getPassword() == password);
		});
	// Si el cliente existe, se obtiene su ID
	if (cliente != nullptr) { 
		this->clienteActivo = *cliente;
		return cliente->getIdCliente(); 
	}

	return "No encontrado";
}
template <typename S, typename F>
void Supermercado<S, F>::crearCuentaCliente() {
	// Implementar el registro de un nuevo cliente
	string username, password, dni, nombre, email, telefono, direccion, fechaNacimiento, imagen, idCliente;

	// Validar Nombre
	bool vNombre = false;
	regex patronNombre("^[a-zA-Z ]{3,}$");
	do {
		cout << "|| Ingrese su nombre: "; getline(cin, nombre);
		if (!regex_match(nombre, patronNombre))
			cout << "|| Nombre invalido. Debe tener al menos 3 letras sin tildes." << endl;
		else vNombre = true;
	} while (!vNombre);

	// Validar DNI
	bool vDni = false;
	regex patronDni("^[0-9]{8}$");
	do {
		cout << "|| Ingrese su DNI: "; getline(cin, dni);
		if (!regex_match(dni, patronDni))
			cout << "|| DNI invalido. Debe tener exactamente 8 digitos numericos." << endl;
		else if (
			clientes.contiene([dni](const Cliente<S, F>& cliente) { return cliente.getDni() == dni; }) ||
			administradores.contiene([dni](const Administrador<S, F>& admin) { return admin.getDni() == dni; })
			)
			cout << "|| DNI invalido. Ya esta registrado en el sistema." << endl;
		else vDni = true;
	} while (!vDni);

	// Validar email
	bool vEmail = false;
	regex patronEmail("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
	do {
		cout << "|| Ingrese su email: "; getline(cin, email);
		if (!regex_match(email, patronEmail))
			cout << "Email invalido. Formato correcto: (ej. ejemplo123@gmail.com)" << endl;
		else if (
			clientes.contiene([email](const Cliente<S, F>& cliente) { return cliente.getEmail() == email; }) ||
			administradores.contiene([email](const Administrador<S, F>& admin) { return admin.getEmail() == email; })
			)
			cout << "|| Email invalido. Ya esta registrado en el sistema." << endl;
		else vEmail = true;
	} while (!vEmail);

	// Validar telefono
	bool vTelefono = false;
	regex patronTelefono("^[0-9]{9}$");
	do {
		cout << "|| Ingrese su telefono: "; getline(cin, telefono);
		if (!regex_match(telefono, patronTelefono))
			cout << "Telefono invalido. Debe tener exactamente 9 digitos numericos." << endl;
		else if (
			clientes.contiene([telefono](const Cliente<S, F>& cliente) { return cliente.getTelefono() == telefono; }) ||
			administradores.contiene([telefono](const Administrador<S, F>& admin) { return admin.getTelefono() == telefono; })
			)
			cout << "|| Telefono invalido. Ya esta registrado en el sistema." << endl;
		else vTelefono = true;
	} while (!vTelefono);

	cout << "|| Ingrese su direccion: "; getline(cin, direccion);

	// Validar fecha de nacimiento (DD-MM-AAAA)
	bool vFecha = false;
	regex patronFecha("^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-[0-9]{4}$");
	do {
		cout << "|| Ingrese su fecha de nacimiento (DD-MM-AAAA): "; getline(cin, fechaNacimiento);
		if (!regex_match(fechaNacimiento, patronFecha))
			cout << "|| Fecha invalida. Formato correcto: (ej. 02-09-1939)" << endl;
		else vFecha = true;
	} while (!vFecha);

	username = nombre.substr(0, 1) + dni;
	password = "@" + nombre.substr(0, 3) + dni.substr(0, 3);
	imagen = username + ".png";
	idCliente = "C00" + to_string(clientes.getTamanio() + 1);

	Cliente<S, F> cliente(username, password, dni, nombre, email, telefono, direccion, fechaNacimiento, imagen, obtenerFechaHoraActual(), idCliente);
	clientes.agregar(cliente);
	agregarAlFichero("clientes.txt", {
		cliente.getUsername(), cliente.getPassword(), cliente.getDni(), cliente.getNombre(),
		cliente.getEmail(), cliente.getTelefono(), cliente.getDireccion(), cliente.getFechaNacimiento(),
		cliente.getImagen(), cliente.getFechaRegistro(), cliente.getIdCliente(),
		cliente.getTipoCliente(), cliente.getMetodoPago(), to_string(cliente.getPuntosCMR()),
		to_string(cliente.getLimiteCredito())
		});
}
template <typename S, typename F>
void Supermercado<S, F>::modificarCuentaUsuario(S tipoUsuario) {
	int opcion;
	string password, nombre, email, telefono, direccion, fechaNacimiento, imagen;
	// Validaciones
	bool vPassword = false, vNombre = false, vEmail = false, vTelefono = false, vFecha = false;
	regex patronPassword("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}$");
	regex patronNombre("^[a-zA-Z ]{3,}$");
	regex patronEmail("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
	regex patronTelefono("^[0-9]{9}$");
	regex patronFecha("^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-[0-9]{4}$");

	// Implementar la modificación de la cuenta de un usuario
	std::cout << "||=================================================||" << std::endl;
	std::cout << "|| MODIFICANDO MI PERFIL:                          ||" << std::endl;
	std::cout << "||=================================================||" << std::endl;
	std::cout << "|| Que atributo de su perfil desea cambiar?        ||" << std::endl;
	std::cout << "||-------------------------------------------------||" << std::endl;
	std::cout << "|| (1) Modificar mi password                       ||" << std::endl;
	std::cout << "|| (2) Modificar mi nombre                         ||" << std::endl;
	std::cout << "|| (3) Modificar mi email                          ||" << std::endl;
	std::cout << "|| (4) Modificar mi telefono                       ||" << std::endl;
	std::cout << "|| (5) Modificar mi direccion                      ||" << std::endl;
	std::cout << "|| (6) Modificar mi fecha de nacimiento            ||" << std::endl;
	std::cout << "|| (7) Modificar mi imagen                         ||" << std::endl;
	std::cout << "||-------------------------------------------------||" << std::endl;
	std::cout << "|| Ingrese su opcion: "; cin >> opcion; cin.ignore();
	std::cout << "||-------------------------------------------------||" << std::endl;
	switch (opcion) {
	case 1:
		do {
			cout << "|| Ingrese su nueva password: "; getline(cin, password);
			if (!regex_match(password, patronPassword))
				cout << "|| Password invalida. Debe tener al menos 8 caracteres, una mayuscula y un numero." << endl;
			else vPassword = true;
		} while (!vPassword);
		switch (tipoUsuario[0]) {
		case 'A':
			this->adminActivo.setPassword(password);
			administradores.modificar([](const Administrador<S, F>& admin) { return true; }, adminActivo); break;
		case 'C':
			this->clienteActivo.setPassword(password);
			clientes.modificar([](const Cliente<S, F>& cliente) { return true; }, clienteActivo); break;
		}
		break;
	case 2:
		do {
			cout << "|| Ingrese su nuevo nombre: "; getline(cin, nombre);
			if (!regex_match(nombre, patronNombre))
				cout << "|| Nombre invalido. Debe tener al menos 3 letras sin tildes." << endl;
			else vNombre = true;
		} while (!vNombre);
		switch (tipoUsuario[0]) {
		case 'A':
			this->adminActivo.setNombre(nombre);
			administradores.modificar([](const Administrador<S, F>& admin) { return true; }, adminActivo); break;
		case 'C':
			this->clienteActivo.setNombre(nombre);
			clientes.modificar([](const Cliente<S, F>& cliente) { return true; }, clienteActivo); break;
		}
		break;
	case 3:
		do {
			cout << "|| Ingrese su email: "; getline(cin, email);
			if (!regex_match(email, patronEmail))
				cout << "Email invalido. Formato correcto: (ej. ejemplo123@gmail.com)" << endl;
			else if (
				clientes.contiene([email](const Cliente<S, F>& cliente) { return cliente.getEmail() == email; }) ||
				administradores.contiene([email](const Administrador<S, F>& admin) { return admin.getEmail() == email; })
				)
				cout << "|| Email invalido. Ya esta registrado en el sistema." << endl;
			else vEmail = true;
		} while (!vEmail);
		switch (tipoUsuario[0]) {
		case 'A':
			this->adminActivo.setEmail(email);
			administradores.modificar([](const Administrador<S, F>& admin) { return true; }, adminActivo); break;
		case 'C':
			this->clienteActivo.setEmail(email);
			clientes.modificar([](const Cliente<S, F>& cliente) { return true; }, clienteActivo); break;
		}
		break;
	case 4:
		do {
			cout << "|| Ingrese su telefono: "; getline(cin, telefono);
			if (!regex_match(telefono, patronTelefono))
				cout << "Telefono invalido. Debe tener exactamente 9 digitos numericos." << endl;
			else if (
				clientes.contiene([telefono](const Cliente<S, F>& cliente) { return cliente.getTelefono() == telefono; }) ||
				administradores.contiene([telefono](const Administrador<S, F>& admin) { return admin.getTelefono() == telefono; })
				)
				cout << "|| Telefono invalido. Ya esta registrado en el sistema." << endl;
			else vTelefono = true;
		} while (!vTelefono);
		switch (tipoUsuario[0]) {
		case 'A':
			this->adminActivo.setTelefono(telefono);
			administradores.modificar([](const Administrador<S, F>& admin) { return true; }, adminActivo); break;
		case 'C':
			this->clienteActivo.setTelefono(telefono);
			clientes.modificar([](const Cliente<S, F>& cliente) { return true; }, clienteActivo); break;
		}
		break;
	case 5:
		cout << "|| Ingrese su nueva direccion: "; getline(cin, direccion);
		switch (tipoUsuario[0]) {
		case 'A':
			this->adminActivo.setDireccion(direccion);
			administradores.modificar([](const Administrador<S, F>& admin) { return true; }, adminActivo); break;
		case 'C':
			this->clienteActivo.setDireccion(direccion);
			clientes.modificar([](const Cliente<S, F>& cliente) { return true; }, clienteActivo); break;
		}
		break;
	case 6:
		do {
			cout << "|| Ingrese su nueva fecha de nacimiento (DD-MM-AAAA): "; getline(cin, fechaNacimiento);
			if (!regex_match(fechaNacimiento, patronFecha))
				cout << "|| Fecha invalida. Formato correcto: (ej. 02-09-1939)" << endl;
			else vFecha = true;
		} while (!vFecha);
		switch (tipoUsuario[0]) {
		case 'A':
			this->adminActivo.setFechaNacimiento(fechaNacimiento);
			administradores.modificar([](const Administrador<S, F>& admin) { return true; }, adminActivo); break;
		case 'C':
			this->clienteActivo.setFechaNacimiento(fechaNacimiento);
			clientes.modificar([](const Cliente<S, F>& cliente) { return true; }, clienteActivo); break;
		}
		break;
	case 7:
		cout << "|| Ingrese su nueva imagen: "; getline(cin, imagen);
		switch (tipoUsuario[0]) {
		case 'A':
			this->adminActivo.setImagen(imagen);
			administradores.modificar([](const Administrador<S, F>& admin) { return true; }, adminActivo); break;
		case 'C':
			this->clienteActivo.setImagen(imagen);
			clientes.modificar([](const Cliente<S, F>& cliente) { return true; }, clienteActivo); break;
		}
		break;
	default:
		std::cout << "||=================================================||" << std::endl;
		std::cout << "|| Opcion invalida..." << std::endl;
		return;
		break;
	}
}

// Otros métodos
template <typename S, typename F>
string Supermercado<S, F>::obtenerFechaHoraActual() {
	time_t ahora = time(nullptr);
	struct tm tiempoStruct;
	char buffer[80];
	localtime_s(&tiempoStruct, &ahora);
	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &tiempoStruct);
	return string(buffer);
}

#endif // SUPERMERCADO_H