#ifndef RESOURCEREPOSITORYFSM_H
#define RESOURCEREPOSITORYFSM_H

#include <boost/msm/front/state_machine_def.hpp>
// functors
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/euml/common.hpp>
#include "connection/ClientConnection.h"
#include "Dispatcher.h"
#include "ResourceRepositoryFsmActions.h"
#include "ResourceRepositoryFsmEvents.h"
#include "ResourceRepositoryFsmStates.h"
#include "messages/ResourceResponse.h"

using namespace boost::msm::front;

struct ResourceRepositoryFsm : public boost::msm::front::state_machine_def<ResourceRepositoryFsm>
{
    ResourceRepositoryFsm(std::shared_ptr<Dispatcher> dispatcher) :
        dispatcher(dispatcher)
    {}

    std::shared_ptr<Dispatcher> dispatcher;
    std::shared_ptr<ClientConnection> connection;

    // Transition table
    struct transition_table : boost::mpl::vector<
             Row< StateInitial, none, StateConnecting, ConnectToRepositoryServer, none >

            ,Row< StateConnecting, Connected, StateIdle, none, none >
            ,Row< StateConnecting, ConnectionError, StateDisconnected, none, none >

            ,Row< StateIdle, GuiResourceRequest, StateIdle, SendResourceRequest, none >
            ,Row< StateIdle, ResourceResponse, StateIdle, SendResourceArrived, none >
            ,Row< StateIdle, ConnectionError, StateDisconnected, none, none >

            ,Row< StateDisconnected, Connected, StateIdle, none, none >
            >{};

    typedef StateInitial initial_state;
};

#endif // RESOURCEREPOSITORYFSM_H
