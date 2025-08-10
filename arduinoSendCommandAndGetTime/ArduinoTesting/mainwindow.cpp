#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    arduino = new QSerialPort(this);
    arduino->setPortName("COM5"); // Укажите ваш порт (например, COM3 или /dev/ttyACM0)
    arduino->setBaudRate(QSerialPort::Baud9600);
    arduino->open(QIODevice::ReadWrite);

    connect(arduino, &QSerialPort::readyRead, this, &MainWindow::readSerialData);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonStart_clicked()
{
    qDebug()<<"start was clicked";

    if (arduino->isOpen()) {
        arduino->write("START\n"); // Отправляем команду
        ui->outputText->append("Отправлено: START");
    }
}

void MainWindow::readSerialData()
{
    QString data = arduino->readAll();
    qDebug()<<data;
    ui->outputText->append("Получено: " + data.trimmed());
}


void MainWindow::on_pushButtonStop_clicked()
{
    if (arduino->isOpen()) {
        arduino->write("STOP\n"); // Отправляем команду
        ui->outputText->append("Отправлено: STOP");
    }
}

