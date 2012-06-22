#ifndef QTSERVICEFSM_H
#define QTSERVICEFSM_H
#include <boost/msm/front/state_machine_def.hpp>

struct QtServiceFsm : public boost::msm::front::state_machine_def<QtServiceFsm>
{
    struct StateInitial : public boost::msm::front::state<>
    {

    };

    typedef StateInitial initial_state;
};

#endif // QTSERVICEFSM_H
