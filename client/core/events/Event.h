#pragma once
#include "EventRegistry.h"
#include <algorithm>
#include <memory>

class Event
{
public:
    virtual ~Event() {}
    virtual bool executeCallbacks(std::shared_ptr<EventRegistry> registry) const = 0;
};

template<typename Message_t>
class EventImplementation : public Event, public std::enable_shared_from_this<Message_t>
{
public:
    virtual bool executeCallbacks(std::shared_ptr<EventRegistry> registry) const
    {
        auto callbacks = registry->Record<Message_t>::getCallbacks();
        for(auto i = callbacks.begin(); i != callbacks.end(); ++i)
        {
            (*i)(this->shared_from_this());
        }
        return !callbacks.empty();
    }
};
