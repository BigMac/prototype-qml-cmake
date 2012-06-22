#ifndef QTSERVICEFSM_H
#define QTSERVICEFSM_H

#include <boost/msm/front/state_machine_def.hpp>
// functors
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/euml/common.hpp>
#include "events/GuiResourceRequest.h"
#include "events/GuiResourceResponse.h"

using namespace boost::msm::front;

struct QtServiceFsm : public boost::msm::front::state_machine_def<QtServiceFsm>
{
    // States
    struct StateInitial : public boost::msm::front::state<>
    {};

    struct StateLoadingMenu : public boost::msm::front::state<>
    {};

    struct StateMenuVisible : public boost::msm::front::state<>
    {};

    // Transition actions TODO move outside for other services, they will be shared
    template<typename EventType>
    struct Send
    {
        Send(EventType event) : event(event)
        {}
        template <class Fsm,class Evt,class SourceState,class TargetState>
        void operator()(Evt const&, Fsm& fsm, SourceState&,TargetState& )
        {
            fsm->submit(event);
        }
        EventType event;
    };

    // Transition table
    struct transition_table : boost::mpl::vector<
            Row< StateInitial, none, StateLoadingMenu, none, none >
            >{};

    typedef StateInitial initial_state;
};

#endif // QTSERVICEFSM_H
