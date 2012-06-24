#ifndef QTSERVICEFSM_H
#define QTSERVICEFSM_H

#include <boost/msm/front/state_machine_def.hpp>
// functors
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/euml/common.hpp>
#include "events/DrawBufferRequest.h"
#include "events/DrawBufferResponse.h"
#include "events/DrawBufferReleased.h"
#include "events/GuiResourceRequest.h"
#include "events/GuiResourceResponse.h"
#include "events/OpenInterfaceWindowRequest.h"

using namespace boost::msm::front;

struct QtServiceFsm : public boost::msm::front::state_machine_def<QtServiceFsm>
{
    // States
    struct StateInitial : public boost::msm::front::state<>
    {};

    struct StateIdle : public boost::msm::front::state<>
    {};

    struct StatedDrawBufferRequested : public boost::msm::front::state<>
    {};

    struct StateQmlRequested : public boost::msm::front::state<>
    {
        std::string requestedUrl;
    };

    struct StateRenderingQml : public boost::msm::front::state<>
    {};

    // Events, in addition to common client events
    struct ResourceNeeded
    {
    public:
        ResourceNeeded(const std::string& url) : m_url(url) {}
        const std::string& getUrl() { return m_url; }
    private:
        std::string m_url;
    };

    struct DrawBufferNeeded
    {};

    // Actions
    struct SendGuiResourceRequest
    {
        template <class Fsm,class Evt,class SourceState,class TargetState>
        void operator()(Evt const& evt, Fsm& fsm, SourceState&,TargetState& )
        {
            std::string url = evt.getUrl();
            fsm->submit(GuiResourceRequest(url));
        }
    };

    struct Repaint
    {
        template <class Fsm,class Evt,class SourceState,class TargetState>
        void operator()(Evt const& evt, Fsm& fsm, SourceState&,TargetState& )
        {
//            std::string url = evt.getUrl();
//            fsm->submit(GuiResourceRequest(url));
        }
    };

    struct SendDrawBufferRequest
    {
        template <class Fsm,class Evt,class SourceState,class TargetState>
        void operator()(Evt const& evt, Fsm& fsm, SourceState&,TargetState& )
        {
            fsm->submit(DrawBufferRequest());
        }
    };

    // Guards
    template<typename Guard>
    struct Not : private Guard
    {
        template <class Fsm,class Evt,class SourceState,class TargetState>
        bool operator()(Evt const& evt, Fsm& fsm, SourceState& ss ,TargetState& ts)
        {
            return ! Guard::operator()(evt, fsm, ss, ts);
        }
    };

    struct DrawBufferResponseOk
    {
        template <class Fsm,class Evt,class SourceState,class TargetState>
        bool operator()(Evt const& evt, Fsm& fsm, SourceState&,TargetState& )
        {
            //fsm->submit(DrawBufferRequest);
            return true; // TEMP
        }
    };

    // Transition table
    struct transition_table : boost::mpl::vector<
            Row< StateInitial, none, StateIdle, none, none >,
            Row< StateIdle, OpenInterfaceWindowRequest, StateQmlRequested, SendGuiResourceRequest, none >,
            Row< StateIdle, DrawBufferNeeded, StatedDrawBufferRequested, SendDrawBufferRequest, none >,
            Row< StatedDrawBufferRequested, DrawBufferResponse, StateIdle, Repaint, DrawBufferResponseOk >,
            Row< StatedDrawBufferRequested, DrawBufferResponse, StateIdle, none, Not<DrawBufferResponseOk> >,
            Row< StateQmlRequested, OpenInterfaceWindowRequest, StateQmlRequested, SendGuiResourceRequest, none >
            >{};

    typedef StateInitial initial_state;
};

#endif // QTSERVICEFSM_H
