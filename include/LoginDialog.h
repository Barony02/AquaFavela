#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "AuthService.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog {
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    User getLoggedUser() const;

private slots:
    void on_btnLogin_clicked();

private:
    Ui::LoginDialog *ui;
    AuthService authService;
    User loggedUser;
};

#endif // LOGINDIALOG_H
