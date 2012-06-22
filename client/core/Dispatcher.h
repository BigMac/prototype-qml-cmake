#ifndef DISPATCHER_H
#define DISPATCHER_H
#include <memory>
#include "events/EventRegistry.h"

class Event;
class Dispatcher :
        public std::enable_shared_from_this<Dispatcher>,
        public EventRegistry
{
public:
    Dispatcher();
    virtual void post(std::shared_ptr<const Event> event);
};

#endif // DISPATCHER_H
