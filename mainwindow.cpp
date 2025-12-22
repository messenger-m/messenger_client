#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&socket, &QWebSocket::connected,
            this, &MainWindow::onConnected);

    // connect(&socket, &QWebSocket::textMessageReceived,
    //         this, &MainWindow::onTextMessageReceived);

    socket.open(QUrl("ws://127.0.0.1:3000/ws"));
}

void MainWindow::onConnected()
{
    qDebug() << "WebSocket подключён";
}

void MainWindow::on_sendButton_clicked()
{
    QString text = ui->messageEdit->toPlainText();

    if (text.isEmpty())
        return;

    QJsonObject json;
    json["text"] = text;
    qDebug() << text;

    QJsonDocument doc(json);
    socket.sendTextMessage(doc.toJson(QJsonDocument::Compact));

    ui->messageEdit->clear();
}

// void MainWindow::onTextMessageReceived(const QString &message)
// {
//     qDebug() << "Сообщение от сервера:" << message;

//     // можно распарсить JSON
//     QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
//     QString text = doc.object()["text"].toString();

//     ui->chatwindow->append(text);
// }

MainWindow::~MainWindow()
{
    delete ui;
}
