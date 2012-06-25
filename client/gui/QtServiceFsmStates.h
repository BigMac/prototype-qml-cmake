#ifndef QTSERVICEFSMSTATES_H
#define QTSERVICEFSMSTATES_H

#include <iostream> // TODO remove when done with debug logging
#include <string>

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
    LOG_STATE(StateGuiResourceRequested)
    std::string requestedUrl;
};

struct StateRenderingQml : public boost::msm::front::state<>
{
    LOG_STATE(StateRenderingQml)
};
#endif // QTSERVICEFSMSTATES_H
