#include <QtTest>
#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include "watermonitor.h"
#include "mainwindow.h"
#include "ConsumptionService.h"
#include "User.h"
#include "DatabaseManager.h"
#include "AuthService.h"

class TestSistemaAgua : public QObject
{
    Q_OBJECT

private slots:

    /**
     * @brief Configura a conexão com o banco de dados antes dos testes.
     * Garante que o driver SQLite está carregado e o arquivo aberto.
     */
    void initTestCase() {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("AquaFavela.db");

        if (!db.open()) {
            QFAIL("Nao foi possivel abrir o banco de dados.");
        }

        QSqlQuery query;
        // Criação da tabela com a estrutura completa
        query.exec(
            "CREATE TABLE IF NOT EXISTS users ("
            "username TEXT PRIMARY KEY,"
            "password TEXT NOT NULL,"
            "role INTEGER NOT NULL,"
            "name TEXT,"
            "maxMonthlyConsumptionGoal REAL,"
            "maxLitersPerMinuteGoal REAL,"
            "totalConsumedLiters REAL DEFAULT 0.0"
            ");"
            );

        // Limpa o usuário de teste para evitar erro de PRIMARY KEY
        query.prepare("DELETE FROM users WHERE username = :u");
        query.bindValue(":u", "gabriel_teste");
        query.exec();

        // INSERT especificando as colunas (Mais robusto para a Sprint 3)
        query.prepare("INSERT INTO users (username, password, role, name, "
                      "maxMonthlyConsumptionGoal, maxLitersPerMinuteGoal, totalConsumedLiters) "
                      "VALUES (:u, :p, :r, :n, :maxM, :maxL, :total)");

        query.bindValue(":u", "gabriel_teste");
        query.bindValue(":p", "123");              // Senha
        query.bindValue(":r", 1);                  // Role (Morador)
        query.bindValue(":n", "Gabriel");          // Nome
        query.bindValue(":maxM", 100.0);           // Meta mensal
        query.bindValue(":maxL", 20.0);            // Meta L/min
        query.bindValue(":total", 0.0);            // Consumo inicial

        if (!query.exec()) {
            QFAIL(qPrintable("Falha ao inserir usuario de teste: " + query.lastError().text()));
        }
    }
    void cleanupTestCase() {
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    }


    // ================================
    // CENÁRIO 1 – Registrar consumo
    // ================================
    void testRegistrarConsumo()
    {
        WaterMonitor monitor;

        monitor.addConsumption(5);
        QCOMPARE(monitor.getTotalConsumedLiters(), 5.0);

        monitor.addConsumption(10);
        QCOMPARE(monitor.getTotalConsumedLiters(), 15.0);

        monitor.addConsumption(15);
        QCOMPARE(monitor.getTotalConsumedLiters(), 30.0);

        monitor.addConsumption(0);
        QCOMPARE(monitor.getTotalConsumedLiters(), 30.0);
    }

    // ==========================================
    // CENÁRIO 2 – Registrar Status Abastecimento
    // ==========================================
    void testRegistrarStatus()
    {
        WaterMonitor monitor;
        monitor.updateStatus(); // O monitor sempre começa com pressão = 100, logo o status é Normal

        monitor.forcePressure(35.0); // < 40 é escassez
        monitor.setStatusDurationRemaining(0);
        monitor.updateStatus();
        QCOMPARE(monitor.getWaterStatus(), QString("Escassez"));


        monitor.forcePressure(5);  // < 10 que é interrupção
        monitor.setStatusDurationRemaining(0);
        monitor.updateStatus();
        QCOMPARE(monitor.getWaterStatus(), QString("Interrupção"));


        monitor.forcePressure(80.0);
        monitor.setStatusDurationRemaining(0);
        monitor.updateStatus();
        QCOMPARE(monitor.getWaterStatus(), QString("Normal"));


        monitor.forcePressure(90.0);
        monitor.setStatusDurationRemaining(0);
        monitor.updateStatus();
        QCOMPARE(monitor.getWaterStatus(), QString("Normal"));


        monitor.forcePressure(35.0);
        monitor.updateStatus();
        monitor.forcePressure(80.0);
        monitor.setStatusDurationRemaining(0);
        monitor.updateStatus();
        QCOMPARE(monitor.getWaterStatus(), QString("Normal"));

    }

    // ==========================================
    // CENÁRIO 3 – Gerar alerta por limite
    // ==========================================
    void testAlertaConsumoExcessivo()
    {
        User user;
        user.setUsername("morador");
        user.setMaxMonthlyConsumptionGoal(100);

        MainWindow window(user);

        QLabel* label;

        window.getMonitor().setTotalConsumedLiters(80);
        window.updateDashboard();

        label = window.findChild<QLabel*>("lblAlertaConsumoMax");

        QVERIFY(label != nullptr);
        QCOMPARE(label->text(), QString(""));

        window.getMonitor().setTotalConsumedLiters(100);
        window.updateDashboard();
        QCOMPARE(label->text(), QString(""));

        window.getMonitor().setTotalConsumedLiters(110);
        window.updateDashboard();
        QCOMPARE(label->text(), QString("ALERTA: CONSUMO MÁXIMO\nULTRAPASSADO!"));

        window.getCurrentUser().setMaxMonthlyConsumptionGoal(200.0);
        window.getMonitor().setTotalConsumedLiters(250.0);
        window.updateDashboard();
        QCOMPARE(label->text(), QString("ALERTA: CONSUMO MÁXIMO\nULTRAPASSADO!"));

        window.getCurrentUser().setMaxMonthlyConsumptionGoal(150.0);
        window.getMonitor().setTotalConsumedLiters(149.0);
        window.updateDashboard();
        QCOMPARE(label->text(), QString(""));
    }

