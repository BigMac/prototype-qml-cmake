#include "RepositoryNetworkReply.h"
#include "core/ResourceRepository.h"
#include "messages/ResourceResponse.h"
#include <QDebug>
#include <QTimer>
#include <functional>

RepositoryNetworkReply::RepositoryNetworkReply(ResourceRepository& repository,
                                               QUrl url,
                                               const QNetworkRequest &request,
                                               QObject *parent) :
    QNetworkReply(parent), m_file(url.toLocalFile())
{
    setUrl(url);
    setRequest(request);
    repository.requestResource(url.path(), std::bind(&RepositoryNetworkReply::responseReceived,
                                                     this,
                                                     std::placeholders::_1));
    setOpenMode(ReadOnly);
    qDebug() << "File" << url.toLocalFile() << "exists:" << m_file.exists()
             << ",open:" << m_file.isOpen() <<",readable:" << m_file.isReadable()
             << ",bytes available:" << m_file.bytesAvailable();
}

void RepositoryNetworkReply::responseReceived(const ResourceResponse &response)
{
    qDebug() << "Response received";
    m_data = response.getData();
    m_bytesRead = 0;
    QTimer::singleShot( 0, this, SIGNAL(readyRead()) );
    QTimer::singleShot( 0, this, SIGNAL(finished()) );
}

void RepositoryNetworkReply::abort()
{
}

qint64 RepositoryNetworkReply::bytesAvailable() const
{
    return m_data.size();
}

bool RepositoryNetworkReply::isSequential() const
{
    return true;
}

qint64 RepositoryNetworkReply::readData(char *data, qint64 maxSize)
{
    qint64 sizeRead = std::min(maxSize, bytesAvailable());
    data = &m_data[m_bytesRead];
    m_bytesRead += sizeRead;
    if (sizeRead == 0 && bytesAvailable() == 0)
    {
        QTimer::singleShot( 0, this, SIGNAL(finished()) );
        return -1;
    }
    else
    {
        QTimer::singleShot( 0, this, SIGNAL(readyRead()) );
        return ret;
    }
}
