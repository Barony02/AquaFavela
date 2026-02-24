#include <QtTest>
#include <QLabel>
#include "watermonitor.h"
#include "mainwindow.h"
#include "User.h"

class TestSistemaAgua : public QObject
{
    Q_OBJECT

private slots:


    // CENÁRIO 1 – Registrar consumo
    void testRegistrarConsumo()
    {
        WaterMonitor monitor;

        monitor.addConsumption(5);
        QCOMPARE(monitor.getTotalConsumedLiters(), 5.0);

        monitor.addConsumption(10);
        QCOMPARE(monitor.getTotalConsumedLiters(), 15.0);

        monitor.addConsumption(15);
        QCOMPARE(monitor.getTotalConsumedLiters(), 30.0);

        monitor.addConsumption(0);
        QCOMPARE(monitor.getTotalConsumedLiters(), 30.0);
    }


    // CENÁRIO 2 – Registrar Status Abastecimento
    void testRegistrarStatus()
    {
        WaterMonitor monitor;
        monitor.updateStatus(); // O monitor sempre começa com pressão = 100, logo o status é Normal

        monitor.forcePressure(35.0); // < 40 é escassez
        monitor.setStatusDurationRemaining(0);
        monitor.updateStatus();
        QCOMPARE(monitor.getWaterStatus(), QString("Escassez"));


        monitor.forcePressure(5);  // < 10 que é interrupção
        monitor.setStatusDurationRemaining(0);
        monitor.updateStatus();
        QCOMPARE(monitor.getWaterStatus(), QString("Interrupção"));


        monitor.forcePressure(80.0);
        monitor.setStatusDurationRemaining(0);
        monitor.updateStatus();
        QCOMPARE(monitor.getWaterStatus(), QString("Normal"));


        monitor.forcePressure(90.0);
        monitor.setStatusDurationRemaining(0);
        monitor.updateStatus();
        QCOMPARE(monitor.getWaterStatus(), QString("Normal"));


        monitor.forcePressure(35.0);
        monitor.updateStatus();
        monitor.forcePressure(80.0);
        monitor.setStatusDurationRemaining(0);
        monitor.updateStatus();
        QCOMPARE(monitor.getWaterStatus(), QString("Normal"));

    }


    // CENÁRIO 3 – Gerar alerta por limite
    void testAlertaConsumoExcessivo()
    {
        User user;
        user.setUsername("morador");
        user.setMaxMonthlyConsumptionGoal(100);

        MainWindow window(user);

        QLabel* label;

        window.getMonitor().setTotalConsumedLiters(80);
        window.updateDashboard();

        label = window.findChild<QLabel*>("lblAlertaConsumoMax");

        QVERIFY(label != nullptr);
        QCOMPARE(label->text(), QString(""));

        window.getMonitor().setTotalConsumedLiters(100);
        window.updateDashboard();
        QCOMPARE(label->text(), QString(""));

        window.getMonitor().setTotalConsumedLiters(110);
        window.updateDashboard();
        QCOMPARE(label->text(), QString("ALERTA: CONSUMO MÁXIMO\nULTRAPASSADO!"));

        window.getCurrentUser().setMaxMonthlyConsumptionGoal(200.0);
        window.getMonitor().setTotalConsumedLiters(250.0);
        window.updateDashboard();
        QCOMPARE(label->text(), QString("ALERTA: CONSUMO MÁXIMO\nULTRAPASSADO!"));

        window.getCurrentUser().setMaxMonthlyConsumptionGoal(150.0);
        window.getMonitor().setTotalConsumedLiters(149.0);
        window.updateDashboard();
        QCOMPARE(label->text(), QString(""));
    }


    // CENÁRIO 4 – Alerta por escassez
    void testEscassezDetectada()
    {
        User user;
        WaterMonitor monitor;
        MainWindow window(user);


        QLabel* label = window.findChild<QLabel*>("lblAlerta");
        QVERIFY(label != nullptr);


        window.getMonitor().forcePressure(90);
        window.getMonitor().updateStatus();
        window.updateDashboard();
        QCOMPARE(label->text(), QString("SISTEMA OPERANDO: Abastecimento Normal"));


        window.getMonitor().forcePressure(60);
        window.getMonitor().updateStatus();
        window.updateDashboard();
        QCOMPARE(label->text(), QString("SISTEMA OPERANDO: Abastecimento Normal"));


        window.getMonitor().forcePressure(35);
        window.getMonitor().updateStatus();
        window.updateDashboard();
        QCOMPARE(label->text(), QString("ATENÇÃO: Fluxo de água reduzido!"));


        window.getMonitor().forcePressure(15);
        window.getMonitor().updateStatus();
        window.updateDashboard();
        QCOMPARE(label->text(), QString("ATENÇÃO: Fluxo de água reduzido!"));


        window.getMonitor().forcePressure(0);
        window.getMonitor().setStatusDurationRemaining(0);
        window.getMonitor().updateStatus();
        window.updateDashboard();
        QCOMPARE(label->text(), QString("ALERTA CRÍTICO: Abastecimento Interrompido!"));
    }


    // CENÁRIO 5 – Exibição na interface
    void testExibicaoInterface()
    {
        User user;
        user.setUsername("morador");
        user.setMaxMonthlyConsumptionGoal(1000);

        MainWindow window(user);
        window.getMonitor().setTotalConsumedLiters(5);
        window.updateDashboard();

        QLabel* label = window.findChild<QLabel*>("lblConsumoTotalAtual");

        QVERIFY(label != nullptr);
        QCOMPARE(label->text(), QString("Consumo Atual = 5 Litros."));

        window.getMonitor().setTotalConsumedLiters(20);
        window.updateDashboard();
        QCOMPARE(label->text(), QString("Consumo Atual = 20 Litros."));

        window.getMonitor().setTotalConsumedLiters(35);
        window.updateDashboard();
        QCOMPARE(label->text(), QString("Consumo Atual = 35 Litros."));

        window.getMonitor().setTotalConsumedLiters(100);
        window.updateDashboard();
        QCOMPARE(label->text(), QString("Consumo Atual = 100 Litros."));

        window.getMonitor().setTotalConsumedLiters(250);
        window.updateDashboard();
        QCOMPARE(label->text(), QString("Consumo Atual = 250 Litros."));
    }
};

QTEST_MAIN(TestSistemaAgua)

#include "testes.moc"
