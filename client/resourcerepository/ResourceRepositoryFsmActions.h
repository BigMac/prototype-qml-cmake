#ifndef RESOURCEREPOSITORYFSMACTIONS_H
#define RESOURCEREPOSITORYFSMACTIONS_H

#include "CommonConnectionListener.h"
#include "messages/ResourceRequest.h"

#define LOG_ACTION(Action) \
    std::cout << "Action: " << #Action << std::endl;

struct ConnectToRepositoryServer
{
    template <class Fsm,class Evt,class SourceState,class TargetState>
    void operator()(Evt const&, Fsm& fsm, SourceState&,TargetState& )
    {
        LOG_ACTION(ConnectToRepositoryServer);
    }
};

struct SendResourceRequest
{

    template <class Fsm,class Evt,class SourceState,class TargetState>
    void operator()(Evt const& evt, Fsm& fsm, SourceState&,TargetState& )
    {
        LOG_ACTION(SendResourceRequest);
        //auto request = std::make_shared<ResourceRequest>(evt.getUrl());
        //fsm.dispatcher->
    }
};

struct SendResourceArrived
{
    template <class Fsm,class Evt,class SourceState,class TargetState>
    void operator()(Evt const& evt, Fsm& fsm, SourceState&,TargetState& )
    {
        LOG_ACTION(SendResourceArrived);
        //auto request = std::make_shared<ResourceRequest>(evt.getUrl());
        //fsm.dispatcher->
    }
};

#endif // RESOURCEREPOSITORYFSMACTIONS_H
