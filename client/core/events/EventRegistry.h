#ifndef EVENTREGISTRY_H
#define EVENTREGISTRY_H
#include <functional>
#include <memory>
#include <vector>

class NetworkRequest;
class QmlRequest;

template<typename T>
class Record
{
public:
    typedef std::function<void(std::shared_ptr<const T>)> CallbackFunction_t;
    void registerCallback(CallbackFunction_t callback) { m_callbacks.push_back(callback); }
    const std::vector<CallbackFunction_t>& getCallbacks() { return m_callbacks; }
private:
    std::vector<CallbackFunction_t> m_callbacks;
};

class EventRegistry :
        public Record<NetworkRequest>,
        public Record<QmlRequest>
{
};

#endif // EVENTREGISTRY_H
