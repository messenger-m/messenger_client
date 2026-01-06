#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextCursor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    auth(new AuthService(this)),
    chat(new ChatClient(this))
{
    ui->setupUi(this);

    ui->password->setEchoMode(QLineEdit::Password);

    ui->toggleButton->setCheckable(true);
    ui->toggleButton->setText("👁");

    connect(ui->toggleButton, &QPushButton::toggled,
            this, [=](bool checked){
                ui->password->setEchoMode(
                    checked ? QLineEdit::Normal : QLineEdit::Password
                    );
            });

    connect(ui->loginButton, &QPushButton::clicked,
            this, &MainWindow::onLoginClicked);

    connect(ui->sendButton, &QPushButton::clicked,
            this, &MainWindow::onSendClicked);

    // connect(auth, &AuthService::loginSuccess, this, [=]() {
    //     ui->stackedWidget->setCurrentWidget(ui->pageChat);
    //     chat->connectToServer();
    //     ui->isSuccess->setText("Login Success");
    // });

    connect(auth, &AuthService::loginError, this,
            [=](const QString& message) {

                ui->isSuccess->setText(
                    QString("<font color='#ff0000'><b>"
                            "%1<br>"
                            "</b></font>")
                        .arg(message)
                    );
            });

    connect(chat, &ChatClient::messageReceived,
            this, &MainWindow::onMessageReceived);

    ui->stackedWidget->setCurrentWidget(ui->pageLogin);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        if (ui->stackedWidget->currentWidget() == ui->pageLogin)
            ui->loginButton->click();
        else
            ui->sendButton->click();
    }
    else
    {
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::onLoginClicked()
{
    auth->login(
        ui->login->text(),
        ui->password->text()
        );
}

void MainWindow::onSendClicked()
{
    QString text = ui->messageEdit->toPlainText().trimmed();
    if (text.isEmpty())
        return;

    appendMessage(
        "<font color='#7FFFD4'><b>Я:</b></font> "
        "<font color='#00FFFF'>" + text.toHtmlEscaped() + "</font>",
        Qt::AlignRight
        );

    chat->sendMessage(text);
    ui->messageEdit->clear();
}

void MainWindow::onMessageReceived(const QString& text)
{
    QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8());
    QString msg = doc.object().value("text").toString();

    appendMessage(
        "<font color='#8FBC8F'><b>Сервер:</b></font> "
        "<font color='#00FF00'>" + text.toHtmlEscaped() + "</font>",
        Qt::AlignLeft
        );
}

void MainWindow::appendMessage(const QString& html, Qt::Alignment align)
{
    QTextCursor cursor = ui->chatWindow->textCursor();
    cursor.movePosition(QTextCursor::End);

    QTextBlockFormat format;
    format.setAlignment(align);

    cursor.insertBlock(format);
    cursor.insertHtml(html);
    ui->chatWindow->setTextCursor(cursor);
}
