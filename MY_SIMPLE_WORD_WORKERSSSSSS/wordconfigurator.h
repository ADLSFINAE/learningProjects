#ifndef WORDCONFIGURATOR_H
#define WORDCONFIGURATOR_H

#include <QObject>
#include <QAxObject>

class WordConfigurator : public QObject
{
    Q_OBJECT
public:
    WordConfigurator();

    void addTable(QAxObject *document, QAxObject* selection, int row, int column);
private:
    QAxObject* rangeAfter{nullptr};
};

#endif // WORDCONFIGURATOR_H
