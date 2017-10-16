#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QFile>
#include <QLayout>

class Utils
{
public:
    static QString loadStyleSheet(QString name);

    static QString generateUUID();

    static void clearLayout(QLayout *layout);
};

#endif // UTILS_H
