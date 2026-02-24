#include "User.h"

QString User::getUsername() const
{
    return username;
}

void User::setUsername(const QString &newUsername)
{
    username = newUsername;
}

UserRole User::getRole() const
{
    return role;
}

void User::setRole(UserRole newRole)
{
    role = newRole;
}

QString User::getName() const
{
    return name;
}

void User::setName(const QString &newName)
{
    name = newName;
}

double User::getMaxMonthlyConsumptionGoal() const
{
    return maxMonthlyConsumptionGoal;
}

void User::setMaxMonthlyConsumptionGoal(double newMaxMonthlyConsumptionGoal)
{
    maxMonthlyConsumptionGoal = newMaxMonthlyConsumptionGoal;
}

double User::getMaxLitersPerMinuteGoal() const
{
    return maxLitersPerMinuteGoal;
}

void User::setMaxLitersPerMinuteGoal(double newMaxLitersPerMinuteGoal)
{
    maxLitersPerMinuteGoal = newMaxLitersPerMinuteGoal;
}

QString User::getPassword() const
{
    return password;
}

void User::setPassword(const QString &newPassword)
{
    password = newPassword;
}

double User::getTotalConsumedLiters() const
{
    return totalConsumedLiters;
}

void User::setTotalConsumedLiters(double newTotalConsumedLiters)
{
    totalConsumedLiters = newTotalConsumedLiters;
}

User::User(const QString &username, UserRole role, const QString &name, double maxMonthlyConsumptionGoal, double maxLitersPerMinuteGoal) : username(username),
    role(role),
    name(name),
    maxMonthlyConsumptionGoal(maxMonthlyConsumptionGoal),
    maxLitersPerMinuteGoal(maxLitersPerMinuteGoal)
{}
