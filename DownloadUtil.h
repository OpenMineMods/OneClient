#pragma once

#include <QString>

class DownloadUtil
{
public:
    static void downloadFile(const QString &url, const QString &dest);
};
