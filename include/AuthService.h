#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include "User.h"
#include <QString>

class AuthService {
public:
    AuthService();
    // Retorna um usuário válido se as credenciais baterem
    User authenticate(const QString &username, const QString &password);
};

#endif // AUTHSERVICE_H
