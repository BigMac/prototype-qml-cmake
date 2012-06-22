#ifndef ISERVICE_H
#define ISERVICE_H
#include <memory>

class Event;
class EventRegistry;
class IService
{
public:
    virtual void post(std::shared_ptr<const Event> event) = 0;
    virtual void run() = 0;
    virtual void registerEventCallbacks(EventRegistry& registry) = 0;
};

#endif // ISERVICE_H
