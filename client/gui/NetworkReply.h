#ifndef NETWORKREPLY_H
#define NETWORKREPLY_H

#include <QtNetwork/QNetworkReply>
#include <QFile>
#include <vector>

class IResourceHandler;
class NetworkReply : public QNetworkReply
{
    Q_OBJECT
public:
    NetworkReply(
            IResourceHandler& resourceHandler,
            QUrl url,
            const QNetworkRequest &request,
            QObject *parent = 0);

    void abort();
    qint64 bytesAvailable() const;
    bool isSequential() const;

protected:
    void dataArrived(const std::string& url, const std::vector<char>& data);
    qint64 readData(char *data, qint64 maxSize);
    IResourceHandler& m_resourceHandler;
    std::vector<char> m_data;
    size_t m_dataIndex;
};

#endif // NETWORKREPLY_H
