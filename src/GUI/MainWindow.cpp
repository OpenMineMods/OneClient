#include "MainWindow.h"
#include "InitialSetup.h"
#include "PackWidget.h"
#include "InstanceWidget.h"
#include "NewInstance.h"
#include "Minecraft/Yggdrasil.h"
#include "Utils.h"
#include <iostream>
#include "FlowLayout.h"
#include <sys/stat.h>
#include <QStandardPaths>
#include "getMemorySize.h"
#include "InstanceWindow.h"

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

    MainWindow::vers.loadFromFile(cache_dir + "/minecraft.json");

    ses.loadFromFile(MainWindow::data_dir + "/auth.dat");

    if (!ses.is_valid) {
        _ui.button_logout->hide();
    } else {
        _ui.button_login->hide();
        _ui.login_username->hide();
        _ui.login_password->hide();
        _ui.login_label->setText("Logged in as " + ses.profile.name);
    }

    _ui.max_ram->setMaximum(getMemorySize() / MEGABYTE);
    _ui.min_ram->setMaximum(getMemorySize() / MEGABYTE);

    _ui.min_ram->setValue(settings.value("java/min_ram", 512).toInt());
    _ui.max_ram->setValue(settings.value("java/max_ram", 4096).toInt());
    _ui.min_ram->setMaximum(_ui.max_ram->value());

    connect(_ui.min_ram, &QSpinBox::editingFinished, this, &MainWindow::valueChanged);
    connect(_ui.max_ram, &QSpinBox::editingFinished, this, &MainWindow::valueChanged);

    connect(_ui.button_logout, &QPushButton::clicked, this, &MainWindow::logout);
    connect(_ui.button_login, &QPushButton::clicked, this, &MainWindow::login);

    rescanInstances();
    Utils::clearLayout(_ui.pack_box);
    populateBrowse(MainWindow::db.search("*", CurseMetaDB::MODPACK));
    connect(_ui.pack_search_button, &QPushButton::clicked, this, &MainWindow::searchChanged);
    connect(_ui.pack_search, &QLineEdit::returnPressed, this, &MainWindow::searchChanged);

    _ui.scroll_box_w->setLayout(fl);
}

void MainWindow::clearRam() {
    qInfo() << "Clearing up RAM for Minecraft";
    browse_widgets.clear();
    Utils::clearLayout(_ui.pack_box);
}

void MainWindow::populateBrowse(QVector<CurseMetaDB::CurseProject> projects) {
    browse_widgets.clear();
    Utils::clearLayout(_ui.pack_box);
    QVectorIterator<CurseMetaDB::CurseProject> iter(projects);
    while (iter.hasNext()) {
        browse_widgets.append(new PackWidget(&iter.next()));
        _ui.pack_box->addWidget(browse_widgets[browse_widgets.length()-1]);
    }
    _ui.pack_box->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

void MainWindow::rescanInstances() {
    QStringList instanceFolders = QDir(MainWindow::data_dir + "/instances").entryList();
    QList<MinecraftInstance*> instances;
    for (int i = 0; i < instanceFolders.length(); ++i) {
        if (instanceFolders[i] == "." || instanceFolders[i] == "..") continue;
        instances.append(new MinecraftInstance(instanceFolders[i]));
    }

    Utils::clearLayout(fl);

    QMutableListIterator<MinecraftInstance*> iter(instances);
    while (iter.hasNext()) {
        instance_widgets.append(new InstanceWidget(iter.next()));
        connect(instance_widgets[instance_widgets.length()-1], SIGNAL(instanceLaunching()), this, SLOT(clearRam()));
        fl->addWidget(instance_widgets[instance_widgets.length()-1]);
    }

    QPushButton* makeInstance = new QPushButton();
    // Apparently 192 is 200. ¯\_(ツ)_/¯
    makeInstance->setStyleSheet(".QPushButton { border-image: url(:/icons/new_instance.svg); width: 192px; height: 192px; }");
    makeInstance->setToolTip("Create New Instance");
    connect(makeInstance, &QPushButton::clicked, this, &MainWindow::addInstance);
    instance_widgets.append(makeInstance);
    fl->addWidget(instance_widgets[instance_widgets.length()-1]);

}

void MainWindow::addInstance() {
    NewInstance dia;
    dia.exec();
    rescanInstances();
}

void MainWindow::searchChanged() {
    Utils::clearLayout(_ui.pack_box);
    if (_ui.pack_search->text() == "") {
        populateBrowse(MainWindow::db.search("*", CurseMetaDB::MODPACK));
    } else {
        populateBrowse(MainWindow::db.search(_ui.pack_search->text(), CurseMetaDB::MODPACK));
    }
}

void MainWindow::logout() {
    ses.is_valid = false;
    ses.access_token = "";
    ses.client_token = "";
    ses.profile.id = "";
    ses.profile.name = "";
    ses.profile.legacy = false;
    ses.writeToFile(MainWindow::data_dir + "/auth.dat");

    _ui.button_login->show();
    _ui.login_username->show();
    _ui.login_password->show();
    _ui.login_label->setText("Log in with your Minecraft account");
    _ui.button_logout->hide();
}

void MainWindow::login() {
    ses = Yggdrasil::login(_ui.login_username->text(), _ui.login_password->text());
    _ui.login_password->clear();
    if (!ses.is_valid) {
        _ui.login_label->setText("Invalid Username/Password!");
        return;
    }
    ses.writeToFile(MainWindow::data_dir + "/auth.dat");
    _ui.button_login->hide();
    _ui.button_logout->show();
    _ui.login_username->clear();
    _ui.login_username->hide();
    _ui.login_password->hide();
    _ui.login_label->setText("Logged in as " + ses.profile.name);
}

void MainWindow::valueChanged() {
    QSettings settings(config_dir + "/oneclient.ini", QSettings::NativeFormat);

    _ui.min_ram->setMaximum(_ui.max_ram->value());
    settings.setValue("java/min_ram", _ui.min_ram->value());
    settings.setValue("java/max_ram", _ui.max_ram->value());
}
