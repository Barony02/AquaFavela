#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyle>

MainWindow::MainWindow(User user, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), currentUser(user)
{
    ui->setupUi(this);

    ui->lblUsuario->setText("Olá, " + currentUser.getUsername() + "!");

    if (currentUser.getRole() == UserRole::Morador) {
        ui->btnAdminPanel->setVisible(false);
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateDashboard);
    timer->start(2000);

    updateDashboard();
    monitor.startMonitoring();
}

WaterMonitor& MainWindow::getMonitor(){
    return monitor;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateDashboard() {
    double flow = monitor.getCurrentFlow();
        QString status = monitor.getWaterStatus();
        // Atualiza os cards de texto
        ui->lblConsumo->setText(QString::number(flow, 'f', 1) + " L/min");
        ui->lblMeta->setText("Meta = " + QString::number(currentUser.getMaxMonthlyConsumptionGoal()) + "L.");
        ui->lblConsumoTotalAtual->setText("Consumo Atual = " + QString::number(monitor.getTotalConsumedLiters()) + " Litros.");

    // Lógica da Barra de Status Dinâmica
    if (status == "Normal") {
        ui->lblAlerta->setText("SISTEMA OPERANDO: Abastecimento Normal");
            ui->lblAlerta->setProperty("status", "normal");
    }
    else if (status == "Escassez") {
        ui->lblAlerta->setText("ATENÇÃO: Fluxo de água reduzido!");
            ui->lblAlerta->setProperty("status", "atencao");
    }
    else if (status == "Interrupção") {
        ui->lblAlerta->setText("ALERTA CRÍTICO: Abastecimento Interrompido!");
            ui->lblAlerta->setProperty("status", "critico");
    }

    if (monitor.getTotalConsumedLiters() > currentUser.getMaxMonthlyConsumptionGoal()) {
        ui->lblAlertaConsumoMax->setText("ALERTA: CONSUMO MÁXIMO\nULTRAPASSADO!");
        ui->lblAlertaConsumoMax->setProperty("status", "alerta");
    } else {
        ui->lblAlertaConsumoMax->setText(""); // Limpa o texto quando está OK
        ui->lblAlertaConsumoMax->setProperty("status", "normal");
    }

    if (monitor.getCurrentFlow() > currentUser.getMaxLitersPerMinuteGoal()) {
        ui->lblAlertaConsumoMinuto->setText("ALERTA: CONSUMO MÁXIMO\nPOR MINUTO ULTRAPASSADO!");
        ui->lblAlertaConsumoMinuto->setProperty("status", "alerta");
    } else {
        ui->lblAlertaConsumoMinuto->setText(""); // Limpa o texto quando está OK
        ui->lblAlertaConsumoMinuto->setProperty("status", "normal");
    }

    ui->lblAlertaConsumoMinuto->style()->unpolish(ui->lblAlertaConsumoMinuto);
    ui->lblAlertaConsumoMinuto->style()->polish(ui->lblAlertaConsumoMinuto);

    ui->lblAlertaConsumoMax->style()->unpolish(ui->lblAlertaConsumoMax);
    ui->lblAlertaConsumoMax->style()->polish(ui->lblAlertaConsumoMax);

    // Força o CSS a atualizar a cor após mudar a propriedade "status"
    ui->lblAlerta->style()->unpolish(ui->lblAlerta);
    ui->lblAlerta->style()->polish(ui->lblAlerta);
}

User& MainWindow::getCurrentUser()
{
    return currentUser;
}

void MainWindow::setCurrentUser(const User &newCurrentUser)
{
    currentUser = newCurrentUser;
}
