#include "MainWindow.h"
#include "InitialSetup.h"
#include "PackWidget.h"
#include "utils.h"
#include <iostream>
#include <sys/stat.h>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {
    _ui.setupUi(this);

    QString style = Utils::loadStyleSheet("main");
    this->setStyleSheet(style);

    QSettings settings(config_dir + "/oneclient.ini", QSettings::NativeFormat);

    if (!settings.value("setup_done", false).toBool()) {
        InitialSetupWindow w;
        w.exec();
    }

    QFile metaFile(cache_dir + "/meta.json");
    metaFile.open(QIODevice::ReadOnly);
    MainWindow::db.load(metaFile.readAll());
    populateBrowse(MainWindow::db.search("*", CurseMetaDB::MODPACK));

    connect(_ui.pack_search_button, &QPushButton::clicked, this, &MainWindow::searchChanged);
    connect(_ui.pack_search, &QLineEdit::returnPressed, this, &MainWindow::searchChanged);

    ad_img.setStyleSheet(".QWidget { border-image: url(:/icons/ad.png) }");
    ad_img.setFixedSize(60, 40);
    ad_img.setParent(this);
}

void MainWindow::populateBrowse(QList<CurseMetaDB::CurseProject> projects) {
    Utils::clearLayout(_ui.pack_box);
    QListIterator<CurseMetaDB::CurseProject> iter(projects);
    while (iter.hasNext()) {
        browse_widgets.append(new PackWidget(&iter.next()));
        _ui.pack_box->addWidget(browse_widgets[browse_widgets.length()-1]);
    }
    _ui.pack_box->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

void MainWindow::searchChanged() {
    if (_ui.pack_search->text() == "") {
        populateBrowse(MainWindow::db.search("*", CurseMetaDB::MODPACK));
    } else {
        populateBrowse(MainWindow::db.search(_ui.pack_search->text(), CurseMetaDB::MODPACK));
    }
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    ad_img.move(this->width() - ad_img.width() - 10, 10);
}
