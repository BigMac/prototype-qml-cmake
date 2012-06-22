#include "Service.h"
#include "Dispatcher.h"
#include "events/Event.h"
#include <algorithm>

Service::Service(std::weak_ptr<Dispatcher> dispatcher) :
    m_running(false), m_dispatcher(dispatcher)
{}

Service::Service() :
    m_running(false)
{}

void Service::post(Service::EventConstSp event)
{
    boost::mutex::scoped_lock(m_queueMutex);
    m_queue.push_back(event);
}

void Service::run()
{
    m_running = true;
    while(m_running)
    {
        EventConstSp event = tryPopEvent();
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

Service::EventConstSp Service::tryPopEvent()
{
    boost::mutex::scoped_lock(m_queueMutex);
    auto beginIter = m_queue.begin();
    if(beginIter == m_queue.end())
        return EventConstSp(); // Nothing on the queue
    EventConstSp result = *beginIter;
    m_queue.pop_front();
    return result;
}
