#include "mysimplewidget.h"

MySimpleWidget::MySimpleWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);


    QObject::connect(btnSave, &QPushButton::clicked, this, [=](){
        QMessageBox::information(this, "SOMETHING", "SUCCESFULLY WAS SAVED");
    });

    QObject::connect(btnUpdate, &QPushButton::clicked, this, &MySimpleWidget::updateItemsInListWidget);

    QObject::connect(btnClose, &QPushButton::clicked, this, &MySimpleWidget::close);

}

void MySimpleWidget::updateItemsInListWidget()
{
    qDebug()<<"SIGNAL TO UPDATE ITEMS IN LIST WIDGET";

    QWidget *containerWidget = new QWidget();
    QHBoxLayout *hLayout = new QHBoxLayout(containerWidget);

    QLabel *label = new QLabel("LABEL");
    QComboBox *comboBox = new QComboBox();
    comboBox->addItems({"VAR1", "VAR2", "VAR3"});

    hLayout->addWidget(label);
    hLayout->addWidget(comboBox);

    QListWidgetItem *item = new QListWidgetItem(listWidget);

    listWidget->setItemWidget(item, containerWidget);

    for (int i = 0; i < 3; ++i) {
        QWidget *container = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(container);
        layout->setContentsMargins(0, 0, 0, 0);

        QLabel *label = new QLabel(QString("%1").arg(i+1));
        QComboBox *cb = new QComboBox();
        cb->addItems({"A", "B", "C"});

        layout->addWidget(label);
        layout->addWidget(cb);

        QListWidgetItem *newItem = new QListWidgetItem();
        listWidget->addItem(newItem);
        newItem->setSizeHint(container->sizeHint());
        listWidget->setItemWidget(newItem, container);
    }
}

