#include "authservice.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>

AuthService::AuthService(QObject* parent)
    : QObject(parent),
    manager(new QNetworkAccessManager(this))
{}

void AuthService::login(const QString& login, const QString& password)
{
    QUrl url("http://127.0.0.1:3000/login");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["login"] = login;
    json["password"] = password;

    auto reply = manager->post(
        request,
        QJsonDocument(json).toJson()
        );

    connect(reply, &QNetworkReply::finished, this, [=]() {
        QString body = QString::fromUtf8(reply->readAll());

        if (reply->error() == QNetworkReply::NoError) {
            emit loginSuccess();
        } else {
            emit loginError(body);
        }

        reply->deleteLater();
    });
}
