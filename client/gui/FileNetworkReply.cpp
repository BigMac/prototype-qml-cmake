#include "FileNetworkReply.h"
#include <QDebug>

FileNetworkReply::FileNetworkReply(QUrl url,
                           const QNetworkRequest &request,
                           QObject *parent) :
    QNetworkReply(parent), m_file(url.toLocalFile())
{
    setUrl(url);
    setRequest(request);
    m_file.open(ReadOnly);
    qDebug() << "File" << url.toLocalFile() << "exists:" << m_file.exists();
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
    return m_file.isSequential();
}

qint64 FileNetworkReply::readData(char *data, qint64 maxSize)
{
    return m_file.read(data, maxSize);
}
