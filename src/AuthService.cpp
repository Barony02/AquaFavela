#include "AuthService.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

AuthService::AuthService() {}

// Alterado para retornar o objeto User diretamente, facilitando o uso no Dialog
User AuthService::authenticate(const QString& username, const QString& password) {
    User loggedUser;
    QSqlQuery query;

    // Selecionando todas as colunas definidas no DatabaseManager
    query.prepare(
        "SELECT username, password, role, name, maxMonthlyConsumptionGoal, maxLitersPerMinuteGoal, totalConsumedLiters "
        "FROM users "
        "WHERE username = :username AND password = :password"
        );

    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Erro SQL:" << query.lastError().text();
        return loggedUser; // Retorna User com Role::None
    }

    if (query.next()) {
        // Usando os métodos setter para contornar o erro de "protected"
        loggedUser.setUsername(query.value("username").toString());
        loggedUser.setPassword(query.value("password").toString());
        loggedUser.setName(query.value("name").toString());

        int roleInt = query.value("role").toInt();
        loggedUser.setRole(static_cast<UserRole>(roleInt));

        loggedUser.setMaxMonthlyConsumptionGoal(query.value("maxMonthlyConsumptionGoal").toDouble());
        loggedUser.setMaxLitersPerMinuteGoal(query.value("maxLitersPerMinuteGoal").toDouble());
    }

    loggedUser.setTotalConsumedLiters(query.value("totalConsumedLiters").toDouble());

    return loggedUser;
}
