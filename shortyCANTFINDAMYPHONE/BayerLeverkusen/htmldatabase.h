#ifndef HTMLDATABASE_H
#define HTMLDATABASE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QDateTime>

class HtmlDatabase : public QObject
{
    Q_OBJECT

public:
    explicit HtmlDatabase(QObject *parent = nullptr);
    ~HtmlDatabase();

    void connectToDatabase(const QString &url);
    void addDevice(const QString &deviceName, const QString &deviceType,
                  const QString &serialNumber, const QString &status,
                  const QString &results, const QString &operatorName);

signals:
    void connected(bool success);
    void dataAdded(bool success);
    void error(const QString &errorMessage);

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;
    QString baseUrl;
};
#endif // HTMLDATABASE_H
