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
    Service();
    virtual ~Service() {}
    typedef std::shared_ptr<const Event> EventConstSp;
    virtual void post(EventConstSp event);
    virtual void run();
    virtual void join();
protected:
    virtual void stop();
    virtual void preRun() = 0;
    virtual uint32_t handleEvent(EventConstSp event) = 0;
    bool m_running;
    ConcurrentQueue<const Event> m_queue;
    boost::thread m_thread;
};

#endif // SERVICE_H
