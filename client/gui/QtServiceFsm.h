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
#include "Dispatcher.h"
#include "QmlRenderer.h"
#include <functional>

#include <iostream> // TODO remove when done with debug logging

#define LOG_STATE(State) \
    template <class Event,class FSM> \
    void on_entry(Event const& ,FSM&) {std::cout << "entering: "<< #State << std::endl;} \
    template <class Event,class FSM> \
    void on_exit(Event const&,FSM& ) {std::cout << "leaving: "<< #State << std::endl;}
#define LOG_ACTION(Action) \
    std::cout << "Action: " << #Action << std::endl;

using namespace boost::msm::front;

struct QtServiceFsm : public boost::msm::front::state_machine_def<QtServiceFsm>
{
    QtServiceFsm(std::shared_ptr<Dispatcher> dispatcher,
                 std::shared_ptr<QmlRenderer> renderer) :
        dispatcher(dispatcher),
        renderer(renderer)
    {}

    std::shared_ptr<Dispatcher> dispatcher;
    std::shared_ptr<QmlRenderer> renderer;

    // States
    struct StateInitial : public boost::msm::front::state<>
    {
        LOG_STATE(StateInitial)
    };

    struct StateIdle : public boost::msm::front::state<>
    {
        LOG_STATE(StateIdle)
    };

    struct StatedDrawBufferRequested : public boost::msm::front::state<>
    {
        LOG_STATE(StatedDrawBufferRequested)
    };

    struct StateQmlRequested : public boost::msm::front::state<>
    {
        LOG_STATE(StateQmlRequested)
        std::string requestedUrl;
    };

    struct StateRenderingQml : public boost::msm::front::state<>
    {
        LOG_STATE(StateRenderingQml)
    };

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

    struct GuiResourceResponseOk
    {
        template <class Fsm,class Evt,class SourceState,class TargetState>
        bool operator()(Evt const& evt, Fsm& fsm, SourceState&,TargetState& )
        {
            //fsm->submit(DrawBufferRequest);
            return true; // TEMP
        }
    };

    template<typename First, typename Second>
    class Seq2 : public ActionSequence_< boost::mpl::vector<First, Second> > {};

    // Transition table
    struct transition_table : boost::mpl::vector<
            Row< StateInitial, none, StateIdle, none, none >,
            Row< StateInitial, OpenInterfaceWindowRequest, StateIdle, StartRendering, none >,

            Row< StateIdle, OpenInterfaceWindowRequest, StateQmlRequested, SendGuiResourceRequest, none >,
            Row< StateIdle, DrawBufferNeeded,   StatedDrawBufferRequested, SendDrawBufferRequest, none >,

            Row< StatedDrawBufferRequested, DrawBufferResponse, StateIdle, Repaint, DrawBufferResponseOk >,
            Row< StatedDrawBufferRequested, DrawBufferResponse, StateIdle, none,    Not<DrawBufferResponseOk> >, // Need proper error handling

            Row< StateQmlRequested, GuiResourceResponse, StateRenderingQml, StartRendering, GuiResourceResponseOk >,
            Row< StateQmlRequested, GuiResourceResponse, StateIdle, none, Not<GuiResourceResponseOk> >, // Need proper error handling

            Row< StateRenderingQml, ResourceNeeded, StateRenderingQml, Seq2<SendGuiResourceRequest, RegisterResourceListener>, none >
            >{};

    typedef StateInitial initial_state;
};

#endif // QTSERVICEFSM_H
