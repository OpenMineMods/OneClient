#include "MainWindow.h"
#include "InitialSetup.h"
#include "PackWidget.h"
#include "InstanceWidget.h"
#include "Utils.h"
#include <iostream>
#include "FlowLayout.h"
#include <sys/stat.h>
#include <QStandardPaths>


MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {
    _ui.setupUi(this);

    setStyleSheet(Utils::loadStyleSheet("main"));
    QSettings settings(config_dir + "/oneclient.ini", QSettings::NativeFormat);

    if (!settings.value("setup_done", false).toBool()) {
        InitialSetupWindow w;
        w.exec();
    }

    fl = new FlowLayout;

    QFile metaFile(cache_dir + "/meta.json");
    metaFile.open(QIODevice::ReadOnly);
    MainWindow::db.load(metaFile.readAll());

    QStringList instanceFolders = QDir(MainWindow::data_dir + "/instances").entryList();
    QList<MinecraftInstance> instances;
    for (int i = 0; i < instanceFolders.length(); ++i) {
        if (instanceFolders[i] == "." || instanceFolders[i] == "..") continue;
        instances.append(MinecraftInstance(MainWindow::data_dir + "/instances/" + instanceFolders[i]));
    }
    populateInstances(instances);
    Utils::clearLayout(_ui.pack_box);
    populateBrowse(MainWindow::db.search("*", CurseMetaDB::MODPACK));
    connect(_ui.pack_search_button, &QPushButton::clicked, this, &MainWindow::searchChanged);
    connect(_ui.pack_search, &QLineEdit::returnPressed, this, &MainWindow::searchChanged);
    connect(_ui.pack_scroll->verticalScrollBar(), &QScrollBar::valueChanged, this, &MainWindow::scrollBrowse);

    _ui.scroll_box_w->setLayout(fl);

    ad_img.setStyleSheet(".QWidget { border-image: url(:/icons/ad.png) }");
    ad_img.setFixedSize(60, 40);
    ad_img.setParent(this);
}

void MainWindow::populateBrowse(QList<CurseMetaDB::CurseProject> projects) {
    MainWindow::page++;
    MainWindow::busy = true;
    QListIterator<CurseMetaDB::CurseProject> iter(projects);
    while (iter.hasNext()) {
        browse_widgets.append(new PackWidget(&iter.next()));
        _ui.pack_box->addWidget(browse_widgets[browse_widgets.length()-1]);
    }
    _ui.pack_box->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    MainWindow::busy = false;
}

void MainWindow::populateInstances(QList<MinecraftInstance> instances) {
    Utils::clearLayout(fl);

    QListIterator<MinecraftInstance> iter(instances);
    while (iter.hasNext()) {
        instance_widgets.append(new InstanceWidget(&iter.next()));
        fl->addWidget(instance_widgets[instance_widgets.length()-1]);
    }

    QWidget* addInstance = new QWidget();
    addInstance->setStyleSheet(".QWidget { border-image: url(:/icons/new_instance.svg) }");
    addInstance->setFixedSize(200, 200);
    addInstance->setToolTip("Create New Instance");
    fl->addWidget(addInstance);

}

void MainWindow::searchChanged() {
     Utils::clearLayout(_ui.pack_box);
    if (_ui.pack_search->text() == "") {
        populateBrowse(MainWindow::db.search("*", CurseMetaDB::MODPACK));
    } else {
        populateBrowse(MainWindow::db.search(_ui.pack_search->text(), CurseMetaDB::MODPACK));
    }
}

void MainWindow::resizeEvent(QResizeEvent*) {
    ad_img.move(this->width() - ad_img.width() - 10, 10);
}

const int pageIncrement = 25;
void MainWindow::scrollBrowse(int position) {
    if(!MainWindow::busy && position >= _ui.pack_scroll->verticalScrollBar()->maximum()) {
        int start = pageIncrement*MainWindow::page+1, end = start+pageIncrement-1;
        if (_ui.pack_search->text() == "") {
            populateBrowse(MainWindow::db.search("*", CurseMetaDB::MODPACK, start,end));
        } else {
            populateBrowse(MainWindow::db.search(_ui.pack_search->text(), CurseMetaDB::MODPACK, start,end));
        }
    }
}
