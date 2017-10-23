#include "PackWidget.h"
#include "MainWindow.h"
#include "Utils.h"
#include "BackgroundDownloader.h"

PackWidget::PackWidget(const CurseMetaDB::CurseProject* project, QWidget* parent) : QWidget(parent) {
    proj_url = QUrl(project->page);
    _ui.setupUi(this);

    _ui.pack_name->setText(project->title);
    _ui.pack_desc->setText(project->desc);
    _ui.pack_downloads->setText("Downloads: " + Utils::formatNumber(project->downloads));

    QStringList authors;
    for (int i = 0; i < project->authors.size(); ++i) {
        authors.append(project->authors[i].toString());
    }

    _ui.pack_authors->setText("By " + authors.join(", "));
    _ui.pack_mcver->setText("Minecraft " + project->versions[project->versions.size() - 1].toString());

    connect(_ui.pack_more, &QPushButton::clicked, this, &PackWidget::moreClicked);

    icon_filename = MainWindow::cache_dir + "/icons/" + project->icon_name;
    if (Utils::fileExists(icon_filename)) {
        _ui.pack_icon->setStyleSheet(".QWidget { border-image: url(" + icon_filename + "); }");
    } else {
        _ui.pack_icon->setStyleSheet(".QWidget { border-image: url(:/icons/OpenMineMods.svg); }");
        if (project->icon_url != "") {
            dl.setTarget(project->icon_url, icon_filename);
            connect(&dl, &BackgroundDownloader::downloadDone, this, &PackWidget::iconDownloaded);
            dl.start();
        }
    }
}

void PackWidget::iconDownloaded() {
    Utils::scaleImage(icon_filename);
    _ui.pack_icon->setStyleSheet(".QWidget { border-image: url(" + icon_filename + "); }");
}

void PackWidget::moreClicked() {
    QDesktopServices::openUrl(proj_url);
}
