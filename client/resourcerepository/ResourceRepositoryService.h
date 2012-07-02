#ifndef RESOURCEREPOSITORYSERVICE_H
#define RESOURCEREPOSITORYSERVICE_H
#include "Service.h"
#include "events/EventRegistry.h"
#include <boost/msm/back/state_machine.hpp>
#include "ResourceRepositoryFsm.h"

class Dispatcher;

class ResourceRepositoryService :
        public Service,
        public boost::msm::back::state_machine<ResourceRepositoryFsm>,
        public std::enable_shared_from_this<ResourceRepositoryService>
{
public:
    ResourceRepositoryService(std::shared_ptr<Dispatcher> dispatcher);

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

#endif // RESOURCEREPOSITORYSERVICE_H
