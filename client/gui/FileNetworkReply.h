#ifndef NETWORKREPLY_H
#define NETWORKREPLY_H

#include <QtNetwork/QNetworkReply>
#include <QFile>

class FileNetworkReply : public QNetworkReply
{
    Q_OBJECT
public:
    FileNetworkReply(QUrl url, const QNetworkRequest &request, QObject *parent = 0);

    void abort();
    qint64 bytesAvailable() const;
    bool isSequential() const;

protected:
    qint64 readData(char *data, qint64 maxSize);
    QFile m_file;
};

#endif // NETWORKREPLY_H
