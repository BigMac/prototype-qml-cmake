#include "QtService.h"
#include "Dispatcher.h"
#include "events/Event.h"

QtService::QtService(std::shared_ptr<Dispatcher> dispatcher,
                     std::shared_ptr<QmlRenderer> renderer) :
    boost::msm::back::state_machine<QtServiceFsm>(dispatcher, renderer),
    m_eventRegistry(std::make_shared<EventRegistry>())
{
    registerInternalCallback<GuiResourceResponse>();
    registerInternalCallback<OpenInterfaceWindowRequest>();
}

QtService::~QtService()
{
    // Empty implementation needed so that std::unique_ptr has complete type
}

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
