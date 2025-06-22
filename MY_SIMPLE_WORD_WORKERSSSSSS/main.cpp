#include <QAxObject>
#include <QApplication>
#include <QDebug>

#include "wordcreator.h"
#include "wordconfigurator.h"
#include "xmlworker.h"

QString algorithmica(QString leftOperand, QString rightOperand){
    bool result = true;


    return result ? QString("Соответствует").toUtf8() : QString("Не соответствует").toUtf8();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WordCreator wordCreator;

    WordConfigurator wordConfigurator;

    XMLWorker worker;

    QVector<TableData> vec = worker.readTablesFromXML(":/new/prefix1/configs/config.txt");
    QList<QString> listNums = {"1","19","3","2","20","4","3","21","4.5"};
    QVector<QVector<QString>> vecs;
    for(auto& elem : vec){
        if(elem.rows == 1 && elem.cols == 1){

        }
        else{
            for(int i = 0; i < elem.rows; i++){
                qDebug()<<elem.cellData[i][1].toStdWString();
                elem.cellData[i][1] = QString("Соответствует");
                qDebug()<<elem.cellData[i][1].toStdWString();
            }
        }
    }

    for(auto& elem : vec){
        wordConfigurator.addTable(wordCreator.getDocument(), wordCreator.getActiveList(),
                                  elem.rows, elem.cols, elem.cellData);
    }

    return a.exec();
}

