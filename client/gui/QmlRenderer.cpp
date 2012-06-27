#include "QmlRenderer.h"
#include "QtService.h"
#include "QtServiceFsmEvents.h"
#include "NetworkAccessManager.h"
#include "ViewLoadedListener.h"
#include "ThreadSafeDeclarativeView.h"
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>
#include <QDeclarativeView>
#include <QtNetwork/QNetworkAccessManager>
#include <QApplication>
#include <QThread>
#include <sstream>
#include <stdexcept>

// TODO remove when done with print debugging
#include <iostream>

QmlRenderer::QmlRenderer(int &argc, char **&argv)
{
    //m_app = std::make_shared<QApplication>(argc, argv);
    m_view = std::make_shared<ThreadSafeDeclarativeView>();
    m_view->engine()->setNetworkAccessManagerFactory(new NetworkAccessManagerFactory(*this));
    m_listener = std::make_shared<ViewLoadedListener>([&](){ allResourcesLoaded(); });
    QDeclarativeView* view = m_view.get();
    ViewLoadedListener* listener = m_listener.get();
    QObject::connect(view, SIGNAL(statusChanged(QDeclarativeView::Status)),
                     listener, SLOT(statusChanged(QDeclarativeView::Status)));
}

void QmlRenderer::setService(std::weak_ptr<QtService> service)
{
    m_service = service;
}

void QmlRenderer::prepareRender(const std::string& qmlUrl)
{
    // All this is temporary
    bool success = QMetaObject::invokeMethod(m_view.get(),
                                             "loadResources",
                                             Qt::AutoConnection,
                                             Q_ARG(QUrl, QUrl(qmlUrl.c_str()))
                                             );
    //m_view->setSource(QUrl(qmlUrl.c_str()));
    //view.setVisible(true);
    //view.connect(view.engine(), SIGNAL(quit()), SLOT(close()));
    //m_view->show();
    std::cout << "prepareRender complete " << qmlUrl << " status " << success << std::endl;
    //m_view->show();
//    view.show();
//    app.exec();
}

void QmlRenderer::paint(/* painting buffer pointer */)
{

}

void QmlRenderer::allResourcesLoaded()
{
}

void QmlRenderer::resourceNeeded(const std::string& url,
                            RequestArrivedCallback callback)
{
    std::cout << "resource needed: " << url << std::endl;
    if(m_callbacks.find(url) != m_callbacks.end())
    {
        std::ostringstream errorMessage;
        errorMessage << "Callback for URL: " << url <<" already exists. "
                        "This resource was already requested. ";
        throw std::runtime_error(errorMessage.str());
    }
    m_callbacks[url] = callback;
    m_service.lock()->process_event(ResourceNeeded(url));
}


void QmlRenderer::resourceArrived(const std::string& url,
                             const std::vector<char>& data)
{
    std::cout << "resource arrived: " << url << std::endl;
    if(m_callbacks.find(url) == m_callbacks.end())
    {
        std::ostringstream errorMessage;
        errorMessage << "Callback for URL: " << url <<" not registered. "
                     << "I didn't request this resource.";
        throw std::runtime_error(errorMessage.str());
    }
    RequestArrivedCallback callback = m_callbacks[url];
    m_callbacks.erase(url);
    callback(url, data);
}
