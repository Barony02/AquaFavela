#include "DatabaseManager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCoreApplication>

bool DatabaseManager::initialize()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    QString path =
        QCoreApplication::applicationDirPath() + "/AquaFavela.db";

    qDebug() << "Banco em:" << path;

    db.setDatabaseName(path);

    if (!db.open())
    {
        qDebug() << "Erro ao abrir banco:"
                 << db.lastError().text();
        return false;
    }

    QSqlQuery query;

    query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "username TEXT PRIMARY KEY,"
        "password TEXT NOT NULL,"
        "role INTEGER NOT NULL,"
        "name TEXT,"
        "maxMonthlyConsumptionGoal REAL,"
        "maxLitersPerMinuteGoal REAL,"
        "totalConsumedLiters REAL DEFAULT 0.0"
        ");"
        );

    // INSERT DO PRIMEIRO USUÁRIO
    QSqlQuery insertQuery;

    insertQuery.exec(
        "INSERT OR IGNORE INTO users "
        "(username, password, role, name, maxMonthlyConsumptionGoal, maxLitersPerMinuteGoal) "
        "VALUES ("
        "'admin',"
        "'admin',"
        "3,"
        "'José Alberto',"
        "1000,"
        "20"
        ");"
        );

    QSqlQuery insertQuery2;

    insertQuery2.exec(
        "INSERT OR IGNORE INTO users "
        "(username, password, role, name, maxMonthlyConsumptionGoal, maxLitersPerMinuteGoal) "
        "VALUES ("
        "'gestor',"
        "'123',"
        "2,"
        "'Lucas',"
        "600000,"
        "500"
        ");"
        );
    qDebug() << "Usuário padrão criado/verificado";

    return true;
}

bool DatabaseManager::updateUserConsumption(const QString& username, double liters) {
    QSqlQuery query;
    query.prepare("UPDATE users SET totalConsumedLiters = :liters WHERE username = :user");
    query.bindValue(":liters", liters);
    query.bindValue(":user", username);

    // Executa a query
    if (!query.exec()) {
        qDebug() << "Erro de SQL no Update:" << query.lastError().text();
        return false;
    }

    // PROVA DE ROBUSTEZ: Verifica se alguma linha foi de fato alterada
    // Se o usuário não existir, rowsAffected() retornará 0
    if (query.numRowsAffected() == 0) {
        qDebug() << "Aviso: Nenhum usuario encontrado com o nome" << username;
        return false;
    }

    return true;
}

bool DatabaseManager::registerUser(const User &newUser) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, role, name, "
                  "maxMonthlyConsumptionGoal, maxLitersPerMinuteGoal, totalConsumedLiters) "
                  "VALUES (:user, :pass, :role, :name, :maxMonth, :maxMin, 0.0)");

    query.bindValue(":user", newUser.getUsername());
    query.bindValue(":pass", newUser.getPassword());
    query.bindValue(":role", static_cast<int>(newUser.getRole()));
    query.bindValue(":name", newUser.getName());
    query.bindValue(":maxMonth", newUser.getMaxMonthlyConsumptionGoal());
    query.bindValue(":maxMin", newUser.getMaxLitersPerMinuteGoal());

    if (!query.exec()) {
        qDebug() << "Erro ao cadastrar usuário:" << query.lastError().text();
        return false;
    }
    return true;
}

double DatabaseManager::getUserConsumption(const QString& username) {
    QSqlQuery query;
    // O nome da coluna DEVE ser idêntico ao do CREATE TABLE
    query.prepare("SELECT totalConsumedLiters FROM users WHERE username = :user");
    query.bindValue(":user", username);

    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    } else {
        // Isso ajudará você a ver o erro real no console de testes
        qDebug() << "Erro SQL:" << query.lastError().text();
        return -1.0;
    }
}
