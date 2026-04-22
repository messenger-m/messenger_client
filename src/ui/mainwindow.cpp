#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chatitemwidget.h"
#include "messagebubble.h"
#include <QPropertyAnimation>
#include <QResizeEvent>
#include "addchatdialog.h"

MainWindow::MainWindow(QString token, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    jwtToken(token)
{
    ui->setupUi(this);

    setWindowTitle("Messenger");
    resize(900, 600);

    ui->splitter->setSizes({250, 650});

    ui->messageView->setSpacing(10);

    // // Чаты
    // addChat("Alice", "Hello!");
    // addChat("Bob", "How are you?");
    // addChat("Notes", "My notes");

    // // первый чат
    // ui->chatList->setCurrentRow(0);

    // currentChat =
    //     ui->chatList->item(0)->data(Qt::UserRole).toString();

    // connect(ui->addChat, )





    menu = new QWidget(ui->centralwidget);
    menu->setFixedWidth(200);
    menu->setStyleSheet("background:#1e293b;");
    menu->setGeometry(-menu->width(), 0,
                      menu->width(),
                      ui->centralwidget->height());

    QVBoxLayout *layout = new QVBoxLayout(menu);

    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(10);

    QPushButton *addChatButton = new QPushButton("Add chat");
    QPushButton *settingsButton = new QPushButton("Settings");

    layout->addWidget(addChatButton);
    layout->addWidget(settingsButton);
    layout->addStretch();


    overlay = new QWidget(ui->centralwidget);
    overlay->setGeometry(ui->centralwidget->rect());
    overlay->setStyleSheet("background:rgba(0,0,0,100);");
    overlay->hide();
    overlay->raise();

    overlay->installEventFilter(this);

    connect(ui->menuButton, &QToolButton::clicked, this, &MainWindow::toggleMenu);
    connect(addChatButton, &QPushButton::clicked, this, [this]() {

        AddChatDialog dialog(this);

        if (dialog.exec() == QDialog::Accepted)
        {
            QString name = dialog.getName();

            if (!name.isEmpty())
            {
                addChat(name, "Новый чат");
            }
        }
    });
    loadChat(currentChat);

    // Переключение чатов
    connect(ui->chatList, &QListWidget::itemClicked,
            this, [this](QListWidgetItem* item)
            {
                currentChat = item->data(Qt::UserRole).toString();
                loadChat(currentChat);
            });

    // Отправка сообщения
    connect(ui->sendButton, &QPushButton::clicked,
            this, [this]()
            {
                QString text = ui->messageEdit->text();

                if(text.isEmpty())
                    return;

                ChatMessage msg;
                msg.sender = "You";
                msg.text = text;

                if (!chats.contains(currentChat))
                {
                    qDebug() << "Chat not found:" << currentChat;
                    return;
                }

                chats[currentChat].append(msg);

                addMessage(text, true);
                updateLastMessage(currentChat, text);

                ui->messageEdit->clear();
                ui->messageEdit->setFocus();
            });

    // Enter отправляет сообщение
    connect(ui->messageEdit,
            &QLineEdit::returnPressed,
            ui->sendButton,
            &QPushButton::click);

    // стиль сообщений
    ui->messageView->setStyleSheet(R"(
QListWidget {
    background:#020617;
    border:none;
}
QListWidget::item {
    border:none;
}
)");

    // общий стиль
    setStyleSheet(R"(

QMainWindow {
    background-color: #0f172a;
}

QListWidget {
    background: #1e293b;
    border: none;
    color: white;
    padding: 6px;
    border-radius: 8px;
}

QListWidget::item {
    padding: 5px;
    border-radius: 6px;
}

QListWidget::item:selected {
    background: #334155;
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

QPushButton {
    background: #3b82f6;
    border-radius: 8px;
    color: white;
    padding: 8px 16px;
    font-weight: bold;
}

QPushButton:hover {
    background: #2563eb;
}

QToolButton {
    background: #3b82f6;
    border-radius: 8px;
    color: white;
    padding: 8px 16px;
    font-weight: bold;
}

QToolButton:hover {
    background: #2563eb;
}

)");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadChat(const QString& chatId)
{
    ui->messageView->clear();

    for(const ChatMessage& msg : chats[chatId])
    {
        bool isMe = msg.sender == "You";

        addMessage(msg.text, isMe);
    }

    ui->messageView->scrollToBottom();
}

void MainWindow::addChat(QString name, QString lastMsg)
{
    QListWidgetItem* item = new QListWidgetItem(ui->chatList);

    item->setData(Qt::UserRole, name);

    ChatItemWidget* widget =
        new ChatItemWidget(name, lastMsg);

    item->setSizeHint(widget->sizeHint());

    ui->chatList->addItem(item);
    ui->chatList->setItemWidget(item, widget);

    chats[name] = {};

    if (ui->chatList->count() == 1)
    {
        currentChat = name;
        ui->chatList->setCurrentItem(item);
        loadChat(name);
    }
}

void MainWindow::addMessage(QString text, bool isMe)
{
    QListWidgetItem* item =
        new QListWidgetItem(ui->messageView);

    MessageBubble* bubble =
        new MessageBubble(text, isMe);

    item->setSizeHint(bubble->sizeHint());

    ui->messageView->addItem(item);
    ui->messageView->setItemWidget(item, bubble);

    ui->messageView->scrollToBottom();
}

void MainWindow::updateLastMessage(const QString& chat, const QString& msg)
{
    for (int i = 0; i < ui->chatList->count(); ++i)
    {
        QListWidgetItem* item = ui->chatList->item(i);

        if (item->data(Qt::UserRole).toString() != chat)
            continue;

        auto widget = qobject_cast<ChatItemWidget*>(
            ui->chatList->itemWidget(item)
            );

        if (!widget)
            return;

        widget->setLastMessage(msg);

        // просто обновляем — БЕЗ перестановки
        return;
    }
}

void MainWindow::toggleMenu()
{
    if (menuOpened)
    {
        overlay->hide();
        animateMenu(-menu->width());
        menuOpened = false;
    }
    else
    {
        overlay->show();
        overlay->raise();
        menu->raise();

        animateMenu(0);
        menuOpened = true;
    }
}


void MainWindow::resizeEvent(QResizeEvent *event)
{

    overlay->setGeometry(ui->centralwidget->rect());

    if (!menuOpened)
        menu->move(-menu->width(), 0);
    else
        menu->setGeometry(0, 0, menu->width(), ui->centralwidget->height());

    QMainWindow::resizeEvent(event);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == overlay && event->type() == QEvent::MouseButtonPress)
    {
        if (menuOpened)
            toggleMenu();
        return true;
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::animateMenu(int endX)
{
    QPropertyAnimation *anim =
        new QPropertyAnimation(menu, "geometry", this);

    anim->setDuration(300);
    anim->setEasingCurve(QEasingCurve::OutCubic);

    QRect start = menu->geometry();
    QRect end(endX, 0, menu->width(), ui->centralwidget->height());

    anim->setStartValue(start);
    anim->setEndValue(end);

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragging = true;
        dragStartPos = event->globalPosition().toPoint();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (!dragging) return;

    int dx = event->globalPosition().toPoint().x() - dragStartPos.x();

    int x = qBound(-menu->width(), dx - menu->width(), 0);

    menu->setGeometry(x, 0, menu->width(), menu->height());
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (!dragging) return;
    dragging = false;

    int x = menu->x();

    if (x > -menu->width() / 2)
    {
        overlay->show();
        menuOpened = true;
        animateMenu(0);
    }
    else
    {
        overlay->hide();
        menuOpened = false;
        animateMenu(-menu->width());
    }
}

