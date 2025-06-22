#include <QAxObject>
#include <QApplication>
#include <QDebug>

#include "wordcreator.h"
#include "wordconfigurator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WordCreator wordCreator;

    WordConfigurator wordConfigurator;

    wordConfigurator.addTable(wordCreator.getDocument(), wordCreator.getActiveList(), 1, 1);
    wordConfigurator.addTable(wordCreator.getDocument(), wordCreator.getActiveList(), 2, 2);
    wordConfigurator.addTable(wordCreator.getDocument(), wordCreator.getActiveList(), 1, 1);
    wordConfigurator.addTable(wordCreator.getDocument(), wordCreator.getActiveList(), 4, 2);
    wordConfigurator.addTable(wordCreator.getDocument(), wordCreator.getActiveList(), 1, 1);
    wordConfigurator.addTable(wordCreator.getDocument(), wordCreator.getActiveList(), 2, 2);

    return a.exec();
}
