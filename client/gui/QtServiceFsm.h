#ifndef QTSERVICEFSM_H
#define QTSERVICEFSM_H

#include <boost/msm/front/state_machine_def.hpp>
// functors
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/euml/common.hpp>

#include "QtServiceFsmActions.h"
#include "QtServiceFsmEvents.h"
#include "QtServiceFsmGuards.h"
#include "QtServiceFsmStates.h"

#include "events/DrawBufferRequest.h"
#include "events/DrawBufferResponse.h"
#include "events/DrawBufferReleased.h"
#include "events/GuiResourceRequest.h"
#include "events/GuiResourceResponse.h"
#include "events/OpenInterfaceWindowRequest.h"
#include "Dispatcher.h"
#include "QmlRenderer.h"
#include <functional>


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

    template<typename First, typename Second>
    class Seq2 : public ActionSequence_< boost::mpl::vector<First, Second> > {};

    // Transition table
    struct transition_table : boost::mpl::vector<
            Row< StateInitial, none, StateIdle, InitializeQmlRenderer, none >

            ,Row< StateIdle, OpenInterfaceWindowRequest, StateRenderingQml, StartRendering, none >
            ,Row< StateIdle, DrawBufferNeeded,   StatedDrawBufferRequested, SendDrawBufferRequest, none >

            ,Row< StatedDrawBufferRequested, DrawBufferResponse, StateIdle, Repaint, DrawBufferResponseOk >
            ,Row< StatedDrawBufferRequested, DrawBufferResponse, StateIdle, none,    Not<DrawBufferResponseOk> > // Need proper error handling

            ,Row< StateRenderingQml, ResourceNeeded, StateGuiResourceRequested, SendGuiResourceRequest, none >

            ,Row< StateGuiResourceRequested, GuiResourceResponse, StateRenderingQml, SupplyResource, GuiResourceResponseOk >
            ,Row< StateGuiResourceRequested, GuiResourceResponse, StateGuiResourceRequested, Print, Not<GuiResourceResponseOk> >
            >{};

    typedef StateInitial initial_state;
};

#endif // QTSERVICEFSM_H
