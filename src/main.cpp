#include "ui/mainwindow.h"
#include "ui/loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow login;

    QObject::connect(&login,
                     &LoginWindow::loginSuccess,
                     [&](QString token)
                     {
                         MainWindow *mainWindow = new MainWindow(token);
                         mainWindow->show();
                         login.hide();
                     });

    login.show();

    return a.exec();
}
