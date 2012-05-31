#ifndef NETWORKACCESSMANAGER_H
#define NETWORKACCESSMANAGER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QDeclarativeNetworkAccessManagerFactory>
#include <QtNetwork/QNetworkReply>

class LocalNetworkAccessManager : public QNetworkAccessManager
{
public:
    explicit LocalNetworkAccessManager(QObject *parent = 0);
protected:
    QNetworkReply* createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData);
    
};

class LocalNetworkAccessManagerFactory : public QDeclarativeNetworkAccessManagerFactory
{
public:
    QNetworkAccessManager* create(QObject *parent) { return new LocalNetworkAccessManager(parent); }
};

#endif // NETWORKACCESSMANAGER_H
