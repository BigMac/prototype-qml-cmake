#include "NetworkReply.h"
#include "IResourceHandler.h"
#include <QDebug>
#include <QTimer>
#include <functional>

NetworkReply::NetworkReply(IResourceHandler &resourceHandler,
                           QUrl url,
                           const QNetworkRequest &request,
                           QObject *parent) :
    QNetworkReply(parent),
    m_resourceHandler(resourceHandler),
    m_dataIndex(0)
{
    setUrl(url);
    setRequest(request);
    setOpenMode(ReadOnly);
    m_resourceHandler.resourceNeeded(std::string(url.path().toUtf8().constData()),
                                     std::bind(&NetworkReply::dataArrived,
                                               this,
                                               std::placeholders::_1,
                                               std::placeholders::_2));

}

void NetworkReply::dataArrived(const std::string& url, const std::vector<char>& data)
{
    qDebug() << "NetworkReply::dataArrived";
    m_data = data;
    QTimer::singleShot( 0, this, SIGNAL(readyRead()) );
    QTimer::singleShot( 0, this, SIGNAL(finished()) );
}

void NetworkReply::abort()
{
}

qint64 NetworkReply::bytesAvailable() const
{
    return m_data.size() - m_dataIndex;
}

bool NetworkReply::isSequential() const
{
    return true;
}

qint64 NetworkReply::readData(char *data, qint64 maxSize)
{
    qint64 bytesRead = std::min(bytesAvailable(), maxSize);
    if (bytesRead == 0 && bytesAvailable() == 0)
    {
        QTimer::singleShot( 0, this, SIGNAL(finished()) );
        return -1;
    }
    else
    {
        data = &m_data[m_dataIndex];
        m_dataIndex += bytesRead;
        QTimer::singleShot( 0, this, SIGNAL(readyRead()) );
        return bytesRead;
    }
}
