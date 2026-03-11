#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "registerdialog.h"
#include "../grps/authclient.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setFixedSize(360, 420);
    setWindowTitle("Messenger Login");
    setStyleSheet(R"(
QWidget {
    background-color: #0f172a;
}

QLabel {
    color: white;
}

#titleLabel {
    font-size: 28px;
    font-weight: bold;
}

QLineEdit {
    background: #1e293b;
    border: 1px solid #334155;
    border-radius: 8px;
    padding: 8px;
    color: white;
}

QLineEdit:focus {
    border: 1px solid #3b82f6;
}

QPushButton#loginButton {
    background: #3b82f6;
    border-radius: 8px;
    color: white;
    font-weight: bold;
}

QPushButton#loginButton:hover {
    background: #2563eb;
}

QPushButton#registerButton {
    border-radius: 8px;
    color: #3b82f6;
}

QPushButton#registerButton:hover {
    color: #60a5fa;
}
)");

    connect(ui->loginButton, &QPushButton::clicked,
            this, &LoginWindow::onLoginClicked);

    connect(ui->registerButton, &QPushButton::clicked,
            this, [this]()
            {
                RegisterDialog dialog(this);
                dialog.exec();
            });
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::onLoginClicked()
{
    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();

    if(login.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Fill login and password");
        return;
    }

    AuthClient client(
        grpc::CreateChannel("localhost:50051",
                            grpc::InsecureChannelCredentials())
        );

    bool success = client.loginUser(
        login.toStdString(),
        password.toStdString()
        );
    if(success)
    {
        QMessageBox::information(this, "Success",
                                 QString::fromStdString("Success create User"));
    }
    else
    {
        QMessageBox::warning(this, "Error", "Invalid credentials");
    }
}
