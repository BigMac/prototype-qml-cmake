#ifndef EVENT_H
#define EVENT_H
#include "EventRegistry.h"
#include <algorithm>
#include <memory>

class Event
{
public:
    virtual ~Event() {}
    virtual void executeCallbacks(EventRegistry& registry) = 0;
};

template<typename Message_t>
class EventImplementation : public Event, public std::enable_shared_from_this<Message_t>
{
public:
    virtual void executeCallbacks(EventRegistry& registry)
    {
        auto callbacks = registry.Register<Message_t>::getCallbacks();
        for(auto i = callbacks.begin(); i != callbacks.end(); ++i)
        {
            (*i)(this->shared_from_this());
        }
    }
};

#endif // EVENT_H
