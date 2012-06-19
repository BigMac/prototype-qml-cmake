#include "NetworkAccessManager.h"
#include "RepositoryNetworkReply.h"
#include "core/ResourceRepository.h"
#include <QtNetwork/QNetworkRequest>
#include <QDebug>
#include <qglobal.h>

NetworkAccessManager::NetworkAccessManager(std::shared_ptr<ResourceRepository> repository, QObject *parent) :
    QNetworkAccessManager(parent), m_repository(repository)
{
}

QNetworkReply* NetworkAccessManager::createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData)
{
    qDebug() << Q_FUNC_INFO;
    if(op == GetOperation || op == PostOperation)
    {
        QUrl url = request.url();
        url = QUrl::fromLocalFile(url.host() + url.path());
        RepositoryNetworkReply* reply(new RepositoryNetworkReply(m_repository, url, request));
        return reply;
    }
    else
        return new QNetworkReply(this->parent());
}
