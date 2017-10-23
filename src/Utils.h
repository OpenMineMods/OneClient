#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QFile>
#include <QLayout>

#if defined(Q_OS_WIN)
    const static QString OS_NAME = "windows";
#elif defined(Q_OS_MACOS)
    const static QString OS_NAME = "osx";
#elif defined(Q_OS_LINUX)
    const static QString OS_NAME = "linux";
#else
    const static QString OS_NAME = "unknown";
#endif

class Utils
{
public:
    static QString loadStyleSheet(QString name);

    static QString generateUUID();

    static void clearLayout(QLayout *layout);

    static bool fileExists(QString path);

    static QString formatNumber(double number, int decimals=1);

    static void scaleImage(QString icon_filename, int scaleX = 128, int scaleY = 128);
};

#endif // UTILS_H
