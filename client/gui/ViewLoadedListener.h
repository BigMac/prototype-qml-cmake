#ifndef VIEWLOADEDLISTENER_H
#define VIEWLOADEDLISTENER_H

#include <QObject>
#include <QDeclarativeView>
#include <functional>

class ViewLoadedListener : public QObject
{
    Q_OBJECT
public:
    typedef std::function<void(void)> LoadingCompleteCallback;
    explicit ViewLoadedListener(LoadingCompleteCallback callback, QObject *parent = 0);
    
signals:
    
public slots:
    void statusChanged(QDeclarativeView::Status status);
protected:
    LoadingCompleteCallback m_callback;
};

#endif // VIEWLOADEDLISTENER_H
