#pragma once

#include <QtWidgets>
#include <QWidget>
#include "ui_PackWidget.h"
#include "CurseMetaDB/CurseMetaDB.h"

class PackWidget : public QWidget {
public:
    PackWidget(const CurseMetaDB::CurseProject* project, QWidget* parent = 0);

    Ui_PackWidget _ui;
};
