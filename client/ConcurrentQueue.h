#ifndef CONCURRENTQUEUE_H
#define CONCURRENTQUEUE_H
#include <memory>
#include <vector>
#include <boost/thread.hpp>

template<typename T>
class ConcurrentQueue
{
public:
    typedef std::shared_ptr<T> ItemSharedPtr;
    void push(ItemSharedPtr item)
    {
        boost::mutex::scoped_lock(m_queueMutex);
        m_queue.push_back(item);
    }

    ItemSharedPtr pop()
    {
        boost::mutex::scoped_lock(m_queueMutex);
        auto beginIter = m_queue.begin();
        if(beginIter == m_queue.end())
            return ItemSharedPtr(); // Nothing on the queue
        auto result = *beginIter;
        m_queue.erase(beginIter);
        return result;
    }

protected:
    typedef std::vector<std::shared_ptr<T> > Queue;
    Queue m_queue;
    boost::mutex m_queueMutex;
};

#endif // CONCURRENTQUEUE_H
