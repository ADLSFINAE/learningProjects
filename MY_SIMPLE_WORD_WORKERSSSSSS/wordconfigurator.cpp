#include "wordconfigurator.h"

WordConfigurator::WordConfigurator()
{

}

void WordConfigurator::addTable(QAxObject *document, QAxObject* selection, int row, int column)
{
    QAxObject* range = document->querySubObject("Range()");
    QAxObject* tables = document->querySubObject("Tables");
    QAxObject* table1;
    if(rangeAfter == nullptr){
        table1 = tables->querySubObject("Add(Range*, int, int)", range->asVariant(), row, column);
    }

    if(rangeAfter != nullptr){
        table1 = tables->querySubObject("Add(Range*, int, int)", rangeAfter->asVariant(), row, column);
    }

    // 4. ��������� ������� ��� ������ �������
    QAxObject* borders1 = table1->querySubObject("Borders");
    borders1->setProperty("Enable", true);
    // ������� ����� 1pt (0.75 �������)
    borders1->querySubObject("Item(WdBorderType)", 1)->setProperty("LineWidth", 1); // ������� �������
    borders1->querySubObject("Item(WdBorderType)", 2)->setProperty("LineWidth", 1); // ���������� �������

    // 5. �������� ��������� ��� ������ �������
    rangeAfter = table1->querySubObject("Range")->querySubObject("Next()");
}

