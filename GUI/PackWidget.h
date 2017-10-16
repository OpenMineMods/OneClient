#pragma once

#include <QtWidgets>
#include <QWidget>
#include "ui_PackWidget.h"
#include "CurseMetaDB/CurseMetaDB.h"
#include "BackgroundDownloader.h"

class PackWidget : public QWidget {
    Q_OBJECT
public:
    PackWidget(const CurseMetaDB::CurseProject* project, QWidget* parent = 0);

    Ui_PackWidget _ui;

public slots:
    void iconDownloaded();
    void moreClicked();

private:
    QString icon_filename;
    BackgroundDownloader dl;
    QUrl proj_url;
};
