#ifndef NETWORKACCESSMANAGER_H
#define NETWORKACCESSMANAGER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QDeclarativeNetworkAccessManagerFactory>
#include <QtNetwork/QNetworkReply>

class IResourceHandler;
class NetworkAccessManager : public QNetworkAccessManager
{
public:
    explicit NetworkAccessManager(IResourceHandler& resourceHandler, QObject *parent = 0);
protected:
    QNetworkReply* createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData);
    IResourceHandler& m_resourceHandler;

};

class NetworkAccessManagerFactory : public QDeclarativeNetworkAccessManagerFactory
{
public:
    NetworkAccessManagerFactory(IResourceHandler& resourceHandler) :
        m_resourceHandler(resourceHandler)
    {}
    QNetworkAccessManager* create(QObject *parent) { return new NetworkAccessManager(m_resourceHandler, parent); }
protected:
    IResourceHandler& m_resourceHandler;
};

#endif // NETWORKACCESSMANAGER_H
