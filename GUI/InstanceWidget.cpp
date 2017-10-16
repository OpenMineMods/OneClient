#include "InstanceWidget.h"
#include "MainWindow.h"
#include "Utils.h"
#include "BackgroundDownloader.h"

InstanceWidget::InstanceWidget(const MinecraftInstance* instance, QWidget* parent) : QWidget(parent) {
    _ui.setupUi(this);

    /*QString icon_filename = MainWindow::cache_dir + "/icons/" + instance->getIcon();
    if (Utils::fileExists(icon_filename)) {
        this->setStyleSheet(".QWidget { border-image: url(" + icon_filename + "); }");
    } else {
        this.pack_icon->setStyleSheet(".QWidget { border-image: url(:/icons/OpenMineMods.svg); }");
    }*/
}
