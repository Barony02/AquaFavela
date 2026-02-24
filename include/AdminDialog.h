#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include "User.h" // Necessário para criar o objeto User que será salvo
#include "DatabaseManager.h" // Necessário para acessar o método de cadastro

namespace Ui {
class AdminDialog;
}
/**
 * @brief A classe AdminDialog é responsável por fornecer uma interface gráfica para o administrador cadastrar novos usuários.
 * Ela herda de QDialog, permitindo que seja exibida como uma janela de diálogo.
 */
class AdminDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construtor da classe AdminDialog. Ele inicializa a interface gráfica e configura os slots para os botões.
     * @param parent O widget pai, que é opcional. Se não for fornecido, o diálogo será independente.
     */
    explicit AdminDialog(QWidget *parent = nullptr);

    /**
     * @brief Destrutor da classe AdminDialog. Ele é responsável por liberar os recursos alocados pela interface gráfica.
     */
    ~AdminDialog();

private slots:
    /**
     * @brief Slot para o clique do botão de registro. Ele coleta os dados do formulário, cria um objeto User e chama o método de cadastro no DatabaseManager.
     */
    void on_btnRegister_clicked();

private:
    Ui::AdminDialog *ui;
};

#endif
