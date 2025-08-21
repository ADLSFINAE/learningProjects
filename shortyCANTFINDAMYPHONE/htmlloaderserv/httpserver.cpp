#include "httpserver.h"

#include <QDebug>
#include <QDir>
#include <QUrl>

HttpServer::HttpServer(QObject *parent) : QTcpServer(parent)
{
    // Добавляем начальные тестовые данные
    QUrlQuery testData1;
    testData1.addQueryItem("id", "1");
    testData1.addQueryItem("device", "БПИ-11.012");
    testData1.addQueryItem("type", "Блок питания");
    testData1.addQueryItem("serial", "SN001234");
    testData1.addQueryItem("status", "OK");
    testData1.addQueryItem("results", "Все тесты пройдены");
    testData1.addQueryItem("operator", "Иванов И.И.");

    QUrlQuery testData2;
    testData2.addQueryItem("id", "2");
    testData2.addQueryItem("device", "БПИ-11.014");
    testData2.addQueryItem("type", "Блок питания");
    testData2.addQueryItem("serial", "SN005678");
    testData2.addQueryItem("status", "error");
    testData2.addQueryItem("results", "Обнаружены неисправности");
    testData2.addQueryItem("operator", "Петров П.П.");

    storedData.append(testData1);
    storedData.append(testData2);
}

bool HttpServer::startServer(quint16 port)
{
    if (isListening()) {
        stopServer();
    }

    if (!listen(QHostAddress::Any, port)) {
        qWarning() << "❌ Не удалось запустить сервер:" << errorString();
        emit serverStarted(false);
        return false;
    }

    qDebug() << "✅ HTTP сервер запущен на порту" << port;
    qDebug() << "🌐 URL: http://localhost:" << port;
    qDebug() << "📊 Начальные данные:" << storedData.size() << "записей";
    emit serverStarted(true);
    return true;
}

void HttpServer::stopServer()
{
    close();
    qDebug() << "🛑 Сервер остановлен";
}

void HttpServer::addDeviceData(const QUrlQuery &queryData)
{
    storedData.append(queryData);
    emit newDataAdded(queryData);

    qDebug() << "📊 Добавлены новые данные. Всего записей:" << storedData.size();
    qDebug() << "📝 Данные:" << queryData.toString();
}

void HttpServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &HttpServer::readClient);
    connect(socket, &QTcpSocket::disconnected, this, &HttpServer::discardClient);

    socket->setSocketDescriptor(socketDescriptor);
}

void HttpServer::readClient()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    QString request = socket->readAll();
    sendResponse(socket, request);
}

void HttpServer::discardClient()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket) {
        socket->deleteLater();
    }
}

void HttpServer::sendResponse(QTcpSocket *socket, const QString &request)
{
    // Парсим URL из запроса
    QUrl url;
    if (request.startsWith("GET")) {
        QRegularExpression regex("GET ([^ ]+) HTTP");
        QRegularExpressionMatch match = regex.match(request);
        if (match.hasMatch()) {
            url = QUrl("http://localhost" + match.captured(1));
        }
    }

    if (url.path() == "/" || url.path() == "/database.html") {
        sendHtmlPage(socket, QUrlQuery(url.query()));
    } else {
        // Проверяем другие файлы
        QString filePath = QDir::currentPath() + url.path();
        QFile file(filePath);

        if (file.exists() && file.open(QIODevice::ReadOnly)) {
            QFileInfo fileInfo(file);
            QString mimeType = getMimeType(fileInfo.suffix());

            QByteArray response = "HTTP/1.1 200 OK\r\n";
            response += "Content-Type: " + mimeType.toUtf8() + "\r\n";
            response += "Content-Length: " + QByteArray::number(file.size()) + "\r\n";
            response += "Connection: close\r\n\r\n";
            response += file.readAll();

            socket->write(response);
            file.close();
        } else {
            sendNotFound(socket);
        }
    }

    socket->close();
}

