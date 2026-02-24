#include "AdminDialog.h"
#include "ui_admindialog.h"
#include <QMessageBox>

AdminDialog::AdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);
    setWindowTitle("AquaFavela - Gestão de Usuários");
}

AdminDialog::~AdminDialog()
{
    delete ui;
}

void AdminDialog::on_btnRegister_clicked()
{
    // 1. Captura de dados da interface
    QString name = ui->edtName->text();
    QString username = ui->edtUsername->text();
    QString password = ui->edtPassword->text();
    double monthlyGoal = ui->spnMonthlyGoal->value();
    double minuteGoal = ui->spnMinuteGoal->value();

    // 2. Validação básica (não permite campos vazios)
    if(name.isEmpty() || username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Aviso", "Preencha todos os campos obrigatórios!");
        return;
    }

    // 3. Criar objeto User temporário (Encapsulamento)
    User newUser;
    newUser.setName(name);
    newUser.setUsername(username);
    newUser.setPassword(password);
    newUser.setRole(UserRole::Morador); // Define como 2 (Morador) por padrão
    newUser.setMaxMonthlyConsumptionGoal(monthlyGoal);
    newUser.setMaxLitersPerMinuteGoal(minuteGoal);

    // 4. Enviar para a camada de persistência (DatabaseManager)
    if (DatabaseManager::registerUser(newUser)) {
        QMessageBox::information(this, "Sucesso", "Morador cadastrado com sucesso!");

        // Limpa os campos após o cadastro
        ui->edtName->clear();
        ui->edtUsername->clear();
        ui->edtPassword->clear();
    } else {
        QMessageBox::critical(this, "Erro", "Erro ao cadastrar. O login já pode estar em uso.");
    }
}
