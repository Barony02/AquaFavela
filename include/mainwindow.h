#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "User.h"
#include "watermonitor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(User user, QWidget *parent = nullptr);
    ~MainWindow();

    User& getCurrentUser();
    void setCurrentUser(const User &newCurrentUser);

private slots:
    void updateDashboard(); // Atualiza dados do sensor

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
