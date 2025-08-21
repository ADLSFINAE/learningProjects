// main.cpp
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QMessageBox>
#include "htmlDatabase.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent)
    {
        setupUI();
        setupDatabase();
    }

private slots:
    void onConnectClicked()
    {
        QString url = urlEdit->text();
        if (url.isEmpty()) {
            url = "http://localhost:8080/database.html"; // Локальный сервер
        }
        db->connectToDatabase(url);
    }

    void onAddDataClicked()
    {
        QString device = deviceEdit->text();
        QString type = typeEdit->text();
        QString serial = serialEdit->text();
        QString status = statusEdit->text();
        QString results = resultsEdit->toPlainText();
        QString operatorName = operatorEdit->text();

        if (device.isEmpty() || serial.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Заполните обязательные поля");
            return;
        }

        db->addDevice(device, type, serial, status, results, operatorName);
    }

    void onConnected(bool success)
    {
        if (success) {
            statusLabel->setText("✅ Подключено к базе данных");
            statusLabel->setStyleSheet("color: green;");
        } else {
            statusLabel->setText("❌ Ошибка подключения");
            statusLabel->setStyleSheet("color: red;");
        }
    }

    void onDataAdded(bool success)
    {
        if (success) {
            QMessageBox::information(this, "Успех", "Данные добавлены в базу!\nОбновите страницу в браузере.");
            clearForm();
        }
    }

    void onError(const QString &errorMessage)
    {
        QMessageBox::critical(this, "Ошибка", errorMessage);
        statusLabel->setText("❌ Ошибка: " + errorMessage);
        statusLabel->setStyleSheet("color: red;");
    }

private:
    void setupUI()
    {
        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);

        // Поля для ввода
        urlEdit = new QLineEdit("http://localhost:8080/database.html");
        deviceEdit = new QLineEdit();
        typeEdit = new QLineEdit("Блок питания");
        serialEdit = new QLineEdit();
        statusEdit = new QLineEdit("OK");
        resultsEdit = new QTextEdit();
        operatorEdit = new QLineEdit();

        // Кнопки
        QPushButton *connectBtn = new QPushButton("Подключиться");
        QPushButton *addDataBtn = new QPushButton("Добавить данные");

        // Статус
        statusLabel = new QLabel("Не подключено");

        // Добавляем элементы
        layout->addWidget(new QLabel("URL базы данных:"));
        layout->addWidget(urlEdit);
        layout->addWidget(connectBtn);
        layout->addWidget(new QLabel("Устройство:"));
        layout->addWidget(deviceEdit);
        layout->addWidget(new QLabel("Тип:"));
        layout->addWidget(typeEdit);
        layout->addWidget(new QLabel("Серийный номер:"));
        layout->addWidget(serialEdit);
        layout->addWidget(new QLabel("Статус:"));
        layout->addWidget(statusEdit);
        layout->addWidget(new QLabel("Результаты:"));
        layout->addWidget(resultsEdit);
        layout->addWidget(new QLabel("Оператор:"));
        layout->addWidget(operatorEdit);
        layout->addWidget(addDataBtn);
        layout->addWidget(statusLabel);

        setCentralWidget(centralWidget);
        resize(600, 800);

        // Подключаем сигналы
        connect(connectBtn, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
        connect(addDataBtn, &QPushButton::clicked, this, &MainWindow::onAddDataClicked);
    }

    void setupDatabase()
    {
        db = new HtmlDatabase(this);
        connect(db, &HtmlDatabase::connected, this, &MainWindow::onConnected);
        connect(db, &HtmlDatabase::dataAdded, this, &MainWindow::onDataAdded);
        connect(db, &HtmlDatabase::error, this, &MainWindow::onError);
    }

    void clearForm()
    {
        deviceEdit->clear();
        serialEdit->clear();
        resultsEdit->clear();
    }

    HtmlDatabase *db;
    QLineEdit *urlEdit, *deviceEdit, *typeEdit, *serialEdit, *statusEdit, *operatorEdit;
    QTextEdit *resultsEdit;
    QLabel *statusLabel;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Тестовое подключение к HTML базе данных");
    window.show();

    return app.exec();
}

#include "main.moc"
