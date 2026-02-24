#include "AuthService.h"

AuthService::AuthService() {}

User AuthService::authenticate(const QString &username, const QString &password) {
    // Simulação de banco de dados para o AquaFavela
    if (username == "admin" && password == "admin") {
        return User(username, UserRole::Administrador, "Admin do Sistema", 0.0, 0.0);
    }

    if (username == "gestor" && password == "123") {
        return User(username, UserRole::Gestor, "Gestor da Rede", 0.0, 0.0);
    }

    if (username == "morador" && password == "123") {
        return User(username, UserRole::Morador, "Morador da Silva", 18000.0, 9.0);
    }

    return User();
}
