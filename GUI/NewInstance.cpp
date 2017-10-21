#include "NewInstance.h"
#include "MainWindow.h"
#include "Utils.h"
#include <QFileDialog>

NewInstance::NewInstance(QWidget *parent) : QDialog(parent) {
    _ui.setupUi(this);
    setStyleSheet(Utils::loadStyleSheet("main"));

    QVectorIterator<QString> iter(MainWindow::vers.orderedVersions);
    while (iter.hasNext()) {
        _ui.mc_ver->addItem(iter.next());
    }
    _ui.icon_button->setStyleSheet(".QPushButton { border-image: url(:/icons/OpenMineMods.svg); }");
    connect(_ui.create, &QPushButton::clicked, this, &NewInstance::createInstance);
    connect(_ui.icon_button, &QPushButton::clicked, this, &NewInstance::setIcon);
}

void NewInstance::setIcon() {
    QFileDialog d;
    d.setFileMode(QFileDialog::ExistingFile);
    QStringList filter;
    filter << "*.png";
    filter << "*.jpg";
    filter << "*.jpeg";
    d.setNameFilters(filter);
    if (!d.exec()) return;
    QString image_file(d.selectedFiles().first());

    QFileInfo icon(image_file);

    QString icon_filename = MainWindow::cache_dir + "/icons/" + icon.fileName();
//    scaleImage(files.first());
    qDebug() << icon_filename;
}

void NewInstance::createInstance() {
    QDir().mkpath(MainWindow::data_dir + "/instances/" + _ui.instance_name->text());
    MinecraftInstance instance(_ui.instance_name->text());
    instance.setVersion(_ui.mc_ver->currentText(),_ui.forge_ver->currentText());
    done(1);
    return;
}
