#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "User.h"
#include "watermonitor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief A classe MainWindow é a janela principal da aplicação, responsável por exibir o dashboard de consumo de água e fornecer acesso às funcionalidades do sistema. Ela herda de QMainWindow, permitindo que seja exibida como a janela principal da aplicação. A classe gerencia o usuário atualmente autenticado, o monitor de água e um timer para atualizar os dados do sensor periodicamente.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Construtor da classe MainWindow. Ele é responsável por inicializar a interface gráfica, configurar os slots para os botões e iniciar o timer para atualizar os dados do sensor.
     * @param user O objeto User representando o usuário atualmente autenticado. Ele é passado como parâmetro para que a MainWindow possa exibir as informações do usuário e gerenciar suas ações de consumo.
     * @param parent O widget pai, que é opcional. Se não for fornecido, a janela será independente.
     */
    MainWindow(User user, QWidget *parent = nullptr);

    /**
     * @brief Destrutor da classe MainWindow. Ele é responsável por liberar os recursos alocados pela interface gráfica e pelo timer.
     */
    ~MainWindow();

    // Getters e Setters
    User& getCurrentUser();
    void setCurrentUser(const User &newCurrentUser);

private slots:

    /**
     * @brief Slot para atualizar o dashboard de consumo de água. Ele é chamado periodicamente pelo timer para obter os dados do monitor de água e atualizar a interface gráfica com as informações mais recentes sobre o consumo, status da água e alertas.
     */
    void updateDashboard(); // Atualiza dados do sensor

    /**
     * @brief Slot para o clique do botão de logout. Ele é responsável por encerrar a sessão do usuário atual, limpar os dados do monitor e redirecionar para a tela de login.
     */
    void closeEvent(QCloseEvent *event);

    /**
     * @brief Slot para salvar os dados de consumo. Ele é chamado quando o usuário deseja salvar os dados de consumo atuais, e é responsável por sincronizar esses dados com um serviço externo, como um banco de dados ou uma API, utilizando a classe ConsumptionService.
     */
    void saveConsumptionData();

    /**
     * @brief Slot para o clique do botão de painel administrativo. Ele é responsável por abrir a janela de administração, onde o administrador pode cadastrar novos usuários e gerenciar as configurações do sistema.
     */
    void on_btnAdminPanel_clicked();

private:
    Ui::MainWindow *ui;
    User currentUser;
    WaterMonitor monitor;
    QTimer *timer;

protected:
    WaterMonitor& getMonitor();
    User& getUser();

friend class TestSistemaAgua;
};

#endif // MAINWINDOW_H
