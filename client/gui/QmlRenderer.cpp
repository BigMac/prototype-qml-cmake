#include "QmlRenderer.h"
#include "QtService.h"

QmlRenderer::QmlRenderer()
{
}

void QmlRenderer::setService(std::weak_ptr<QtService> service)
{
    m_service = service;
}

void QmlRenderer::prepareRender(const std::string& qmlUrl)
{

}

void QmlRenderer::paint(/* painting buffer pointer */)
{

}
