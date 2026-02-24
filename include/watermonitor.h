#ifndef WATERMONITOR_H
#define WATERMONITOR_H

#include <QString>
#include <QTimer>

/**
 * @brief A classe WaterMonitor é responsável por monitorar o consumo de água, fornecendo informações sobre o fluxo atual, status da água, consumo total e alertas. Ela utiliza um timer para atualizar os dados do sensor periodicamente e oferece métodos para acessar essas informações, bem como para configurar limites de consumo e forçar condições específicas de pressão.
 */
class WaterMonitor
{
public:
    /**
     * @brief Construtor da classe WaterMonitor. Ele é responsável por inicializar os atributos da classe, configurar o timer para atualizar os dados do sensor e definir os valores iniciais para o consumo, status e alertas.
     */
    WaterMonitor();

    /**
     * @brief Método para iniciar o monitoramento do consumo de água. Ele ativa o timer para que os dados do sensor sejam atualizados periodicamente, permitindo que a aplicação tenha informações em tempo real sobre o consumo de água e o status da água.
     */
    void startMonitoring();

    /**
     * @brief Método para verificar se há alertas relacionados ao consumo de água. Ele avalia as condições atuais do consumo, status da água e limites configurados para determinar se algum alerta deve ser acionado, como excesso de consumo ou problemas na rede de água.
     * @return true se houver alertas ativos, ou false caso contrário
     */
    bool checkAlerts();

    // Getters e Setters
    double getCurrentFlow();
    QString getWaterStatus();
    double getTotalConsumedLiters();
    
    void setTotalConsumedLiters(double x);
    QString getCurrentStatus() const;
    void setCurrentStatus(const QString &newCurrentStatus);

    double getCurrentUsage() const;
    void setCurrentUsage(double newCurrentUsage);

private:
    /**
     * @brief Método para atualizar os dados do sensor. Ele é chamado periodicamente pelo timer para obter as informações mais recentes sobre o consumo de água, status da água e alertas, garantindo que a aplicação tenha dados atualizados para exibir no dashboard e tomar decisões com base nessas informações.
     */
    void updateSensor();

    /**
     * @brief Método para atualizar o status da água. Ele avalia as condições atuais do consumo e da rede de água para determinar o status atual, como "Normal", "Alerta" ou "Crítico", e atualiza o atributo correspondente para que a interface gráfica possa exibir essa informação ao usuário.
     */
    void updateStatus();

    double currentUsage;
    double networkPressure;
    double totalConsumedLiters;
    QString currentStatus;
    int statusDurationRemaining;
    QTimer timer;

protected:
    double getTotalConsumedLiters() const;

    void setConsumptionLimit(double limit);
    bool isLimitExceeded() const;

    /**
     * @brief Método para forçar uma condição específica de pressão na rede de água. Ele é utilizado para simular situações de pressão anormal, permitindo que a aplicação teste as respostas do sistema a essas condições e verifique se os alertas e status são atualizados corretamente.
     * @param pressure O valor de pressão a ser forçado, que pode representar uma condição de pressão baixa ou alta na rede de água.
     */
    void forcePressure(double pressure);

    void setStatusDurationRemaining(int x);
    void addConsumption(double x);

    friend class TestSistemaAgua;
};

#endif // WATERMONITOR_H
