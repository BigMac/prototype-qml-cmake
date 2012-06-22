#ifndef SERVICE_H
#define SERVICE_H
#include "IService.h"
#include "ConcurrentQueue.h"
#include <cstdint>
#include <boost/thread.hpp>

class Dispatcher;
class Service : public IService
{
public:
    Service(std::shared_ptr<Dispatcher> dispatcher);
    typedef std::shared_ptr<const Event> EventConstSp;
    virtual void post(EventConstSp event);
    virtual void run();
protected:
    virtual void stop();
    virtual void submit(EventConstSp event);
    virtual void preRun() = 0;
    virtual uint32_t handleEvent(EventConstSp event) = 0;
    boost::thread m_thread;
    bool m_running;
    std::shared_ptr<Dispatcher> m_dispatcher;
    ConcurrentQueue<const Event> m_queue;
};

#endif // SERVICE_H
