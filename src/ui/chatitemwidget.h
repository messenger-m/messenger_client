#ifndef CHATITEMWIDGET_H
#define CHATITEMWIDGET_H

#include <QWidget>

class QLabel;

class ChatItemWidget : public QWidget
{
    Q_OBJECT

public:
    ChatItemWidget(QString name, QString lastMessage);
    void setLastMessage(const QString &msg);

private:
    QLabel* avatar;
    QLabel* title;
    QLabel* preview;
};

#endif // CHATITEMWIDGET_H
