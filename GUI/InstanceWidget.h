#pragma once

#include <QtWidgets>
#include <QWidget>
#include "ui_InstanceWidget.h"
#include "Minecraft/MinecraftInstance.h"
#include "BackgroundDownloader.h"

class InstanceWidget : public QWidget {
    Q_OBJECT
public:
    InstanceWidget(const MinecraftInstance* instance, QWidget* parent = 0);

    void paintEvent(QPaintEvent *e);

    Ui_InstanceWidget _ui;
    QString icon_filename;
};
