#include "ViewLoadedListener.h"
#include <iostream>

ViewLoadedListener::ViewLoadedListener(
        LoadingCompleteCallback callback,
        QObject *parent) :
    QObject(parent),
    m_callback(callback)
{
}


void ViewLoadedListener::statusChanged(QDeclarativeView::Status status)
{
    std::cout << "ViewLoadedListener::statusChanged" << std::endl;
    if(status == QDeclarativeView::Ready)
        m_callback();
}
