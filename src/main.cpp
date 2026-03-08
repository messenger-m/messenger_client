#include "ui/mainwindow.h"
#include "ui/loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow login;
    MainWindow mainWindow;

    QObject::connect(&login,
                     &LoginWindow::loginSuccess,
                     [&](QString token)
                     {
                         login.hide();
                         mainWindow.show();
                     });

    login.show();

    return a.exec();
}
