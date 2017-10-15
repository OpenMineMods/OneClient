#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QFile>

class Utils
{
public:
    static QString loadStyleSheet(QString name);

    static QString generateUUID();
};

#endif // UTILS_H
