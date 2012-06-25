#ifndef QTSERVICE_H
#define QTSERVICE_H
#include "Service.h"
#include "ConcurrentQueue.h"
#include "events/EventRegistry.h"
#include <boost/msm/back/state_machine.hpp>

struct QtServiceFsm;
class Dispatcher;
class QtService :
        public Service,
        public std::enable_shared_from_this<QtService>
{
public:
    QtService(std::shared_ptr<Dispatcher> dispatcher);
    ~QtService();
    virtual void registerReceivedEventTypes(std::shared_ptr<Dispatcher> dispatcher);
protected:
    virtual uint32_t handleEvent(EventConstSp event);
    virtual void preRun();

    std::shared_ptr<EventRegistry> m_eventRegistry;
    typedef boost::msm::back::state_machine<QtServiceFsm> QtFsm;
    std::unique_ptr<QtFsm> m_fsm;
    friend class QtServiceFsm;

private:
};

#endif // QTSERVICE_H
