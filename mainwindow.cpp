#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&socket, &QWebSocket::connected,
            this, &MainWindow::onConnected);

    ui->password->setEchoMode(QLineEdit::Password);


    ui->toggleButton->setCheckable(true);
    ui->toggleButton->setText("👁");
    ui->toggleButton->setCursor(Qt::PointingHandCursor);

    // подключаем сигнал
    connect(ui->toggleButton, &QPushButton::toggled, [=](bool checked){
        if(checked)
            ui->password->setEchoMode(QLineEdit::Normal); // показываем пароль
        else
            ui->password->setEchoMode(QLineEdit::Password); // скрываем
    });

    connect(&socket, &QWebSocket::textMessageReceived,
            this, &MainWindow::onTextMessageReceived);
    ui->stackedWidget->setCurrentWidget(ui->pageLogin);

    networkManager = new QNetworkAccessManager(this);
    // connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onLoginReply);
    connect(
        ui->loginButton,
        &QPushButton::clicked,
        this,
        &MainWindow::onLoginClicked
        );


}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        if (ui->stackedWidget->currentWidget() == ui->pageLogin)
            ui->loginButton->click();
        else if (ui->stackedWidget->currentWidget() == ui->pageChat)
            ui->sendButton->click();
    }
    else
    {
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::sendLoginRequest(const QString& login, const QString& password)
{
     qDebug() << "sendLoginRequest";
    QUrl url("http://127.0.0.1:3000/login"); // Go-gateway
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;
    obj["login"] = login;
    obj["password"] = password;

    networkManager->post(request, QJsonDocument(obj).toJson());
}

void MainWindow::onLoginClicked()
{
    QString login = ui->login->text();
    QString password = ui->password->text();
    qDebug() << login << password;
    sendLoginRequest(login, password);
    ui->stackedWidget->setCurrentWidget(ui->pageChat);
    socket.open(QUrl("ws://127.0.0.1:3000/ws"));
}


void MainWindow::onConnected()
{
    qDebug() << "connected";
}

void MainWindow::appendMessage(const QString &html, Qt::Alignment align)
{
    QTextCursor cursor = ui->chatWindow->textCursor();
    cursor.movePosition(QTextCursor::End);

    QTextBlockFormat format;
    format.setAlignment(align);

    cursor.insertBlock(format);
    cursor.insertHtml(html);

    ui->chatWindow->setTextCursor(cursor);
}

void MainWindow::on_sendButton_clicked()
{
    QString text = ui->messageEdit->toPlainText().trimmed().toHtmlEscaped();
    qDebug() << text;
    if (text.isEmpty())
        return;

    QString time = QTime::currentTime().toString("HH:mm");

    appendMessage(
        "<font color='#7FFFD4'><b>Я:</b></font> "
        "<font color='#00FFFF'>" + text + "</font>",
        Qt::AlignRight
        );

    QJsonObject json;
    json["text"] = text;

    QJsonDocument doc(json);
    socket.sendTextMessage(doc.toJson(QJsonDocument::Compact));

    ui->messageEdit->clear();
}

void MainWindow::onTextMessageReceived(const QString &message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QString text = doc.object().value("text").toString().toHtmlEscaped();

    QString time = QTime::currentTime().toString("HH:mm");

    appendMessage(
        "<font color='#8FBC8F'><b>Сервер:</b></font> "
        "<font color='#00FF00'>" + text + "</font>",
        Qt::AlignLeft
        );

}

MainWindow::~MainWindow()
{
    delete ui;
}
