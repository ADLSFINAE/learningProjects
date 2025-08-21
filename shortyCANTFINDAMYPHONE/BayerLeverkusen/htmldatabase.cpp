#include "htmldatabase.h"
#include <QNetworkRequest>
#include <QDebug>

HtmlDatabase::HtmlDatabase(QObject *parent) : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &HtmlDatabase::onReplyFinished);
}

HtmlDatabase::~HtmlDatabase()
{
    delete networkManager;
}

void HtmlDatabase::connectToDatabase(const QString &url)
{
    baseUrl = url;

    // Проверяем подключение, отправляя GET запрос
    QNetworkRequest request((QUrl(url)));
    networkManager->get(request);
}

void HtmlDatabase::addDevice(const QString &deviceName, const QString &deviceType,
                           const QString &serialNumber, const QString &status,
                           const QString &results, const QString &operatorName)
{
    if (baseUrl.isEmpty()) {
        emit error("Не установлено подключение к базе данных");
        return;
    }

    // Формируем URL с параметрами
    QUrl url(baseUrl);
    QUrlQuery query;

    // Генерируем простой ID на основе времени
    QString id = QString::number(QDateTime::currentSecsSinceEpoch());

    query.addQueryItem("id", id);
    query.addQueryItem("device", deviceName);
    query.addQueryItem("type", deviceType);
    query.addQueryItem("serial", serialNumber);
    query.addQueryItem("status", status);
    query.addQueryItem("results", results);
    query.addQueryItem("operator", operatorName);

    url.setQuery(query);

    qDebug() << "Отправка данных по URL:" << url.toString();

    QNetworkRequest request(url);
    networkManager->get(request);
}

void HtmlDatabase::onReplyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QString urlString = reply->url().toString();

        if (urlString == baseUrl) {
            // Это был запрос на подключение
            emit connected(true);
            qDebug() << "✅ Успешное подключение к базе данных";
        } else {
            // Это был запрос на добавление данных
            emit dataAdded(true);
            qDebug() << "✅ Данные успешно добавлены в базу";
        }
    } else {
        QString errorMsg = reply->errorString();
        emit error(errorMsg);
        qWarning() << "❌ Ошибка:" << errorMsg;
    }

    reply->deleteLater();
}
