#include "Service.h"
#include "Dispatcher.h"
#include "events/Event.h"
#include <algorithm>

Service::Service(std::shared_ptr<Dispatcher> dispatcher) :
    m_running(false), m_dispatcher(dispatcher)
{}

void Service::post(Service::EventConstSp event)
{
    m_queue.push(event);
}

void Service::run()
{
    auto thread = boost::thread([&]()
    {
    preRun();
    m_running = true;
    while(m_running)
    {
        EventConstSp event = m_queue.pop();
        if(event)
            handleEvent(event);
    }
    });
    thread.join();
}

void Service::stop()
{
    m_running = false;
}

void Service::submit(EventConstSp event)
{
    m_dispatcher->post(event);
}

