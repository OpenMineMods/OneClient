#include "PackWidget.h"

PackWidget::PackWidget(const CurseMetaDB::CurseProject* project, QWidget* parent) : QWidget(parent) {
    _ui.setupUi(this);

    _ui.pack_name->setText(project->title);
    _ui.pack_desc->setText(project->desc);
    _ui.pack_downloads->setText("Downloads: " + QString::number(project->downloads));
}
