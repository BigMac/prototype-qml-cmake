#ifndef QTSERVICEFSMACTIONS_H
#define QTSERVICEFSMACTIONS_H

#include <memory>
#include <string>
#include <iostream> // TODO remove when done with debug logging

#define LOG_ACTION(Action) \
    std::cout << "Action: " << #Action << std::endl;

// Actions
struct SendGuiResourceRequest
{
    template <class Fsm,class Evt,class SourceState,class TargetState>
    void operator()(Evt const& evt, Fsm& fsm, SourceState&,TargetState& )
    {
        LOG_ACTION(SendGuiResourceRequest)
        std::string url = evt.getUrl();
        fsm.dispatcher->post(std::make_shared<GuiResourceRequest>(url));
    }
};

struct Repaint
{
    template <class Fsm,class Evt,class SourceState,class TargetState>
    void operator()(Evt const& evt, Fsm& fsm, SourceState&,TargetState& )
    {
        LOG_ACTION(Repaint)
    }
};

struct SendDrawBufferRequest
{
    template <class Fsm,class Evt,class SourceState,class TargetState>
    void operator()(Evt const& evt, Fsm& fsm, SourceState&,TargetState& )
    {
        fsm.dispatcher->post(std::make_shared<DrawBufferRequest>());
    }
};
struct StartRendering
{
    template <class Fsm,class Evt,class SourceState,class TargetState>
    void operator()(Evt const& evt, Fsm& fsm, SourceState&,TargetState& )
    {
        LOG_ACTION(StartRendering)
    }
};

struct RegisterResourceListener
{
    template <class Fsm,class Evt,class SourceState,class TargetState>
    void operator()(Evt const& evt, Fsm& fsm, SourceState&,TargetState& )
    {
        LOG_ACTION(RegisterResourceListener)
    }
};

#endif // QTSERVICEFSMACTIONS_H
