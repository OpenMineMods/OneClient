#include "InstanceWidget.h"
#include "MainWindow.h"
#include "Utils.h"
#include "BackgroundDownloader.h"

InstanceWidget::InstanceWidget(const MinecraftInstance* instance, QWidget* parent) : QWidget(parent) {
    _ui.setupUi(this);

    _ui.instance_name->setText(instance->getName());

    icon_filename = MainWindow::cache_dir + "/icons/" + instance->getIcon();
    if (!Utils::fileExists(icon_filename)) {
        icon_filename = ":/icons/OpenMineMods.svg";
    }
}

void InstanceWidget::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(icon_filename).scaled(size()));
    QWidget::paintEvent(e);
}
