#ifndef QMLRENDERER_H
#define QMLRENDERER_H
#include <string>
#include <memory>

class QtService;
class QmlRenderer
{
public:
    QmlRenderer();
    void setService(std::weak_ptr<QtService> service);
    void prepareRender(const std::string& qmlUrl);
    void paint(/* painting buffer pointer */);
protected:
    std::weak_ptr<QtService> m_service;
};

#endif // QMLRENDERER_H
