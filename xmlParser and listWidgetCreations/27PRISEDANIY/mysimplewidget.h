#ifndef MYSIMPLEWIDGET_H
#define MYSIMPLEWIDGET_H

#include "ui_mysimplewidget.h"

#include <QPushButton>
#include <QWidget>
#include <QObject>
#include <QMessageBox>
#include <QDebug>

#include <QComboBox>
#include <QHBoxLayout>

#include <QLabel>

class MySimpleWidget : public QWidget, private Ui::MySimpleWidget
{
    Q_OBJECT

public:
    explicit MySimpleWidget(QWidget *parent = nullptr);

public slots:
    void updateItemsInListWidget();
};

#endif // MYSIMPLEWIDGET_H
