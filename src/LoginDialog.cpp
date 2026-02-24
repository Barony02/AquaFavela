#include "LoginDialog.h"
#include "ui_logindialog.h"


LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog) {
    ui->setupUi(this);
    ui->lblError->clear();
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

    User result = authService.authenticate(user, pass);

    // Use o método getRole() em vez de acessar .role diretamente
    if (result.getRole() != UserRole::None) {
        loggedUser = result;
        accept();
    } else {
        ui->lblError->setText("Usuário ou senha inválidos!");
    }
}
