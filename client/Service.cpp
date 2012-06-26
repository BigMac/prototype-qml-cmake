#include "Service.h"
#include "Dispatcher.h"
#include "events/Event.h"
#include <algorithm>

Service::Service() :
    m_running(false)
{}

void Service::post(Service::EventConstSp event)
{
    m_queue.push(event);
}

void Service::run()
{
    m_thread = boost::thread([&]()
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
}

void  Service::join()
{
    m_thread.join();
}

void Service::stop()
{
    m_running = false;
}

