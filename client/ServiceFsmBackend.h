#ifndef SERVICEFSMBACKEND_H
#define SERVICEFSMBACKEND_H

#include "events/EventRegistry.h"
#include <boost/msm/back/state_machine.hpp>

template<typename ServiceFsm_t>
class ServiceFsmBackend :
        public boost::msm::back::state_machine<ServiceFsm_t>
{
public:
    std::shared_ptr<EventRegistry> getFsmEventRegistry();

    template<typename EventType>
    void registerInternalCallback()
    {
        m_eventRegistry->Record<EventType>::registerCallback( \
                    [&](std::shared_ptr<const EventType> evt) { process_event(*evt); });
    }
protected:
    std::shared_ptr<EventRegistry> m_eventRegistry;
};

#endif // SERVICEFSMBACKEND_H
