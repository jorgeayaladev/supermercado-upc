#ifndef LOGIN_VISTA_H
#define LOGIN_VISTA_H

#include <string>
#include <iostream>
#include "../controladores/UsuarioController.h"
#include "../utilidades/Utilidades.h"
#include "Menu.h"

class LoginVista {
private:
    UsuarioController& usuarioController;

public:
    LoginVista(UsuarioController& _usuarioController)
        : usuarioController(_usuarioController) {
    }

    bool mostrarLogin() {
        Utilidades::limpiarPantalla();
        std::cout << "\033[1;36m";
        std::cout << "|| ================================================ ||" << std::endl;
        std::cout << "||                  INICIAR SESION                  ||" << std::endl;
        std::cout << "|| ================================================ ||" << std::endl;

        std::string username, password;

        std::cout << "|| Usuario: ";
        std::getline(std::cin, username);

        if (username.empty()) {
            Menu::mostrarError("El usuario no puede estar vacio.");
            return false;
        }

        std::cout << "|| Contrasena: ";
        std::getline(std::cin, password);

        std::cout << "|| ================================================ ||" << std::endl;
        std::cout << "\033[0m";

        if (password.empty()) {
            Menu::mostrarError("La contrasena no puede estar vacia.");
            return false;
        }

        if (usuarioController.login(username, password)) {
            Menu::mostrarExito("Inicio de sesion exitoso!");
            return true;
        }
        else {
            Menu::mostrarError("Usuario o contrasena incorrectos!");
            return false;
        }
    }
};

#endif