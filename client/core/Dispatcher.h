#ifndef DISPATCHER_H
#define DISPATCHER_H
#include "IService.h"
#include "events/EventRegistry.h"
#include <memory>

class Event;
class Dispatcher :
        public std::enable_shared_from_this<Dispatcher>,
        public EventRegistry
{
public:
    Dispatcher();
    virtual void post(std::shared_ptr<const Event> event);
    template<typename EventType>
    void registerReceiver(IService& service)
    {
        Record<EventType>::registerCallback([&](std::shared_ptr<const EventType> event)
        {
            service.post(event);
        });
    }
};

#endif // DISPATCHER_H
