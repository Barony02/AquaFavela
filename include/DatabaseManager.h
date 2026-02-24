#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include "User.h"

/**
 * @brief A classe DatabaseManager é responsável por gerenciar a conexão com o banco de dados e fornecer métodos para realizar operações relacionadas aos usuários, como cadastro e atualização do consumo. Ela oferece uma interface centralizada para acessar o banco de dados, garantindo que as operações sejam realizadas de forma consistente e segura em toda a aplicação.
 */
class DatabaseManager
{
public:
    /**
     * @brief Método estático para inicializar a conexão com o banco de dados. Ele é responsável por configurar os parâmetros de conexão, como o tipo de banco de dados, o nome do banco, o nome de usuário e a senha. O método retorna um valor booleano indicando se a inicialização foi bem-sucedida ou não.
     * @return true se a inicialização for bem-sucedida, ou false caso contrário
     */
    static bool initialize();

    /**
     * @brief Método estático para obter a instância do banco de dados. Ele retorna um objeto QSqlDatabase que representa a conexão com o banco de dados, permitindo que outras partes da aplicação realizem operações de consulta e manipulação de dados.
     * @return A instância do banco de dados como um objeto QSqlDatabase
     */
    static QSqlDatabase getDatabase();

    /**
     * @brief Método estático para atualizar o consumo de água de um usuário no banco de dados. Ele recebe o nome de usuário e a quantidade total de litros consumidos, e realiza a atualização do consumo no banco de dados. O método retorna um valor booleano indicando se a atualização foi bem-sucedida ou não.
     * @param username O nome de usuário para o qual o consumo será atualizado.
     * @param totalLiters A quantidade total de litros consumidos que será atualizada no banco de dados.
     * @return true se a atualização for bem-sucedida, ou false caso contrário
     */
    static bool updateUserConsumption(const QString &username, double totalLiters);

    /**
     * @brief Método estático para registrar um novo usuário no banco de dados. Ele recebe um objeto User contendo as informações do usuário a ser registrado, e realiza a inserção dos dados no banco de dados. O método retorna um valor booleano indicando se o registro foi bem-sucedido ou não.
     * @param newUser O objeto User contendo as informações do usuário a ser registrado.
     * @return true se o registro for bem-sucedido, ou false caso contrário
     */
    static bool registerUser(const User &newUser);

    /**
    * @brief Recupera o consumo total de um usuário específico do banco de dados.
    * @param username O login do morador.
    * @return O valor do consumo em litros (double). Retorna -1.0 se o usuário não existir.
    */
    static double getUserConsumption(const QString& username);
};

#endif
