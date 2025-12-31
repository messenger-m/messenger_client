#pragma once

#include <QObject>
#include <QWebSocket>

class ChatClient : public QObject
{
    Q_OBJECT

public:
    explicit ChatClient(QObject* parent = nullptr);
    void connectToServer();
    void sendMessage(const QString& text);

signals:
    void connected();
    void messageReceived(const QString& text);

private:
    QWebSocket socket;
};
