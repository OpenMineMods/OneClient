#include "DownloadUtil.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QObject>
#include <QFile>
#include <QDir>

DownloadUtil::DownloadUtil() {

}

void DownloadUtil::downloadFile(const QString &url, const QString &dest) {
    QNetworkAccessManager m_netMan;
    QNetworkReply *reply = m_netMan.get(QNetworkRequest(url));
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(m_downloadProgress(qint64,qint64)));
    loop.exec();
    QFile file(dest);
    file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
    delete reply;
}

void DownloadUtil::m_downloadProgress(qint64 bytesRecived, qint64 totalBytes) {
    emit(downloadProgress(bytesRecived, totalBytes));
}
