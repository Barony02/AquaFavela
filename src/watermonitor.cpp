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

}

double WaterMonitor::getCurrentFlow()
{
    return currentUsage;
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

void WaterMonitor::addConsumption(double x){
    totalConsumedLiters += x;
}
