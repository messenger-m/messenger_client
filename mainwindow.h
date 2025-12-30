#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QKeyEvent>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    QWebSocket socket;
    QNetworkAccessManager* networkManager;
    QString authToken;


private slots:
    void onLoginClicked();
    void onConnected();
    void appendMessage(const QString &html, Qt::Alignment align);
    void onTextMessageReceived(const QString &message);
    void on_sendButton_clicked();
    // void onLoginReply(QNetworkReply* reply);
    void sendLoginRequest(const QString& login, const QString& password);
};
#endif // MAINWINDOW_H
