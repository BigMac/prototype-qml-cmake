#ifndef NETWORKREPLY_H
#define NETWORKREPLY_H

#include <QtNetwork/QNetworkReply>
#include <QFile>
#include <vector>

class ResourceRepository;
class ResourceResponse;
class RepositoryNetworkReply : public QNetworkReply
{
    Q_OBJECT
public:
    RepositoryNetworkReply(ResourceRepository& connection,
                           QUrl url,
                           const QNetworkRequest &request,
                           QObject *parent = 0);

    void abort();
    qint64 bytesAvailable() const;
    bool isSequential() const;

protected:
    void responseReceived(const ResourceResponse& response);
    qint64 readData(char *data, qint64 maxSize);
    std::vector<char> m_data;
    size_t m_bytesRead;
};

#endif // NETWORKREPLY_H
