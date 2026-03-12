#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct ChatMessage
{
    QString sender;
    QString text;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString token, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString jwtToken;

    QString currentChat;

    QMap<QString, QVector<ChatMessage>> chats;
};
#endif // MAINWINDOW_H
