#include "chatclient.h"

#include <QJsonObject>
#include <QJsonDocument>

ChatClient::ChatClient(QObject* parent)
    : QObject(parent)
{
    connect(&socket, &QWebSocket::connected,
            this, &ChatClient::connected);

    connect(&socket, &QWebSocket::textMessageReceived,
            this, &ChatClient::messageReceived);
}

void ChatClient::connectToServer()
{
    socket.open(QUrl("ws://127.0.0.1:3000/ws"));
}

void ChatClient::sendMessage(const QString& text)
{
    QJsonObject json;
    json["text"] = text;

    socket.sendTextMessage(
        QJsonDocument(json).toJson(QJsonDocument::Compact)
        );
}