    // ==========================================
    // CENÁRIO 4 – Alerta por escassez
    // ==========================================
    void testEscassezDetectada()
    {
        User user;
        WaterMonitor monitor;
        MainWindow window(user);


        QLabel* label = window.findChild<QLabel*>("lblAlerta");
        QVERIFY(label != nullptr);


        window.getMonitor().forcePressure(90);
        window.getMonitor().updateStatus();
        window.updateDashboard();
        QCOMPARE(label->text(), QString("SISTEMA OPERANDO: Abastecimento Normal"));


        window.getMonitor().forcePressure(60);
        window.getMonitor().updateStatus();
        window.updateDashboard();
        QCOMPARE(label->text(), QString("SISTEMA OPERANDO: Abastecimento Normal"));


        window.getMonitor().forcePressure(35);
        window.getMonitor().updateStatus();
        window.updateDashboard();
        QCOMPARE(label->text(), QString("ATENÇÃO: Fluxo de água reduzido!"));


        window.getMonitor().forcePressure(15);
        window.getMonitor().updateStatus();
        window.updateDashboard();
        QCOMPARE(label->text(), QString("ATENÇÃO: Fluxo de água reduzido!"));


        window.getMonitor().forcePressure(0);
        window.getMonitor().setStatusDurationRemaining(0);
        window.getMonitor().updateStatus();
        window.updateDashboard();
        QCOMPARE(label->text(), QString("ALERTA CRÍTICO: Abastecimento Interrompido!"));
    }

    // ==========================================
    // CENÁRIO 5 – Exibição na interface
    // ==========================================
    void testExibicaoInterface()
    {
        User user;
        user.setUsername("morador");
        user.setMaxMonthlyConsumptionGoal(1000);

        MainWindow window(user);
        window.getMonitor().setTotalConsumedLiters(5);
        window.updateDashboard();

        QLabel* label = window.findChild<QLabel*>("lblConsumoTotalAtual");

        QVERIFY(label != nullptr);
        QCOMPARE(label->text(), QString("Consumo Atual = 5 Litros."));

        window.getMonitor().setTotalConsumedLiters(20);
        window.updateDashboard();
        QCOMPARE(label->text(), QString("Consumo Atual = 20 Litros."));

        window.getMonitor().setTotalConsumedLiters(35);
        window.updateDashboard();
        QCOMPARE(label->text(), QString("Consumo Atual = 35 Litros."));

        window.getMonitor().setTotalConsumedLiters(100);
        window.updateDashboard();
        QCOMPARE(label->text(), QString("Consumo Atual = 100 Litros."));

        window.getMonitor().setTotalConsumedLiters(250);
        window.updateDashboard();
        QCOMPARE(label->text(), QString("Consumo Atual = 250 Litros."));
    }

    /**
     * @brief Valida se a atualização de consumo é persistida e recuperada corretamente.
     */
    void testIntegridadeConsumo()
    {
        QString user = "gabriel_teste";
        double consumoNovo = 125.75;

        // Ação: Salva via BusinessLayer (provando o desacoplamento)
        bool sucesso = ConsumptionService::syncUserConsumption(user, consumoNovo);
        QVERIFY(sucesso);

        // Verificação: Busca o valor real no banco
        double valorRecuperado = DatabaseManager::getUserConsumption(user);
        QCOMPARE(valorRecuperado, consumoNovo);
    }

    /**
     * @brief Testa o fluxo de login real consultando o SQLite.
     */
    void testLoginBD()
    {
        AuthService auth;
        // Supõe que o usuário 'admin' com senha '123' existe no seu AquaFavela.db de teste
        User resultado = auth.authenticate("admin", "admin");

        QVERIFY(resultado.getUsername() == "admin");
        QVERIFY(resultado.getRole() == (UserRole)3); // Verifica se carregou o cargo corretamente
    }


    /**
     * @brief Verifica o comportamento do sistema ao buscar um usuário que não existe.
     */
    void testUsuarioInexistente()
    {
        // Tenta sincronizar consumo para um usuário que não está no banco
        bool resultado = ConsumptionService::syncUserConsumption("usuario_fantasma", 10.0);

        // O sistema deve retornar false de forma elegante, não dar crash
        QCOMPARE(resultado, false);
    }
};

QTEST_MAIN(TestSistemaAgua)

#include "testes.moc"
