#include "QtService.h"
#include "QtServiceFsm.h"
#include "Dispatcher.h"
#include "events/Event.h"

#define REGISTER_INTERNAL_CALLBACK(EventType) \
        m_eventRegistry->Record<EventType>::registerCallback( \
                    [&](std::shared_ptr<const EventType> evt) { m_fsm->process_event(*evt); });

QtService::QtService(std::shared_ptr<Dispatcher> dispatcher) :
    m_eventRegistry(std::make_shared<EventRegistry>()),
    m_fsm(new QtFsm(dispatcher))
{
    REGISTER_INTERNAL_CALLBACK(GuiResourceResponse)
    REGISTER_INTERNAL_CALLBACK(OpenInterfaceWindowRequest)
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
    m_fsm->start();
}
