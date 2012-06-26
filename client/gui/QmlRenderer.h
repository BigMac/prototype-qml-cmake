#ifndef QMLRENDERER_H
#define QMLRENDERER_H
#include "IResourceHandler.h"
#include <string>
#include <memory>
#include <map>

class QtService;
class QApplication;
class QDeclarativeView;
class ViewLoadedListener;
class QmlRenderer : public IResourceHandler
{
public:
    QmlRenderer(int& argc, char**& argv);
    void setService(std::weak_ptr<QtService> service);
    void prepareRender(const std::string& qmlUrl);
    void paint(/* painting buffer pointer */);
    virtual void resourceNeeded(const std::string& url,
                                RequestArrivedCallback callback);
    virtual void resourceArrived(const std::string& url,
                                 const std::vector<char>& data);
    void allResourcesLoaded();
protected:
    std::weak_ptr<QtService> m_service;
    typedef std::map<std::string, RequestArrivedCallback> CallbacksMap;
    CallbacksMap m_callbacks;

    std::shared_ptr<QApplication> m_app;
    std::shared_ptr<QDeclarativeView> m_view;
    std::shared_ptr<ViewLoadedListener> m_listener;
};

#endif // QMLRENDERER_H
