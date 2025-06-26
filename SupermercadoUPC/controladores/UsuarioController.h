#ifndef USUARIO_CONTROLLER_H
#define USUARIO_CONTROLLER_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "../modelos/Usuario.h"
#include "../estructuras/Lista.h"
#include "../utilidades/Utilidades.h"

class UsuarioController {
private:
    Lista<Usuario> usuarios;
    Usuario* usuarioActual;
    const std::string archivoUsuarios = "datos/usuarios.txt";

public:
    UsuarioController() : usuarioActual(nullptr) {
        cargarUsuarios();
    }

    bool login(const std::string& username, const std::string& password) {
        auto buscarUsuario = [&username, &password](const Usuario& u) {
            return u.getUsername() == username && u.getPassword() == password && u.isActivo();
        };

        Usuario* usuario = usuarios.buscar(buscarUsuario);

        if (usuario) {
            usuarioActual = usuario;
            return true;
        }

        return false;
    }

    void logout() {
        usuarioActual = nullptr;
    }

    bool esAdministrador() const {
        return usuarioActual && usuarioActual->getRol() == "administrador";
    }

    bool esCliente() const {
        return usuarioActual && usuarioActual->getRol() == "cliente";
    }

    Usuario* getUsuarioActual() const {
        return usuarioActual;
    }

    void cargarUsuarios() {
        std::ifstream archivo(archivoUsuarios);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo de usuarios. Se creará uno nuevo al guardar." << std::endl;
            generarUsuariosEjemplo();
            return;
        }

        std::string linea;
        while (std::getline(archivo, linea)) {
            if (!linea.empty()) {
                Usuario usuario = Usuario::desdeCSV(linea);
                usuarios.insertarFinal(usuario);
            }
        }

        archivo.close();
    }

    void guardarUsuarios() {
        system("mkdir -p datos");

        std::ofstream archivo(archivoUsuarios);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para guardar los usuarios." << std::endl;
            return;
        }

        auto guardarUsuario = [&archivo](const Usuario& u) {
            archivo << u.aCSV() << std::endl;
        };

        usuarios.forEach(guardarUsuario);

        archivo.close();
    }

private:
    void generarUsuariosEjemplo() {
        usuarios.insertarFinal(Usuario("E001", "admin", "admin123", "administrador"));
        usuarios.insertarFinal(Usuario("CL001", "cliente1", "cliente123", "cliente"));
        usuarios.insertarFinal(Usuario("CL002", "cliente2", "cliente234", "cliente"));
        usuarios.insertarFinal(Usuario("CL003", "cliente3", "cliente345", "cliente"));
        usuarios.insertarFinal(Usuario("CL004", "cliente4", "cliente456", "cliente"));
        usuarios.insertarFinal(Usuario("CL005", "cliente5", "cliente567", "cliente"));

        guardarUsuarios();
    }
};

#endif