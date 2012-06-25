#ifndef QMLRENDERER_H
#define QMLRENDERER_H
#include "IResourceHandler.h"
#include <string>
#include <memory>
#include <map>

class QtService;
class QmlRenderer : public IResourceHandler
{
public:
    QmlRenderer();
    void setService(std::weak_ptr<QtService> service);
    void prepareRender(const std::string& qmlUrl);
    void paint(/* painting buffer pointer */);
    virtual void resourceNeeded(const std::string& url,
                                RequestArrivedCallback callback);
    virtual void resourceArrived(const std::string& url,
                                 const std::vector<char>& data);
protected:
    std::weak_ptr<QtService> m_service;
    typedef std::map<std::string, RequestArrivedCallback> CallbacksMap;
    CallbacksMap m_callbacks;
};

#endif // QMLRENDERER_H
