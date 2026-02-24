#include "LoginDialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->lblError->clear();
    ui->edtPass->setEchoMode(QLineEdit::Password); // Esconde a senha
    setWindowTitle("AquaFavela - Login");
}

LoginDialog::~LoginDialog() {
    delete ui;
}

User LoginDialog::getLoggedUser() const {
    return loggedUser;
}

void LoginDialog::on_btnLogin_clicked() {
    QString user = ui->edtUser->text();
    QString pass = ui->edtPass->text();

    // Chama o serviço atualizado
    User result = authService.authenticate(user, pass);

    if (result.getRole() != UserRole::None) {
        this->loggedUser = result;
        accept(); // Fecha o diálogo com sucesso
    } else {
        ui->lblError->setText("Usuário ou senha inválidos!");
        ui->edtPass->clear();
    }
}
