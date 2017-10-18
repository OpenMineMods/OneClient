#pragma once

#include <QtWidgets>
#include "ui_NewInstanceDialog.h"

class NewInstance : public QDialog {
    Q_OBJECT
public:
    NewInstance(QWidget *parent = NULL);

    Ui_NewInstanceDialog _ui;
};
