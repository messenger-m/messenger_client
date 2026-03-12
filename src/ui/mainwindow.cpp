#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString token, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    jwtToken(token)
{
    ui->setupUi(this);

    setWindowTitle("Messenger");
    resize(900, 600);

    ui->splitter->setSizes({250, 650});
    ui->chatList->addItem("Notes");
    ui->chatList->addItem("Alice");
    ui->chatList->addItem("Bob");
    ui->chatList->setCurrentRow(0);
    currentChat = "Notes";

    connect(ui->chatList, &QListWidget::itemClicked,
            this, [this](QListWidgetItem* item)
            {
                currentChat = item->text();

                ui->messageView->clear();

                for(const ChatMessage& msg : chats[currentChat])
                {
                    ui->messageView->addItem(msg.sender + ": " + msg.text);
                }
            });

    connect(ui->sendButton, &QPushButton::clicked,
            this, [this]()
            {
                QString text = ui->messageEdit->text();

                if(text.isEmpty())
                    return;

                ChatMessage msg;
                msg.sender = "You";
                msg.text = text;

                chats[currentChat].append(msg);

                ui->messageView->addItem("You: " + text);

                ui->messageView->scrollToBottom();

                ui->messageEdit->clear();
            });

    connect(ui->messageEdit,
            &QLineEdit::returnPressed,
            ui->sendButton,
            &QPushButton::click);

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
    padding: 10px;
    border-radius: 6px;
}

QListWidget::item:selected {
    background: #334155;
}

QTextEdit {
    background: #020617;
    border: none;
    color: white;
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
)");

}
MainWindow::~MainWindow()
{
    delete ui;
}


