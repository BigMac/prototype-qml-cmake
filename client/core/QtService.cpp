#include "QtService.h"
#include "Dispatcher.h"
#include "events/GuiResourceResponse.h"
#include "events/Event.h"

QtService::QtService(std::shared_ptr<Dispatcher> dispatcher) :
    Service(dispatcher), m_eventRegistry(std::make_shared<EventRegistry>())
{}

void QtService::registerReceivedEventTypes(std::shared_ptr<Dispatcher> dispatcher)
{
    dispatcher->registerReceiver<GuiResourceResponse>(*this);
}


uint32_t QtService::handleEvent(EventConstSp event)
{
    event->executeCallbacks(m_eventRegistry);
    return 10;
}

void QtService::preRun()
{
    start();
}
