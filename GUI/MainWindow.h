#pragma once

#include <QtWidgets>
#include "ui_MainWindow.h"
#include "FlowLayout.h"
#include "Minecraft/AuthSession.h"
#include "Minecraft/MinecraftInstance.h"
#include "Minecraft/MinecraftVersions.h"
#include "CurseMetaDB/CurseMetaDB.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:

    MainWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);

    Ui_MainWindow _ui;

    QString m_sSettingsFile;
    static AuthSession ses;

    static QString config_dir;
    static QString data_dir;
    static QString cache_dir;

    static CurseMetaDB db;

    static MinecraftVersions vers;

public slots:
    void searchChanged();
    void logout();
    void login();
    void valueChanged();
    void rescanInstances();
    void addInstance();
    void clearRam();

private:

    void populateBrowse(QVector<CurseMetaDB::CurseProject> projects);
    void populateInstances(QList<MinecraftInstance*> instances);
    void scrollBrowse(int position);

    QString conf_file;
    QList<QWidget*> browse_widgets;
    QList<QWidget*> instance_widgets;
    FlowLayout* fl;

    int page;
    bool busy;
};
