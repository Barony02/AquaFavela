#ifndef USER_H
#define USER_H

#include <QString>

enum class UserRole {
    None,
    Morador,
    Gestor,
    Administrador
};

class User {
public:
    // Construtor
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

protected:
    UserRole role;
    QString username;
    QString name;
    double maxMonthlyConsumptionGoal;
    double maxLitersPerMinuteGoal;

    friend class LoginDialog;
}; 
#endif // USER_H
