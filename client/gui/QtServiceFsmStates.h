#ifndef QTSERVICEFSMSTATES_H
#define QTSERVICEFSMSTATES_H

#include <iostream> // TODO remove when done with debug logging
#include <string>
#include "events/GuiResourceResponse.h" // TEMP

#define LOG_STATE(State) \
    template <class Event,class FSM> \
    void on_entry(Event const& ,FSM&) {std::cout << "entering: "<< #State << std::endl;} \
    template <class Event,class FSM> \
    void on_exit(Event const&,FSM& ) {std::cout << "leaving: "<< #State << std::endl;}

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

struct StateGuiResourceRequested : public boost::msm::front::state<>
{
    template <class Event,class FSM>
    void on_entry(Event const& evt, FSM& fsm)
    {
        requestedUrl = evt.getUrl();
        std::cout << "entering: StateGuiResourceRequested: "<< requestedUrl << std::endl;
        fsm.dispatcher->post(std::make_shared<GuiResourceResponse>(requestedUrl));
        std::cout << "GuiResourceResponse sent" << std::endl;
    }
    template <class Event,class FSM>
    void on_exit(Event const&,FSM& )
    {
        std::cout << "leaving: StateGuiResourceRequested"<< std::endl;
    }
    std::string requestedUrl;
};

struct StateRenderingQml : public boost::msm::front::state<>
{
    LOG_STATE(StateRenderingQml)
};
#endif // QTSERVICEFSMSTATES_H
