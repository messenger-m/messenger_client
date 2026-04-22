#include "chatitemwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

ChatItemWidget::ChatItemWidget(QString name, QString lastMessage)
{
    avatar = new QLabel;
    avatar->setFixedSize(40,40);
    avatar->setStyleSheet(R"(
        background:#3b82f6;
        border-radius:20px;
    )");

    title = new QLabel(name);
    title->setStyleSheet("color:white; font-weight:bold;");

    preview = new QLabel(lastMessage);
    preview->setStyleSheet("color:#94a3b8; font-size:12px;");

    QVBoxLayout* textLayout = new QVBoxLayout;
    textLayout->addWidget(title);
    textLayout->addWidget(preview);
    textLayout->setSpacing(2);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(avatar);
    layout->addLayout(textLayout);

    layout->setSpacing(10);
}
void ChatItemWidget::setLastMessage(const QString &msg)
{
    preview->setText(msg);
}
