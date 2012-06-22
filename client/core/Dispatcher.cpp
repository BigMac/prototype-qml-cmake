#include "Dispatcher.h"
#include "events/Event.h"

Dispatcher::Dispatcher()
{
}

void Dispatcher::post(std::shared_ptr<const Event> event)
{
    event->executeCallbacks(shared_from_this());
}
