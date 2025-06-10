#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _serialPort(nullptr)
{
    setupUi(this);
    loadPorts();
}

MainWindow::~MainWindow()
{
    delete ui;

    if(_serialPort != nullptr){
        _serialPort->close();
        delete _serialPort;
    }

}

void MainWindow::loadPorts()
{
    for(auto& port : QSerialPortInfo::availablePorts())
        cmbPorts->addItem(port.portName());
}


void MainWindow::on_btnOpenPort_clicked()
{

    if(_serialPort != nullptr){
        _serialPort->close();
        delete _serialPort;
    }

    _serialPort = new QSerialPort;
    _serialPort->setPortName(cmbPorts->currentText());
    _serialPort->setBaudRate(QSerialPort::Baud9600);
    _serialPort->setDataBits(QSerialPort::Data8);
    _serialPort->setParity(QSerialPort::NoParity);
    _serialPort->setStopBits(QSerialPort::OneStop);


    if(_serialPort->open(QIODevice::ReadWrite)){
        QMessageBox::information(nullptr, "OPEN", "PORT SUCCESFULLY OPENNED");
        QObject::connect(_serialPort, &QSerialPort::readyRead, this, &MainWindow::readData);
    }
    else{
        QMessageBox::warning(nullptr, "Error", "WE ARE FUCKED UP");
    }
}


void MainWindow::on_pushButton_clicked()
{
    if(!_serialPort->isOpen()){
        QMessageBox::warning(this, "Error", "WE ARE FUCKED UP");
        return;
    }
    _serialPort->write(lnMessage->text().toUtf8());
}

void MainWindow::readData()
{
    if(!_serialPort->isOpen()){
        QMessageBox::warning(this, "Error", "WE ARE FUCKED UP");
        return;
    }

    auto data = _serialPort->readAll();

    lstMessage->addItem(data);

}

