#include "treewidget.h"

TreeWidget::TreeWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    QObject::connect(btnSendInfo, &QPushButton::clicked, this, &TreeWidget::slotSendInformation);
}

void TreeWidget::slotSendInformation()
{
    emit signalSendText(textEdit->toPlainText());
}

void TreeWidget::slotAddTreeItems(QTreeWidgetItem *item)
{
    treeWidget->addTopLevelItem(item);
}
