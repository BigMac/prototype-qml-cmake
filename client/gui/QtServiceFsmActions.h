#ifndef QTSERVICEFSMACTIONS_H
#define QTSERVICEFSMACTIONS_H

#include "events/DrawBufferRequest.h"
#include "events/DrawBufferResponse.h"
#include "events/DrawBufferReleased.h"
#include "events/GuiResourceRequest.h"
#include "events/GuiResourceResponse.h"
#include "events/OpenInterfaceWindowRequest.h"

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
                fsm.renderer->prepareRender(evt.getUrl());
    }
};

struct SupplyResource
{
    template <class Fsm,class Evt,class SourceState,class TargetState>
    void operator()(Evt const& evt, Fsm& fsm, SourceState& ss,TargetState& )
    {
        LOG_ACTION(SupplyResource)
                fsm.renderer->resourceArrived(evt.getUrl(), evt.getData());
    }
};

#endif // QTSERVICEFSMACTIONS_H
