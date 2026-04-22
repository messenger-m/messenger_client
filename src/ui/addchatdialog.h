#ifndef ADDCHATDIALOG_H
#define ADDCHATDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;

class AddChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddChatDialog(QWidget *parent = nullptr);

    QString getName() const;

private:
    QLineEdit *nameEdit;

};

#endif
