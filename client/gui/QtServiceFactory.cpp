#include "QtServiceFactory.h"
#include "QtService.h"
#include "QmlRenderer.h"

// static
std::shared_ptr<QtService> QtServiceFactory::create(
        std::shared_ptr<Dispatcher> dispatcher,
        int &argc,
        char **&argv)
{
    auto renderer = std::make_shared<QmlRenderer>(argc, argv);
    auto service = std::make_shared<QtService>(dispatcher, renderer);
    renderer->setService(service);
    return service;
}
