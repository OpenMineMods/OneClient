#include "utils.h"

Utils::Utils()
{

}

QString Utils::loadStyleSheet(QString name) {
    QFile stylesheet(":/style/main.qss");
    stylesheet.open(QFile::ReadOnly);
    // TODO: Preprocesssor
    return QString(stylesheet.readAll());
}
