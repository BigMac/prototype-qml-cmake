#include "LocalNetworkAccessManager.h"
#include "FileNetworkReply.h"
#include <QtNetwork/QNetworkRequest>
#include <QDebug>
#include <qglobal.h>

LocalNetworkAccessManager::LocalNetworkAccessManager(QObject *parent) :
    QNetworkAccessManager(parent)
{
}

QNetworkReply* LocalNetworkAccessManager::createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData)
{
    qDebug() << Q_FUNC_INFO;
    QUrl url = request.url();
    url = QUrl::fromLocalFile(url.host() + url.path());
    FileNetworkReply* reply(new FileNetworkReply(url, request));
    return reply;
}
