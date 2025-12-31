#pragma once

#include <QMainWindow>
#include <QKeyEvent>

#include "authservice.h"
#include "chatclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void onLoginClicked();
    void onSendClicked();
    void onMessageReceived(const QString& text);

private:
    Ui::MainWindow *ui;
    AuthService* auth;
    ChatClient* chat;

    void appendMessage(const QString& html, Qt::Alignment align);
};
