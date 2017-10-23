#pragma once

#include <QtWidgets>
#include <QSettings>
#include "ui_SetupDialog.h"

class InitialSetupWindow : public QDialog {
    Q_OBJECT
public:
    InitialSetupWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);

    void nextTab();
    int inf(FILE *source, FILE *dest);

    Ui_SetupDialog _ui;

public slots:
    void downloadProgress(qint64 bytesRecived, qint64 totalBytes);

private:
    QString conf_file;
};
