#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include "ui_treewidget.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>

class TreeWidget : public QWidget, private Ui::TreeWidget
{
    Q_OBJECT

public:
    explicit TreeWidget(QWidget *parent = nullptr);

signals:
    void signalSendText(QString info);

public slots:
    void slotSendInformation();
    void slotAddTreeItems(QTreeWidgetItem* item);
};

#endif // TREEWIDGET_H


