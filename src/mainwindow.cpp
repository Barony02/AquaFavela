#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DatabaseManager.h"
#include "ConsumptionService.h"
#include "AdminDialog.h"
#include <QStyle>
#include <QCloseEvent>

MainWindow::MainWindow(User user, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), currentUser(user)
{
    ui->setupUi(this);

    ui->lblUsuario->setText("Olá, " + currentUser.getName() + "!");

    if (currentUser.getRole() == (UserRole)3) {
        ui->btnAdminPanel->setVisible(true);
    } else {
        ui->btnAdminPanel->setVisible(false);
    }

    monitor.setTotalConsumedLiters(currentUser.getTotalConsumedLiters());

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateDashboard);
    timer->start(2000);


    QTimer *saveTimer = new QTimer(this);
    connect(saveTimer, &QTimer::timeout, this, &MainWindow::saveConsumptionData);
    saveTimer->start(300000);

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
        ui->lblMetaMinuto->setText("Meta Maxima = " + QString::number(currentUser.getMaxLitersPerMinuteGoal()) + "L/Min");

        //Atualiza a barra de progresso da Meta de Consumo Maxima
        double percent = (monitor.getTotalConsumedLiters()/currentUser.getMaxMonthlyConsumptionGoal()) * 100.0;
        ui->progressMeta->setValue(percent);
        ui->progressMeta->setFormat(QString::number(percent, 'f', 2) + "%");

        //Atualiza a barra de progresso da Meta de Consumo Maxima por minuto
        percent = (monitor.getCurrentUsage()/currentUser.getMaxLitersPerMinuteGoal()) * 100.0;
        ui->progressConsumo->setValue(percent);
        ui->progressConsumo->setFormat(QString::number(percent, 'f', 2) + "%");

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


void MainWindow::saveConsumptionData() {
    double totalAtual = monitor.getTotalConsumedLiters();
    QString username = currentUser.getUsername();

    // PROVA DE ACOPLAMENTO FRACO: A UI chama a Lógica, não o Banco.
    if (ConsumptionService::syncUserConsumption(username, totalAtual)) {
        qDebug() << "Consumo sincronizado via BusinessLayer.";
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    // Salva os dados antes de destruir o objeto
    saveConsumptionData();

    // Permite que a janela feche normalmente
    event->accept();
}

void MainWindow::on_btnAdminPanel_clicked()
{
    // Instancia o diálogo passando a MainWindow como pai (this)
    AdminDialog dialog(this);

    // Define um título para a janela, se ainda não definiu no Designer
    dialog.setWindowTitle("Painel de Administração - AquaFavela");

    // Abre a janela e trava a MainWindow até o admin fechar
    dialog.exec();
}

