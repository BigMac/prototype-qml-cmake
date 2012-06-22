#ifndef QTSERVICE_H
#define QTSERVICE_H
#include "Service.h"
#include "QtServiceFsm.h"
#include "ConcurrentQueue.h"
#include "events/EventRegistry.h"
#include <boost/msm/back/state_machine.hpp>

struct QtServiceFsm;
class Dispatcher;
class QtService :
        public Service,
        public boost::msm::back::state_machine<QtServiceFsm>,
        public std::enable_shared_from_this<QtService>
{
public:
    QtService(std::shared_ptr<Dispatcher> dispatcher);
    virtual void registerReceivedEventTypes(std::shared_ptr<Dispatcher> dispatcher);
protected:
    virtual uint32_t handleEvent(EventConstSp event) = 0;
    virtual void preRun();

    std::shared_ptr<EventRegistry> m_eventRegistry;

private:
    template<typename EventType>
    void registerInternalCallback()
    {
        m_eventRegistry->Record<EventType>::registerCallback(
                    [&](std::shared_ptr<const EventType> evt) { process_event(*evt); });
    }
};

#endif // QTSERVICE_H
