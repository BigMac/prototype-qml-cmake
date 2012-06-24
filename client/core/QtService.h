#ifndef QTSERVICE_H
#define QTSERVICE_H
#include "Service.h"
#include "ConcurrentQueue.h"
#include "QtServiceFsm.h"
#include <boost/msm/back/state_machine.hpp>

struct QtServiceFsm;
class Dispatcher;
class QtService :
        public Service,
        public std::enable_shared_from_this<QtService>
{
public:
    QtService(std::shared_ptr<Dispatcher> dispatcher);
    virtual void registerReceivedEventTypes(std::shared_ptr<Dispatcher> dispatcher);
protected:
    virtual uint32_t handleEvent(EventConstSp event);
    virtual void preRun();

    std::shared_ptr<EventRegistry> m_eventRegistry;
    typedef boost::msm::back::state_machine<QtServiceFsm> QtFsm;
    QtFsm m_fsm;

private:
    template<typename EventType>
    void registerInternalCallback()
    {
        m_eventRegistry->Record<EventType>::registerCallback(
                    [&](std::shared_ptr<const EventType> evt) { m_fsm.process_event(*evt); });
    }
};

#endif // QTSERVICE_H
