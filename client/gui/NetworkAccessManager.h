#ifndef NETWORKACCESSMANAGER_H
#define NETWORKACCESSMANAGER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QDeclarativeNetworkAccessManagerFactory>
#include <QtNetwork/QNetworkReply>
#include <memory>

class ResourceRepository;
class NetworkAccessManager : public QNetworkAccessManager
{
public:
    explicit NetworkAccessManager(std::shared_ptr<ResourceRepository> repo, QObject *parent = 0);
protected:
    QNetworkReply* createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData);
    std::shared_ptr<ResourceRepository> m_repository;
};

class NetworkAccessManagerFactory : public QDeclarativeNetworkAccessManagerFactory
{
public:
    NetworkAccessManagerFactory(std::shared_ptr<ResourceRepository> repo) : m_repository(repo) {}
    QNetworkAccessManager* create(QObject *parent) { return new NetworkAccessManager(parent); }
private:
    std::shared_ptr<ResourceRepository> m_repository;
};

#endif // NETWORKACCESSMANAGER_H
