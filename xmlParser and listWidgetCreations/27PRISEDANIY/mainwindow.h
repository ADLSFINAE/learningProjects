#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include "mysimplewidget.h"
#include "treewidget.h"
#include "xmlworker.h"

#include <QMainWindow>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void createMySimpleWidget();
    void createTreeVisualiserWidget();

private:
    MySimpleWidget* _mySimpleWidget{nullptr};
    TreeWidget* _myTreeWidget{nullptr};

    XMLWorker* _xmlWorker;
};
#endif // MAINWINDOW_H
