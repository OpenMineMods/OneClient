#pragma once

#include <QtWidgets>
#include <QWidget>
#include "ui_InstanceWidget.h"
#include "Minecraft/MinecraftInstance.h"
#include "BackgroundDownloader.h"

class InstanceWidget : public QWidget {
    Q_OBJECT
public:
    InstanceWidget(MinecraftInstance* instance, QWidget* parent = 0);

    void paintEvent(QPaintEvent *e);

    Ui_InstanceWidget _ui;
    QString icon_filename;

private slots:
    void launchClicked();

signals:
    void instanceLaunching();

private:
    MinecraftInstance* m_instance;
};
