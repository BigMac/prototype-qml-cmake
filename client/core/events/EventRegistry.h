#ifndef EVENTREGISTRY_H
#define EVENTREGISTRY_H
#include <functional>
#include <memory>
#include <vector>

class GuiResourceRequest;
class GuiResourceResponse;
class NetworkMessageRequest;
class NetworkMessageResponse;

template<typename T>
class Record
{
public:
    typedef std::function<void(std::shared_ptr<const T>)> CallbackFunction;
    typedef std::shared_ptr<const T> EventPtr;
    void registerCallback(CallbackFunction callback) { m_callbacks.push_back(callback); }
    const std::vector<CallbackFunction>& getCallbacks() { return m_callbacks; }
private:
    std::vector<CallbackFunction> m_callbacks;
};

class EventRegistry :
        public Record<GuiResourceRequest>,
        public Record<GuiResourceResponse>,
        public Record<NetworkMessageRequest>,
        public Record<NetworkMessageResponse>
{
};

#endif // EVENTREGISTRY_H
