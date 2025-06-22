#include "xmlworker.h"

XMLWorker::XMLWorker()
{

}

QVector<TableData> XMLWorker::readTablesFromXML(const QString &filePath)
{
    QVector<TableData> tables;
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл:" << filePath;
        return tables;
    }

    QXmlStreamReader xml(&file);
    TableData currentTable;
    QVector<QString> currentRow;

    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::StartElement) {
            if (xml.name().toString() == "table") {
                currentTable = TableData();
                currentTable.rows = xml.attributes().value("rows").toInt();
                currentTable.cols = xml.attributes().value("cols").toInt();
            }
            else if (xml.name().toString() == "row") {
                currentRow.clear();
            }
            else if (xml.name().toString() == "cell") {
                currentRow.append(xml.readElementText());
            }
        }
        else if (token == QXmlStreamReader::EndElement) {
            if (xml.name().toString() == "row") {
                currentTable.cellData.append(currentRow);
            }
            else if (xml.name().toString() == "table") {
                tables.append(currentTable);
            }
        }
    }

    if (xml.hasError()) {
        qDebug() << "Ошибка XML:" << xml.errorString();
    }

    file.close();
    return tables;
}
