#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnOpenPort_clicked();

    void on_pushButton_clicked();

    void readData();

private:
    Ui::MainWindow* ui;
    QSerialPort* _serialPort;
    void loadPorts();
};
#endif // MAINWINDOW_H
