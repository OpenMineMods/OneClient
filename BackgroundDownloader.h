#pragma once

#include <QtWidgets>

class BackgroundDownloader : public QThread
{
    Q_OBJECT
public:
    BackgroundDownloader(QObject *parent = NULL);
    void setTarget(const QString &url, const QString &path);

    void run() override;

signals:
    void downloadDone();

private:
    QString m_url;
    QString m_path;
};
