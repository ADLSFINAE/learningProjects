#ifndef XMLWORKER_H
#define XMLWORKER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QTreeWidget>
#include <QStack>
#include <QStringList>
#include <QDebug>

class XMLWorker : public QObject
{
    Q_OBJECT
public:
    explicit XMLWorker(QObject* parent = nullptr);

signals:
    void signalToAddTreeItem(QTreeWidgetItem* treeItem);

public slots:
    void xmlParsing(QString info);

private:
    QXmlStreamReader* _xmlStreamReader{nullptr};
};

#endif // XMLWORKER_H
