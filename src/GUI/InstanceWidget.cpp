#include "InstanceWidget.h"
#include "MainWindow.h"
#include "Utils.h"
#include "BackgroundDownloader.h"

InstanceWidget::InstanceWidget(MinecraftInstance* instance, QWidget* parent) : QWidget(parent) {
    m_instance = instance;
    _ui.setupUi(this);

    _ui.instance_name->setText(instance->getName());

    icon_filename = MainWindow::cache_dir + "/icons/" + instance->getIcon();
    if (!Utils::fileExists(icon_filename)) {
        icon_filename = ":/icons/OpenMineMods.svg";
    }

    connect(_ui.play_button, &QToolButton::clicked, this, &InstanceWidget::launchClicked);
}

void InstanceWidget::launchClicked() {
    emit(instanceLaunching());
    m_instance->launch();
}

void InstanceWidget::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(icon_filename).scaled(size()));
    QWidget::paintEvent(e);
}
