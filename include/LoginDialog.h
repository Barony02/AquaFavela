#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "AuthService.h"

namespace Ui {
class LoginDialog;
}

/**
 * @brief A classe LoginDialog é responsável por fornecer uma interface gráfica para os usuários realizarem o login. Ela herda de QDialog, permitindo que seja exibida como uma janela de diálogo. A classe utiliza o AuthService para autenticar os usuários com base em suas credenciais (nome de usuário e senha) e armazena o usuário autenticado para uso posterior na aplicação.
 */
class LoginDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Construtor da classe LoginDialog. Ele inicializa a interface gráfica e configura os slots para os botões.
     * @param parent O widget pai, que é opcional. Se não for fornecido, o diálogo será independente.
     */
    explicit LoginDialog(QWidget *parent = nullptr);

    /**
     * @brief Destrutor da classe LoginDialog. Ele é responsável por liberar os recursos alocados pela interface gráfica.
     */
    ~LoginDialog();

    /**
    * @brief Método para obter o usuário autenticado. Ele retorna o objeto User correspondente ao usuário que realizou o login com sucesso. Esse método pode ser utilizado por outras partes da aplicação para acessar as informações do usuário autenticado.
    * @return O objeto User correspondente ao usuário autenticado.
    */
    User getLoggedUser() const;

private slots:
    /**
     * @brief Slot para o clique do botão de login. Ele coleta as credenciais do formulário, chama o método de autenticação no AuthService e, se a autenticação for bem-sucedida, armazena o usuário autenticado e fecha o diálogo. Caso contrário, pode exibir uma mensagem de erro para o usuário.
     */
    void on_btnLogin_clicked();

private:
    Ui::LoginDialog *ui;
    AuthService authService;
    User loggedUser;
};

#endif // LOGINDIALOG_H
