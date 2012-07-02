#ifndef RESOURCEREPOSITORYFSMSTATES_H
#define RESOURCEREPOSITORYFSMSTATES_H

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

struct StateConnecting : public boost::msm::front::state<>
{
    LOG_STATE(StateConnecting)
};

struct StateDisconnected : public boost::msm::front::state<>
{
    LOG_STATE(StateDisconnected)
};

#endif // RESOURCEREPOSITORYFSMSTATES_H
