#ifndef NETWORKACCESSMANAGER_H
#define NETWORKACCESSMANAGER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QDeclarativeNetworkAccessManagerFactory>
#include <QtNetwork/QNetworkReply>

class NetworkAccessManager : public QNetworkAccessManager
{
public:
    explicit NetworkAccessManager(QObject *parent = 0);
protected:
    QNetworkReply* createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData);

};

class NetworkAccessManagerFactory : public QDeclarativeNetworkAccessManagerFactory
{
public:
    QNetworkAccessManager* create(QObject *parent) { return new NetworkAccessManager(parent); }
};

#endif // NETWORKACCESSMANAGER_H
