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

    setStyleSheet(R"(
QMainWindow {
    background-color: #0f172a;
}

QListWidget {
    background: #1e293b;
    border: none;
    color: white;
    padding: 6px;
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
