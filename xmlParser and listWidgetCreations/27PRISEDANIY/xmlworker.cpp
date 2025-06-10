#include "xmlworker.h"

XMLWorker::XMLWorker(QObject *parent)
    :QObject(parent)
{
    _xmlStreamReader = new QXmlStreamReader;
}

void XMLWorker::xmlParsing(QString info)
{
    _xmlStreamReader->addData(info);
    qDebug()<<"xmlParsing was started";
    QStack<QTreeWidgetItem*> stackWidget;
    while(not _xmlStreamReader->atEnd()){
        if(_xmlStreamReader->isStartElement()){
            QStringList strList;
            strList << _xmlStreamReader->name().toString();
            QTreeWidgetItem* item = new QTreeWidgetItem(strList);
            if(stackWidget.empty()){
                emit signalToAddTreeItem(item);
            }
            else{
                stackWidget.top()->addChild(item);
            }
            stackWidget.push(item);
        }
        if(_xmlStreamReader->isEndElement()){
            stackWidget.pop();
        }
        _xmlStreamReader->readNext();
    }
}
