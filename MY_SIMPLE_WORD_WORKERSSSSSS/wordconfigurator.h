#ifndef WORDCONFIGURATOR_H
#define WORDCONFIGURATOR_H

#include <QObject>
#include <QAxObject>

class WordConfigurator : public QObject
{
    Q_OBJECT
public:
    WordConfigurator();

    void addTable(QAxObject *document, QAxObject* selection, int row, int column, QVector<QVector<QString>> data);

    void insertIntoCell(QAxObject* table, int row, int col, const QString& text);

    int getGlobalTargetRow() const {return globalTargetRow;}

private:
    QAxObject* rangeAfter{nullptr};
    int globalTargetRow = 0;
};

#endif // WORDCONFIGURATOR_H