void HttpServer::sendHtmlPage(QTcpSocket *socket, const QUrlQuery &query)
{
    // Если есть данные в query, добавляем их
    if (!query.isEmpty()) {
        addDeviceData(query);
    }

    QString html = generateHtmlWithData(query);

    QByteArray response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: text/html; charset=utf-8\r\n";
    response += "Content-Length: " + QByteArray::number(html.toUtf8().size()) + "\r\n";
    response += "Connection: close\r\n\r\n";
    response += html.toUtf8();

    socket->write(response);
}

void HttpServer::sendNotFound(QTcpSocket *socket)
{
    QByteArray response = "HTTP/1.1 404 Not Found\r\n";
    response += "Content-Type: text/plain\r\n";
    response += "Connection: close\r\n\r\n";
    response += "404 - File Not Found";

    socket->write(response);
}

void HttpServer::sendError(QTcpSocket *socket, const QString &message)
{
    QByteArray response = "HTTP/1.1 500 Internal Server Error\r\n";
    response += "Content-Type: text/plain\r\n";
    response += "Connection: close\r\n\r\n";
    response += "500 - " + message.toUtf8();

    socket->write(response);
}

QString HttpServer::getMimeType(const QString &extension)
{
    static QMap<QString, QString> mimeTypes = {
        {"html", "text/html"}, {"css", "text/css"}, {"js", "application/javascript"},
        {"json", "application/json"}, {"png", "image/png"}, {"jpg", "image/jpeg"},
        {"jpeg", "image/jpeg"}, {"gif", "image/gif"}, {"ico", "image/x-icon"},
        {"txt", "text/plain"}
    };
    return mimeTypes.value(extension.toLower(), "application/octet-stream");
}

QString HttpServer::generateHtmlWithData(const QUrlQuery &query)
{
    // Читаем исходный HTML файл
    QFile htmlFile("C://database.html");

    if (!htmlFile.open(QIODevice::ReadOnly)) {
        qWarning() << "❌ Не удалось открыть database.html";
        return "<h1>Error: database.html not found</h1>";
    }

    QString html = QString::fromUtf8(htmlFile.readAll());
    htmlFile.close();

    // Находим tbody для добавления данных
    int tbodyStart = html.indexOf("<tbody id=\"data-body\">");
    int tbodyEnd = html.indexOf("</tbody>", tbodyStart);

    if (tbodyStart == -1 || tbodyEnd == -1) {
        qWarning() << "❌ Не найден tbody в HTML";
        return html;
    }

    // Генерируем HTML для всех данных
    QString newRows;
    for (const auto &data : storedData) {
        QString id = data.queryItemValue("id");
        QString device = data.queryItemValue("device");
        QString type = data.queryItemValue("type");
        QString serial = data.queryItemValue("serial");
        QString status = data.queryItemValue("status");
        QString results = data.queryItemValue("results");
        QString operatorName = data.queryItemValue("operator");

        // Генерируем дату, если не указана
        QString date = data.queryItemValue("date");
        if (date.isEmpty()) {
            date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm");
        }

        // Определяем класс статуса
        QString statusClass = "status-warning";
        if (status == "OK") statusClass = "status-ok";
        else if (status == "error") statusClass = "status-error";

        newRows += QString("<tr>"
            "<td>%1</td>"
            "<td>%2</td>"
            "<td>%3</td>"
            "<td>%4</td>"
            "<td><span class=\"status %5\">%6</span></td>"
            "<td>%7</td>"
            "<td>%8</td>"
            "<td>%9</td>"
            "</tr>")
            .arg(id)
            .arg(device)
            .arg(type)
            .arg(serial)
            .arg(statusClass)
            .arg(status)
            .arg(date)
            .arg(results)
            .arg(operatorName);
    }

    // Заменяем содержимое tbody
    QString newTbody = "<tbody id=\"data-body\">" + newRows + "</tbody>";
    html.replace(tbodyStart, tbodyEnd - tbodyStart + 8, newTbody);

    return html;
}
