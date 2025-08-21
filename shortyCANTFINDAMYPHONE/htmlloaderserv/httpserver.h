#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>
#include <QUrlQuery>
#include <QDateTime>
#include <QRegularExpression>

class HttpServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit HttpServer(QObject *parent = nullptr);
    bool startServer(quint16 port = 8080);
    void stopServer();

    // Метод для добавления данных из других программ
    void addDeviceData(const QUrlQuery &queryData);

signals:
    void serverStarted(bool success);
    void newDataAdded(const QUrlQuery &data);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void readClient();
    void discardClient();

private:
    void sendResponse(QTcpSocket *socket, const QString &request);
    void sendHtmlPage(QTcpSocket *socket, const QUrlQuery &query = QUrlQuery());
    void sendNotFound(QTcpSocket *socket);
    void sendError(QTcpSocket *socket, const QString &message);

    QString getMimeType(const QString &extension);
    QString generateHtmlWithData(const QUrlQuery &query = QUrlQuery());

    QList<QUrlQuery> storedData; // Храним все добавленные данные
};


#endif // HTTPSERVER_H
