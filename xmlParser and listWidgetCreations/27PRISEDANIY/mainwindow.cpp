#include "mainwindow.h"
#include <QThread>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    QObject::connect(btnSettings, &QPushButton::clicked, this, &MainWindow::createMySimpleWidget);

    QObject::connect(btnOpenXML, &QPushButton::clicked, this, &MainWindow::createTreeVisualiserWidget);

}

MainWindow::~MainWindow()
{
}

void MainWindow::createMySimpleWidget()
{
    _mySimpleWidget = new MySimpleWidget();

    _mySimpleWidget->show();
}

void MainWindow::createTreeVisualiserWidget()
{
    _myTreeWidget = new TreeWidget();

    _myTreeWidget->show();

    _xmlWorker = new XMLWorker;

    connect(_myTreeWidget, &TreeWidget::signalSendText, _xmlWorker, &XMLWorker::xmlParsing);

    connect(_xmlWorker, &XMLWorker::signalToAddTreeItem, _myTreeWidget, &TreeWidget::slotAddTreeItems);
}

