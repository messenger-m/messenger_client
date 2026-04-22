#include "addchatdialog.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

AddChatDialog::AddChatDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Добавить контакт");
    setFixedSize(300, 150);

    QVBoxLayout *layout = new QVBoxLayout(this);

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Введите имя");

    QPushButton *okBtn = new QPushButton("Добавить", this);

    layout->addWidget(nameEdit);
    layout->addWidget(okBtn);

    connect(okBtn, &QPushButton::clicked, this, &QDialog::accept);
}

QString AddChatDialog::getName() const
{
    return nameEdit->text();
}
