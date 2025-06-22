#ifndef XMLWORKER_H
#define XMLWORKER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QVector>
#include <QDebug>
#include <QFile>
#include <QString>

struct TableData{
    int rows;
    int cols;
    QVector<QVector<QString>> cellData;
};

class XMLWorker
{
public:
    XMLWorker();
    QVector<TableData> readTablesFromXML(const QString& filePath);
private:
    QVector<TableData> tables;
};

#endif // XMLWORKER_H
