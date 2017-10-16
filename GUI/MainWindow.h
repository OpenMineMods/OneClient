#pragma once

#include <QtWidgets>
#include "ui_MainWindow.h"
#include "CurseMetaDB/CurseMetaDB.h"

class MainWindow : public QMainWindow {
public:

    MainWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);

    Ui_MainWindow _ui;

    QString m_sSettingsFile;

    static QString config_dir;
    static QString data_dir;
    static QString cache_dir;

    static CurseMetaDB db;

private:

    void loadSettings();
    void saveSettings();

    QString conf_file;
};
