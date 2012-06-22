#ifndef SERVICE_H
#define SERVICE_H
#include "IService.h"
#include <cstdint>
#include <boost/circular_buffer.hpp>
#include <boost/thread.hpp>

class Dispatcher;
class Service : public IService
{
public:
    Service();
    Service(std::weak_ptr<Dispatcher> dispatcher);
    typedef std::shared_ptr<const Event> EventConstSp;
    virtual void post(EventConstSp event);
    virtual void run();
protected:
    virtual void stop();
    virtual EventConstSp tryPopEvent();
    virtual void submit(EventConstSp event);
    virtual uint32_t handleEvent(EventConstSp event) = 0;

    boost::thread m_thread;
    bool m_running;
    typedef boost::circular_buffer_space_optimized<EventConstSp> EventQueue;
    EventQueue m_queue;
    boost::mutex m_queueMutex;
    std::weak_ptr<Dispatcher> m_dispatcher;
};

#endif // SERVICE_H
