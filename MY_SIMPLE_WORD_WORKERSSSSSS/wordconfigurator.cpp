#include "wordconfigurator.h"

WordConfigurator::WordConfigurator()
{

}

void WordConfigurator::addTable(QAxObject *document, QAxObject* selection,
                                int rows, int columns, QVector<QVector<QString>> data)
{
    QAxObject* range = document->querySubObject("Range()");
    QAxObject* tables = document->querySubObject("Tables");
    QAxObject* table1;
    if(rangeAfter == nullptr){
        table1 = tables->querySubObject("Add(Range*, int, int)", range->asVariant(), rows, columns);
    }

    if(rangeAfter != nullptr){
        table1 = tables->querySubObject("Add(Range*, int, int)", rangeAfter->asVariant(), rows, columns);
    }

    QAxObject* borders1 = table1->querySubObject("Borders");
    borders1->setProperty("Enable", true);

    borders1->querySubObject("Item(WdBorderType)", 1)->setProperty("LineWidth", 1); // ¬нешн€€ граница
    borders1->querySubObject("Item(WdBorderType)", 2)->setProperty("LineWidth", 1); // ¬нутренние границы

    rangeAfter = table1->querySubObject("Range")->querySubObject("Next()");

    for(int i = 1; i <= rows; i++) {
        globalTargetRow++;
        for(int j = 1; j <= columns; j++) {
            insertIntoCell(table1, globalTargetRow, j, data[i - 1][j - 1]);
        }
    }
}

void WordConfigurator::insertIntoCell(QAxObject *table, int row, int col, const QString &text)
{
    QAxObject* cell = table->querySubObject("Cell(Row, Column)", row, col);

    if(cell && !cell->isNull()) {
        QAxObject* cellRange = cell->querySubObject("Range");

        cellRange->dynamicCall("SetText(const QString&)", text);

        cellRange->querySubObject("ParagraphFormat")->setProperty("Alignment", 1);

        delete cellRange;
        delete cell;
    }
}

