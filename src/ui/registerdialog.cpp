#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "../grps/authclient.h"
#include <QMessageBox>

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);

    connect(ui->registerButton,
            &QPushButton::clicked,
            this,
            &RegisterDialog::onRegisterClicked);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::onRegisterClicked()
{
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();
    QString confirmPassword = ui->confirmPasswordEdit->text();

    if(username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Fill all fields");
        return;
    }

    if(password != confirmPassword)
    {
        QMessageBox::warning(this, "Error", "Passwords do not match");
        return;
    }

    AuthClient client(
        grpc::CreateChannel("localhost:50051",
                            grpc::InsecureChannelCredentials())
        );

    std::string message;

    bool success = client.registerUser(
        username.toStdString(),
        password.toStdString(),
        message
        );

    if(success)
    {
        QMessageBox::information(this, "Success",
                                 QString::fromStdString(message));
        accept();
    }
    else
    {
        QMessageBox::warning(this, "Error",
                             QString::fromStdString(message));
    }
}
