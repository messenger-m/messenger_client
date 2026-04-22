#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QVector>
#include <QPushButton>


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

    QWidget *menu = nullptr;
    QWidget *overlay = nullptr;
    QPushButton *addChatButton = nullptr;

    bool menuOpened = false;

    bool dragging = false;
    QPoint dragStartPos;

    void loadChat(const QString& chatId);

    void addChat(QString name, QString lastMsg);

    void addMessage(QString text, bool isMe);
    void updateLastMessage(const QString& chat, const QString& msg);


    void toggleMenu();
    void animateMenu(int endX);

    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);





};
#endif // MAINWINDOW_H
