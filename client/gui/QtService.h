#ifndef QTSERVICE_H
#define QTSERVICE_H
#include "Service.h"
#include "events/EventRegistry.h"
#include <boost/msm/back/state_machine.hpp>
#include "QtServiceFsm.h"

class QmlRenderer;
class Dispatcher;
class QtService :
        public Service,
        public boost::msm::back::state_machine<QtServiceFsm>,
        public std::enable_shared_from_this<QtService>
{
public:
    QtService(std::shared_ptr<Dispatcher> dispatcher,
              std::shared_ptr<QmlRenderer> renderer);

    virtual void registerReceivedEventTypes(std::shared_ptr<Dispatcher> dispatcher);
protected:
    virtual uint32_t handleEvent(EventConstSp event);
    virtual void preRun();

    std::shared_ptr<EventRegistry> m_eventRegistry;

private:
    template<typename EventType>
    void registerInternalCallback()
    {
        m_eventRegistry->Record<EventType>::registerCallback( \
                    [&](std::shared_ptr<const EventType> evt) { process_event(*evt); });
    }
};

#endif // QTSERVICE_H
