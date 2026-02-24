#include "mainwindow.h"
#include "LoginDialog.h"
#include <QApplication>
#include "DatabaseManager.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    DatabaseManager::initialize();

    // 1. Exibe Tela de Login
    LoginDialog login;
    if (login.exec() == QDialog::Accepted) {
        // 2. Se logou, abre a Janela Principal passando o usuário
        MainWindow w(login.getLoggedUser());
        w.show();
        return a.exec();
    }

    return 0;
}
