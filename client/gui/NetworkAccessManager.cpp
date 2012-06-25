#include "NetworkAccessManager.h"
#include "NetworkReply.h"
#include <QtNetwork/QNetworkRequest>
#include <QDebug>
#include <qglobal.h>

NetworkAccessManager::NetworkAccessManager(QObject *parent) :
    QNetworkAccessManager(parent)
{
}

QNetworkReply* NetworkAccessManager::createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData)
{
    qDebug() << Q_FUNC_INFO;
    QUrl url = request.url();
    url = QUrl::fromLocalFile(url.host() + url.path());
    NetworkReply* reply(new NetworkReply(url, request));
    return reply;
}
