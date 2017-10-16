#include "PackWidget.h"

PackWidget::PackWidget(const CurseMetaDB::CurseProject* project, QWidget* parent) : QWidget(parent) {
    _ui.setupUi(this);

    _ui.pack_name->setText(project->title);
    _ui.pack_desc->setText(project->desc);
    _ui.pack_downloads->setText("Downloads: " + QString::number(project->downloads));

    QStringList authors;
    for (int i = 0; i < project->authors.size(); ++i) {
        authors.append(project->authors[i].toString());
    }

    _ui.pack_authors->setText("By " + authors.join(", "));
    _ui.pack_mcver->setText("Minecraft " + project->versions[project->versions.size() - 1].toString());
}
