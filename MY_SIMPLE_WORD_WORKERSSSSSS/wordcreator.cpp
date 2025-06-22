#include "wordcreator.h"

WordCreator::WordCreator(QObject *parent)
    :QObject(parent),
      _pWordProgrammObject(nullptr),
      _pDocumentsOfWordProgrammObject(nullptr),
      _pDocument(nullptr),
      _pActiveList(nullptr)
{
    initObject();
}

void WordCreator::initObject()
{
    _pWordProgrammObject = new QAxObject("Word.Application");
    _pWordProgrammObject->dynamicCall("SetVisible(bool)", true);
    _pWordProgrammObject->setProperty("DisplayAlerts", false);

    _pDocumentsOfWordProgrammObject = _pWordProgrammObject->querySubObject("Documents");

    _pDocument = _pDocumentsOfWordProgrammObject->querySubObject("Add()");

    _pActiveList = _pWordProgrammObject->querySubObject("Selection");

}

QAxObject *WordCreator::getWordProgrammObject() const
{
    return _pWordProgrammObject;
}

QAxObject *WordCreator::getDocumentsOfWordProgrammObject() const
{
    return _pDocumentsOfWordProgrammObject;
}

QAxObject *WordCreator::getDocument() const
{
    return _pDocument;
}

QAxObject *WordCreator::getActiveList() const
{
    return _pActiveList;
}
