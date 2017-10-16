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

    static bool fileExists(QString path);

    static QString formatNumber(double number, int decimals=1);
};

#endif // UTILS_H
