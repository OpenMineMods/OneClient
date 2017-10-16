#pragma once

#include <QString>
#include <QtWidgets>

class DownloadUtil : public QObject
{
    Q_OBJECT
public:
    DownloadUtil();

    void downloadFile(const QString &url, const QString &dest);

public slots:
    void m_downloadProgress(qint64 bytesRecived, qint64 totalBytes);

signals:
    void downloadProgress(qint64 bytesRecived, qint64 totalBytes);
};
