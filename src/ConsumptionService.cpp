#include "ConsumptionService.h"
#include "DatabaseManager.h" // A Lógica pode acessar os Dados

bool ConsumptionService::syncUserConsumption(const QString& username, double liters) {
    // Aqui você pode adicionar regras de negócio no futuro
    return DatabaseManager::updateUserConsumption(username, liters);
}
