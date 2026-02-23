#include "watermonitor.h"
#include <QRandomGenerator>
#include <QObject>

WaterMonitor::WaterMonitor()
    : currentUsage(0.0),
    networkPressure(100.0),
    currentStatus("Normal"),
    statusDurationRemaining(0),
    totalConsumedLiters(0)
{
}

void WaterMonitor::startMonitoring()
{
    // faz primeira leitura imediatamente
    updateSensor();

    QObject::connect(&timer, &QTimer::timeout, [this]() {
        updateSensor();
    });

    // leitura a cada 30 segundos
    timer.start(2000);
}

void WaterMonitor::updateSensor()
{
    // variação suave do consumo (-5 a +5)
    double variation =
        (QRandomGenerator::global()->generateDouble() * 10.0) - 5.0;

    currentUsage += variation;

    if (currentUsage < 0)
        currentUsage = 0;

    if (currentUsage > 50)
        currentUsage = 50;

    // variação da meta de consumo

    totalConsumedLiters += currentUsage * (2/60.0);

    // variação lenta da pressão (-2 a +2)
    double pressureVariation =
        (QRandomGenerator::global()->generateDouble() * 4.0) - 2.0;

    networkPressure += pressureVariation;

    if (networkPressure < 0)
        networkPressure = 0;

    if (networkPressure > 100)
        networkPressure = 100;

    updateStatus();
}

void WaterMonitor::updateStatus()
{
    // mantém estado atual até acabar o tempo mínimo
    if (statusDurationRemaining > 0) {
        statusDurationRemaining--;
        return;
    }

    QString newStatus;

    if (networkPressure < 10)
        newStatus = "Interrupção";
    else if (networkPressure < 40)
        newStatus = "Escassez";
    else
        newStatus = "Normal";

    // se mudou o estado, define duração mínima
    if (newStatus != currentStatus)
    {
        currentStatus = newStatus;

        if (newStatus == "Interrupção")
            statusDurationRemaining = 10;

        else if (newStatus == "Escassez")
            statusDurationRemaining = 8;

        else
            statusDurationRemaining = 5;
    }
}

QString WaterMonitor::getCurrentStatus() const
{
    return currentStatus;
}

void WaterMonitor::setCurrentStatus(const QString &newCurrentStatus)
{
    currentStatus = newCurrentStatus;
}

double WaterMonitor::getCurrentFlow()
{
    return currentUsage;
}

QString WaterMonitor::getWaterStatus()
{
    return currentStatus;
}

bool WaterMonitor::checkAlerts()
{
    return (currentStatus == "Interrupção" ||
            currentStatus == "Escassez" ||
            currentUsage > 45);
}

double WaterMonitor::getTotalConsumedLiters(){
    return totalConsumedLiters;
}

void WaterMonitor::setTotalConsumedLiters(double x){
    totalConsumedLiters = x;
}

void WaterMonitor::forcePressure(double pressure){
    networkPressure = pressure;
}

void WaterMonitor::setStatusDurationRemaining(int x){
    statusDurationRemaining = x;
}
void WaterMonitor::addConsumption(double x){
    totalConsumedLiters += x;
}
