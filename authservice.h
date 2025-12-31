#pragma once

#include <QObject>
#include <QNetworkAccessManager>

class AuthService : public QObject
{
    Q_OBJECT

public:
    explicit AuthService(QObject* parent = nullptr);
    void login(const QString& login, const QString& password);

signals:
    void loginSuccess();
    void loginError(const QString& error);

private:
    QNetworkAccessManager* manager;
};
