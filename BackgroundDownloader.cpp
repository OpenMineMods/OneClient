#include "BackgroundDownloader.h"
#include "DownloadUtil.h"

BackgroundDownloader::BackgroundDownloader(QObject *parent) : QThread(parent) {

}

void BackgroundDownloader::setTarget(const QString &url, const QString &path) {
    m_url = url;
    m_path = path;
}

void BackgroundDownloader::run() {
    DownloadUtil dl;
    dl.downloadFile(m_url, m_path);
    emit downloadDone();
}
