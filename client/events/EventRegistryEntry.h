#ifndef EVENTREGISTRYENTRY_H
#define EVENTREGISTRYENTRY_H

#include "EventRegistry.h"
#include <memory>

template<typename Message_t>
class EventRegistryEntry
{
public:
    EventRegistryEntry(
            std::shared_ptr<EventRegistry> registry,
            Record<Message_t>::CallbackFunction callback) :
        m_registry(registry),
        m_callback(callback)
    {
        m_registry->Record<Message_t>::registerCallback(m_callback);
    }
    ~EventRegistryEntry()
    {
        m_registry->Record<Message_t>::deregisterCallback(m_callback);
    }

private:
    std::shared_ptr<EventRegistry> m_registry;
    Record<Message_t>::CallbackFunction m_callback;
};

#endif // EVENTREGISTRYENTRY_H
