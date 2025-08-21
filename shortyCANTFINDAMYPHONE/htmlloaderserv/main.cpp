// main.cpp
#include <QCoreApplication>
#include <QTimer>
#include "httpserver.h"
#include "databaseclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Запускаем сервер
    HttpServer server;
    if (!server.startServer(8080)) {
        return 1;
    }

    // Создаем клиент для добавления данных
    /*DatabaseClient client;

    qDebug() << "🚀 Сервер запущен!";
    qDebug() << "🌐 Откройте: http://localhost:8080/database.html";
    qDebug() << "📝 Данные будут добавлены через 2 и 4 секунды...";

    // Добавляем тестовые данные через таймеры
    QTimer::singleShot(2000, [&client]() {
        qDebug() << "➕ Добавляем устройство 1...";
        client.addDevice(
            "БПИ-11.015",
            "Блок питания",
            "SN009999",
            "OK",
            "Автоматическое тестирование завершено",
            "Автотест"
        );
    });

    QTimer::singleShot(4000, [&client]() {
        qDebug() << "➕ Добавляем устройство 2...";
        client.addDevice(
            "БПИ-11.016",
            "Блок питания",
            "SN000001",
            "error",
            "Обнаружена неисправность в цепи",
            "Система мониторинга"
        );
    });

    QTimer::singleShot(6000, [&client]() {
        qDebug() << "➕ Добавляем устройство через параметры...";
        QUrlQuery params;
        params.addQueryItem("device", "БПИ-11.017");
        params.addQueryItem("type", "Блок питания");
        params.addQueryItem("serial", "SN000002");
        params.addQueryItem("status", "warning");
        params.addQueryItem("results", "Требуется дополнительная проверка");
        params.addQueryItem("operator", "Инженер");

        client.addDeviceWithUrlParams(params);
    });*/

    return app.exec();
}
