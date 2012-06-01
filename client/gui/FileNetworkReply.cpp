#include "FileNetworkReply.h"
#include <QDebug>
#include <QTimer>

FileNetworkReply::FileNetworkReply(QUrl url,
                           const QNetworkRequest &request,
                           QObject *parent) :
    QNetworkReply(parent), m_file(url.toLocalFile())
{
    setUrl(url);
    setRequest(request);
    setOpenMode(ReadOnly);
    m_file.open(ReadOnly);
    qDebug() << "File" << url.toLocalFile() << "exists:" << m_file.exists()
             << ",open:" << m_file.isOpen() <<",readable:" << m_file.isReadable()
             << ",bytes available:" << m_file.bytesAvailable();

    QTimer::singleShot( 0, this, SIGNAL(readyRead()) );
    QTimer::singleShot( 0, this, SIGNAL(finished()) );
}

void FileNetworkReply::abort()
{
}

qint64 FileNetworkReply::bytesAvailable() const
{
    return m_file.bytesAvailable();
}

bool FileNetworkReply::isSequential() const
{
    return true;
}

qint64 FileNetworkReply::readData(char *data, qint64 maxSize)
{
    qint64 ret = m_file.read(data, maxSize);
    if (ret == 0 && bytesAvailable() == 0)
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
