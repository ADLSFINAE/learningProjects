#ifndef WORDCREATOR_H
#define WORDCREATOR_H

#include <QAxObject>
#include <QObject>

class WordCreator : public QObject
{
    Q_OBJECT
public:
    explicit WordCreator(QObject* parent = nullptr);

    QAxObject* getWordProgrammObject() const;
    QAxObject* getDocumentsOfWordProgrammObject() const;
    QAxObject* getDocument() const;

    QAxObject* getActiveList() const;

private:
    void initObject();

private:
    QAxObject* _pWordProgrammObject;
    QAxObject* _pDocumentsOfWordProgrammObject;
    QAxObject* _pDocument;

    QAxObject* _pActiveList;
};

#endif // WORDCREATOR_H
