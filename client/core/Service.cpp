#include "Service.h"
#include "Dispatcher.h"
#include "events/Event.h"
#include <algorithm>

Service::Service(std::weak_ptr<Dispatcher> dispatcher) :
    m_running(false), m_dispatcher(dispatcher)
{}

void Service::post(Service::EventConstSp event)
{
    m_queue.push(event);
}

void Service::run()
{
    m_running = true;
    while(m_running)
    {
        EventConstSp event = m_queue.pop();
        if(event)
            handleEvent(event);
    }
}

void Service::stop()
{
    m_running = false;
}

void Service::submit(EventConstSp event)
{
    m_dispatcher.lock()->post(event);
}

