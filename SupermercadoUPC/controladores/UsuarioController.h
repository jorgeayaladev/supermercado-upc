#ifndef USUARIO_CONTROLLER_H
#define USUARIO_CONTROLLER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "../modelos/Usuario.h"
#include "../estructuras/Lista.h"
#include "../utilidades/Utilidades.h"

class UsuarioController {
private:
    Lista<Usuario> usuarios;
    const std::string archivoUsuarios = "datos/usuarios.txt";
    Usuario* usuarioActual;

public:
    UsuarioController() : usuarioActual(nullptr) {
        cargarUsuarios();
    }

    bool login(const std::string& username, const std::string& password) {
        auto buscarUsuario = [&username, &password](const Usuario& u) {
            return u.getUsername() == username &&
                u.getPassword() == password &&
                u.isActivo();
            };

        usuarioActual = usuarios.buscar(buscarUsuario);
        return usuarioActual != nullptr;
    }

    void logout() {
        usuarioActual = nullptr;
    }

    Usuario* getUsuarioActual() const {
        return usuarioActual;
    }

    bool esAdministrador() const {
        return usuarioActual && usuarioActual->getRol() == "administrador";
    }

    bool esCliente() const {
        return usuarioActual && usuarioActual->getRol() == "cliente";
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
        usuarios.insertarFinal(Usuario("U001", "admin", "admin123", "administrador"));
        usuarios.insertarFinal(Usuario("U002", "cliente1", "cliente123", "cliente"));
        usuarios.insertarFinal(Usuario("U003", "cliente2", "cliente456", "cliente"));

        guardarUsuarios();
    }
};

#endif