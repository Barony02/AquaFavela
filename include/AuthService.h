#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include "User.h"

/**
 * @brief A classe AuthService é responsável por autenticar os usuários com base em suas credenciais (nome de usuário e senha).
 * Ela fornece um método para verificar se as credenciais fornecidas correspondem a um usuário registrado e retorna o objeto User correspondente se a autenticação for bem-sucedida.
 */
class AuthService
{
public:
    /**
     * @brief Construtor da classe AuthService. Ele é responsável por inicializar quaisquer recursos necessários para a autenticação, como conexões com o banco de dados ou carregamento de dados de usuários.
     */
    AuthService();

    /**
     * @brief Método para autenticar um usuário com base em suas credenciais (nome de usuário e senha).
     * Ele verifica se as credenciais fornecidas correspondem a um usuário registrado e retorna o objeto User correspondente se a autenticação for bem-sucedida. Caso contrário, pode lançar uma exceção ou retornar um valor indicando falha na autenticação.
     * @param username O nome de usuário fornecido para autenticação.
     * @param password A senha fornecida para autenticação.
     * @return O objeto User correspondente ao usuário autenticado, ou um valor indicando falha na autenticação.
     */
    User authenticate(const QString& username, const QString& password);
};

#endif
