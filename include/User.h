#ifndef USER_H
#define USER_H

#include <QString>

enum class UserRole {
    None,
    Morador,
    Gestor,
    Administrador
};

/**
 * @brief A classe User representa um usuário do sistema, contendo informações como nome de usuário, nome completo, papel (morador, gestor ou administrador), metas de consumo e consumo total. Ela fornece getters e setters para acessar e modificar essas informações, e é utilizada em várias partes da aplicação para gerenciar as ações e permissões dos usuários.
 */
class User {
public:
    /**
     * @brief Construtor da classe User. Ele é responsável por inicializar as informações do usuário, como nome de usuário, papel, nome completo, metas de consumo e consumo total. O construtor pode receber parâmetros para definir essas informações no momento da criação do objeto User, ou pode ser chamado sem parâmetros para criar um usuário com valores padrão.
     * @param username O nome de usuário do usuário, que é uma string única que identifica o usuário no sistema.
     * @param role O papel do usuário, que pode ser Morador, Gestor ou Administrador, e determina as permissões e funcionalidades disponíveis para o usuário.
     * @param name O nome completo do usuário, que é uma string que representa o nome do usuário para exibição na interface gráfica.
     * @param maxMonthlyConsumptionGoal A meta de consumo mensal do usuário, que é um valor numérico que representa a quantidade máxima de litros que o usuário pretende consumir por mês.
     * @param maxLitersPerMinuteGoal A meta de consumo por minuto do usuário, que é um valor numérico que representa a quantidade máxima de litros que o usuário pretende consumir por minuto.
     */
    User(const QString &username = "",
         UserRole role = UserRole::None,
         const QString &name = "",
         double maxMonthlyConsumptionGoal = 0.0,
         double maxLitersPerMinuteGoal = 0.0);

    // Getters e Setters
    QString getUsername() const;
    void setUsername(const QString &newUsername);

    UserRole getRole() const;
    void setRole(UserRole newRole);

    QString getName() const;
    void setName(const QString &newName);

    double getMaxMonthlyConsumptionGoal() const;
    void setMaxMonthlyConsumptionGoal(double newMaxMonthlyConsumptionGoal);

    double getMaxLitersPerMinuteGoal() const;
    void setMaxLitersPerMinuteGoal(double newMaxLitersPerMinuteGoal);

    QString getPassword() const;
    void setPassword(const QString &newPassword);

    double getTotalConsumedLiters() const;
    void setTotalConsumedLiters(double newTotalConsumedLiters);

protected:
    UserRole role;
    QString username;
    QString name;
    QString password;
    double maxMonthlyConsumptionGoal;
    double maxLitersPerMinuteGoal;
    double totalConsumedLiters;

    // Amizade declarada dentro da classe
    friend class LoginDialog;
}; 

#endif // USER_H
