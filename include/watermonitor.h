#ifndef WATERMONITOR_H
#define WATERMONITOR_H

#include <QString>
#include <QTimer>

class WaterMonitor
{
public:
    WaterMonitor();
    void startMonitoring();
    double getCurrentFlow();
    QString getWaterStatus();
    double getTotalConsumedLiters();
    bool checkAlerts();

    QString getCurrentStatus() const;
    void setCurrentStatus(const QString &newCurrentStatus);

private:
    void updateSensor();
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

    void forcePressure(double pressure);

    void setStatusDurationRemaining(int x);
    void setTotalConsumedLiters(double x);
    void addConsumption(double x);

    friend class TestSistemaAgua;
};

#endif // WATERMONITOR_H
