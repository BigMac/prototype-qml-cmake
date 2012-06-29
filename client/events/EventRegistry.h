#pragma once
#include <functional>
#include <memory>
#include <vector>
#include <algorithm>

class DrawBufferReleased;
class DrawBufferRequest;
class DrawBufferResponse;
class GuiResourceRequest;
class GuiResourceResponse;
class NetworkMessageRequest;
class NetworkMessageResponse;
class OpenInterfaceWindowRequest;

template<typename T>
class Record
{
public:
    typedef std::function<void(std::shared_ptr<const T>)> CallbackFunction;
    typedef std::shared_ptr<const T> EventPtr;
    void registerCallback(CallbackFunction callback)
    {
        m_callbacks.push_back(callback);
    }

    void deregisterCallback(CallbackFunction callback)
    {
        m_callbacks.erase(
                    std::remove(
                        m_callbacks.begin(),
                        m_callbacks.end(),
                        callback),
                    m_callbacks.end());
    }
    const std::vector<CallbackFunction>& getCallbacks() { return m_callbacks; }
private:
    std::vector<CallbackFunction> m_callbacks;
};

class EventRegistry :
        public Record<DrawBufferReleased>,
        public Record<DrawBufferRequest>,
        public Record<DrawBufferResponse>,
        public Record<GuiResourceRequest>,
        public Record<GuiResourceResponse>,
        public Record<NetworkMessageRequest>,
        public Record<NetworkMessageResponse>,
        public Record<OpenInterfaceWindowRequest>
{
};
