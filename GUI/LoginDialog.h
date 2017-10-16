#pragma once

#include <QtWidgets>
#include "ui_LoginDialog.h"

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    LoginDialog();

    Ui_LoginDialog _ui;

public slots:
    void loginClicked();
};
