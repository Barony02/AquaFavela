#ifndef CONSUMPTIONSERVICE_H
#define CONSUMPTIONSERVICE_H

#include <QString>
#include <QObject>

/**
 * @brief A classe ConsumptionService é responsável por sincronizar o consumo de água dos usuários com um serviço externo, como um banco de dados ou uma API. Ela fornece um método estático para realizar essa sincronização, permitindo que o consumo seja atualizado de forma centralizada e consistente em toda a aplicação.
 */
class ConsumptionService : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Método estático para sincronizar o consumo de água de um usuário com um serviço externo. Ele recebe o nome de usuário e a quantidade de litros consumidos, e realiza a atualização do consumo no serviço externo. O método retorna um valor booleano indicando se a sincronização foi bem-sucedida ou não.
     * @param username O nome de usuário para o qual o consumo será sincronizado.
     * @param liters A quantidade de litros consumidos que será sincronizada.
     * @return true se a sincronização for bem-sucedida, ou false caso contrário
     */
    static bool syncUserConsumption(const QString& username, double liters);
};

#endif
