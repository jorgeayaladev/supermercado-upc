#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <iostream>
#include <sstream>

class Usuario {
private:
    std::string id;
    std::string username;
    std::string password;
    std::string rol; // "administrador" o "cliente"
    bool activo;

public:
    Usuario() : id(""), username(""), password(""), rol("cliente"), activo(true) {}

    Usuario(std::string _id, std::string _username, std::string _password,
        std::string _rol = "cliente", bool _activo = true)
        : id(_id), username(_username), password(_password), rol(_rol), activo(_activo) {
    }

    std::string getId() const { return id; }
    void setId(const std::string& _id) { id = _id; }

    std::string getUsername() const { return username; }
    void setUsername(const std::string& _username) { username = _username; }

    std::string getPassword() const { return password; }
    void setPassword(const std::string& _password) { password = _password; }

    std::string getRol() const { return rol; }
    void setRol(const std::string& _rol) { rol = _rol; }

    bool isActivo() const { return activo; }
    void setActivo(bool _activo) { activo = _activo; }

    std::string aCSV() const {
        return id + "," + username + "," + password + "," + rol + "," + (activo ? "1" : "0");
    }

    static Usuario desdeCSV(const std::string& csv) {
        Usuario u;
        std::stringstream ss(csv);
        std::string token;

        std::getline(ss, token, ','); u.id = token;
        std::getline(ss, token, ','); u.username = token;
        std::getline(ss, token, ','); u.password = token;
        std::getline(ss, token, ','); u.rol = token;
        std::getline(ss, token, ','); u.activo = (token == "1");

        return u;
    }
};

#endif