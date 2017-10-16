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
    }

    QFile metaFile(cache_dir + "/meta.json");
    metaFile.open(QIODevice::ReadOnly);
    MainWindow::db.load(metaFile.readAll());
    populate_browse(MainWindow::db.search("*", CurseMetaDB::MODPACK));

    connect(_ui.pack_search_button, SIGNAL(clicked()), this, SLOT(search_changed()));
    connect(_ui.pack_search, SIGNAL(returnPressed()), this, SLOT(search_changed()));
}

void MainWindow::populate_browse(QList<CurseMetaDB::CurseProject> projects) {
    Utils::clearLayout(_ui.pack_box);
    QListIterator<CurseMetaDB::CurseProject> iter(projects);
    while (iter.hasNext()) {
        browse_widgets.append(new PackWidget(&iter.next()));
        _ui.pack_box->addWidget(browse_widgets[browse_widgets.length()-1]);
    }
    _ui.pack_box->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

void MainWindow::search_changed() {
    if (_ui.pack_search->text() == "") {
        populate_browse(MainWindow::db.search("*", CurseMetaDB::MODPACK));
    } else {
        populate_browse(MainWindow::db.search(_ui.pack_search->text(), CurseMetaDB::MODPACK));
    }
}
